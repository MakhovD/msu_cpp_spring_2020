#include "sort.h"
using FILE_pointer = std::unique_ptr<FILE, int(*)(FILE*)>;
FILE * special_fopen(const char * fname, const char * modeopen){
    FILE* f = fopen(fname, modeopen);
    if(!f) {
        throw std::runtime_error("can not open file");
    } else {
        return f;
    }
}

int first_sort() {
    std::unique_ptr<uint64_t[]> data(new uint64_t [store]);
    FILE_pointer  input  (special_fopen(input_file, "rb"), fclose);
    FILE_pointer  output  (special_fopen(output_file, "wb"), fclose);

    int read_numbers = 0, i = 0;
    do {
        read_numbers = fread(data.get(), sizeof(uint64_t), store, input.get());
        i++;
        std::sort(data.get(), data.get() + read_numbers);
        fwrite(data.get(), sizeof(uint64_t), read_numbers, output.get());
    }
    while (read_numbers == store);
    return i;
}

void merging(const int beg, const int size_of_chunk, const char *temp_file, FILE* const output) {
    FILE_pointer  input1 (special_fopen(temp_file, "rb"),fclose);
    FILE_pointer  input2 (special_fopen(temp_file, "rb"), fclose);

    std::unique_ptr<uint64_t []> first_store (new uint64_t [store]);
    std::unique_ptr<uint64_t []> second_store (new uint64_t [store]);
    std::unique_ptr<uint64_t []> merge (new uint64_t [2 * store]);

    fread(first_store.get(),  sizeof(uint64_t), store * beg, input1.get());
    fread(second_store.get(), sizeof(uint64_t), store * beg, input2.get());

    for (int i = 0; i <= size_of_chunk; i++) {
        fread(second_store.get(), sizeof(uint64_t), store, input2.get());
    }

    fread(first_store.get(), sizeof(uint64_t), store, input1.get());
    int numbers_read = fread(second_store.get(), sizeof(uint64_t), store, input2.get());

    uint64_t *first_cur = first_store.get(), *sec_cur = second_store.get();
    int carried_out_1 = 1, carried_out_2 = 1; 
    bool finished = 0;
    do {
        if (*first_cur - *(first_store.get()) == store) {
            carried_out_1++;
            fread(first_store.get(), sizeof(uint64_t), store, input1.get());
            first_cur = first_store.get();
        }
        if (*sec_cur  - *(second_store.get()) == numbers_read) {
            carried_out_2++;
            numbers_read = fread(second_store.get(), sizeof(uint64_t), store, input2.get());
            sec_cur  = second_store.get();
        }
        int how_comp = 0, cur1 = 0, cur2 = 0;
        while (cur1 < store && cur2 < store) {
            auto merge_array = merge.get();
            if (*first_cur < *sec_cur) {
                merge_array[how_comp++] = *(first_cur++);
                cur1++;
            } else {
                merge_array[how_comp++] = *(sec_cur ++);
                cur2++;
            }
        }
        finished = cur1 != store;

        fwrite(merge.get(), sizeof(uint64_t), how_comp, output);
    } while (!finished && !(carried_out_1 == size_of_chunk && !finished)
           && !(carried_out_2 == size_of_chunk && finished));

    if (finished) {
        fwrite(sec_cur , sizeof(uint64_t), store, output);
        while (carried_out_2 != size_of_chunk) {
            fread(second_store.get(), sizeof(uint64_t), store, input2.get());
            carried_out_2++;
            fwrite(second_store.get(), sizeof(uint64_t), store, output);
        }
    } else {
        fwrite(first_cur , sizeof(uint64_t), store - (*first_cur - *(first_store.get())), output);
        while (carried_out_1 != size_of_chunk) {
            fread(first_store.get(), sizeof(uint64_t), store, input1.get());
            carried_out_1++;
            fwrite(first_store.get(), sizeof(uint64_t), store, output);
        }
    }
    return;
}

void merge_in_one(bool flag) {
    char *name1 = (char*)output_first_file, *name2 = (char*)output_second_file;
    if (!flag) {
        std::swap(name1, name2);
    }        

    FILE_pointer  output1 (special_fopen(name1, "rb"),fclose);
    FILE_pointer  output2 (special_fopen(name2, "rb"),fclose);
    FILE_pointer  output (special_fopen(temp_file, "wb"),fclose);

    std::unique_ptr<uint64_t []> buf (new uint64_t [store]);
    int how_read = 1;
    while (how_read) {
        how_read = fread(buf.get(), sizeof(uint64_t), store, output1.get());
        fwrite(buf.get(), sizeof(uint64_t), how_read, output.get());
    }
    how_read = 1;
    while (how_read) {
        how_read = fread(buf.get(), sizeof(uint64_t), store, output2.get());
        fwrite(buf.get(), sizeof(uint64_t), how_read, output.get());
    }
    return;
}

int main() {
    std::thread thread1, thread2;
    int n = first_sort();
    int i = (int)log2(n) + 1, size = 1;
    n /= 2;
    for (int j = 0; j < i; j++)
    {
        FILE_pointer  output1 (special_fopen(output_first_file, "wb"), fclose);
        FILE_pointer  output2 (special_fopen(output_second_file, "wb"), fclose);

        for (int k = 1; k <= n; k += 2)
        {
            thread1 = std::thread(merging,  2 * k * size, size, output_file, output1.get());
            thread2 = std::thread(merging,  2 * (k-1) * size, size, output_file, output2.get());
            thread1.join();
            thread2.join();
        }
        size <<= 1;
        merge_in_one(!(n & 1));
    }
    std::system("rm outputtmp1.bin outputtmp2.bin temp.bin");
    return 0;
}