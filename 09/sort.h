#include <iostream>
#include <algorithm>
#include <atomic>
#include <thread>
#include <string.h>
#include <cmath>
#include <cstdlib>
#include <exception> 


const int store = 1 << 18;
const char *output_file = "out.bin";
const char *input_file = "test.bin";
const char *temp_file = "temp.bin";
const char *output_first_file = "outputtmp1.bin";
const char *output_second_file = "outputtmp2.bin";

FILE * special_fopen(const char * fname, const char * modeopen);
int first_sort();
void merging(const int beg, const int size_of_chunk, const char *temp_file, FILE* const output);
void merge_in_one(bool flag);
int main();