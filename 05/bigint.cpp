#include "bigint.h"

int BigInt::count_size(int value){
    int i = 0;
    if(value<0){
        value *= (-1);
    }
    while(value != 0) {
        value /= 10;
        i++;
    }
    i++;
    return i;
}

BigInt::BigInt(int value) {
    if(value<0){
        sign = -1;
        value *= (-1);
    } else {
        sign = 1;
    }

    size = count_size(value);
    //mem = (char*)malloc(sizeof(char)*size);
    mem = new char[size];

    for (int i = 0; i<size; i++){
        mem[i]=value%10 + '0';
        value /= 10;
    }
    mem[size]='\0';
}

BigInt::BigInt(){
    sign = 1;
    size = 2;
    //mem = (char*)malloc(sizeof(char)*size);
    mem = new char[size];
    mem[0]='0';
    mem[1]='\0';
}

BigInt::~BigInt(){
    //free(mem);
    delete[] mem;
}

BigInt::BigInt(const BigInt& copied)
    //:mem((char*)malloc(sizeof(char)*copied.size))
    : mem(new char[copied.size])
    , size(copied.size)
    , sign(copied.sign)
{
    std::copy(copied.mem, copied.mem + size, this->mem);
}

BigInt& BigInt::operator=(const BigInt& copied)
{
    if(this == &copied){
        return *this;
    }
    //char* ptr = (char*)malloc(sizeof(char) * (copied.size));
    char* ptr = new char[copied.size];
    //free(mem);
    delete[] mem;
    mem = ptr;
    size = copied.size;
    sign = copied.sign;
    std::copy(copied.mem, copied.mem + size, this->mem);
    return *this;
}


BigInt::BigInt(BigInt&& moved)
    : mem(moved.mem)
    , size(moved.size)
    , sign(moved.sign)
{
    moved.mem = nullptr;
    moved.size = 0;
    moved.sign = 0;
}

BigInt& BigInt::operator=(BigInt&& moved){
    if (this == &moved)
        return *this;
    //free(mem);
    delete [] mem;
    mem = moved.mem;
    size = moved.size;
    sign = moved.sign;
    moved.mem = nullptr;
    moved.size = 0;
    moved.sign = 0;
    return *this;
}

bool BigInt::operator==(const BigInt& other) const{
    bool check = true;
    if (size != other.size || sign != other.sign)
        return false;
    for (int i = 0; i < size; i++)
    {
        if(mem[i] != other.mem[i]){
            check = false;
            break;
        }
    }
    return check;
}

bool BigInt::operator!=(const BigInt& other) const {
    return !(*this == other);
}

bool BigInt::operator>(const BigInt& other) const {
    int i = size - 1;
    if (sign == -1 && other.sign == 1)
        return false;
    if (sign == 1 && other.sign == -1)
        return true;
    if (sign == 1 && other.sign == 1)
    {
        if (size < other.size)
            return false;
        if (size > other.size)
            return true;
        while (i >= 0 && mem[i] == other.mem[i])
            i--;
        if (mem[i] > other.mem[i])
            return true;
        return false;
    }

    if (sign == -1 && other.sign == -1)
    {
        if (size < other.size)
            return true;
        if (size > other.size)
            return false;
        while (i >= 0 && mem[i] == other.mem[i])
            i--;
        if (mem[i] > other.mem[i])
            return false;
        return true;
    } 
}

bool BigInt::operator<(const BigInt& other)const  {
    return !(*this > other);
}

bool BigInt::operator<=(const BigInt& other) const {
    return (*this < other || *this == other);
}

bool BigInt::operator>=(const BigInt& other) const {
    return (*this > other || *this == other);
}

BigInt BigInt::operator-() const {
    BigInt temp = *this;
    temp.sign *= -1;
    return temp;
}

std::ostream& operator<<(std::ostream& out, const BigInt& obj)
{
    if (obj.sign==-1)
    {
        out << '-';
    }
    for (int i = obj.size - 1; i >= 0; i--)
    {
        out << obj.mem[i];
    }
    return out;
}

BigInt BigInt::operator+(const BigInt & other) const
{
    BigInt res;
    int left = 0;
    int i = 0;
    char* ptr_max;
    int max_size, min_size, tmp;
    if (sign == 1 && other.sign == -1)
    {
        BigInt temp;
        temp = other;
        temp.sign = 1;
        res = *this - temp;
        return res;
    }
    if (sign == -1 && other.sign == 1)
    {
        BigInt temp;
        temp = *this;
        temp.sign = 1;
        res = other - temp;
        return res;
    }
    if (sign == -1 && other.sign == -1)
        res.sign = -1;
    else
        res.sign = 1;
    if (size >= other.size)
    {
        ptr_max = mem;
        max_size = size;
        min_size = other.size;
    }
    else
    {
        ptr_max = other.mem;
        max_size = other.size;
        min_size = size;
    }

    //char* ptr = (char*)malloc(sizeof(char) * (max_size + 2));
    char* ptr = new char[max_size + 2];
    //free(res.mem);
    delete [] res.mem;
    res.mem = ptr;
    while (i < min_size)
    {
        tmp = mem[i] + other.mem[i] - 2 *'0' + left;
        left = tmp / 10;
        res.mem[i] = tmp % 10 + '0';
        i++;
    }
    while (i < max_size)
    {
        tmp = ptr_max[i] - '0' + left;
        left = tmp / 10;
        res.mem[i] = tmp % 10 + '0';
        i++;
    }
    if (left != 0)
    {
        res.mem[i] = left + '0';
        i++;
    }
    res.mem[i] = '\0';
    res.size = i;
    return res;
}

BigInt BigInt::operator-(const BigInt & other) const
{
    BigInt res;
    int left = 0;
    int i = 0;
    char *ptr_max, *ptr_min;
    int max_size, min_size, tmp;
    if (sign == 1 && other.sign == -1)
    {
        BigInt x;
        x = other;
        x.sign = 1;
        res = *this + x;
        return res;
    }
    if (sign == -1 && other.sign == 1)
    {
        BigInt x;
        x = other;
        x.sign = -1;
        res = x + *this;
        return res;
    }
    if (*this >= other)
        res.sign = false;
    else
        res.sign = true;
    BigInt x;
    BigInt y;
    x = *this;
    y = other;
    x.sign = false;
    y.sign = false;
    if (x >= y)
    {
        ptr_max = mem;
        ptr_min = other.mem;
        max_size = size;
        min_size = other.size;
    }
    else
    {
        ptr_max = other.mem;
        ptr_min = mem;
        max_size = other.size;
        min_size = size;
    }
    //char* ptr = (char*)malloc(sizeof(char) * (max_size + 1));
    char* ptr = new char[max_size + 1];
    //free(res.mem);
    delete[] res.mem;
    res.mem = ptr;
    while (i < min_size)
    {
        if (ptr_max[i] - left < ptr_min[i])
        {
            res.mem[i] = ptr_max[i] + 10 - ptr_min[i] + '0' - left;
            left = 1;
        }
        else
        {
            res.mem[i] = ptr_max[i] - ptr_min[i] + '0' - left;
            left = 0;
        }
        i++;
    }
    while (i < max_size)
    {
        if (ptr_max[i] == '0' && left)
        {
            res.mem[i] = ptr_max[i] + 10 - left;
            left = 1;
        }
        else
        {
            res.mem[i] = ptr_max[i] - left;
            left = 0;
        }
        i++;
    }
    res.mem[i] = '\0';
    res.size = i;
    res.delete_zeros();
    return res;
}

void BigInt::delete_zeros()
{
    int i = size - 1;
    while (mem[i] == '0')
    {
        i--;
    }
    if (i == -1)
    {
        BigInt z;
        *this = z;
        return;
    }
    //char* ptr = (char*)malloc(sizeof(char) * (i + 2));
    char* ptr = new char[i+2];
    ptr[i + 1] = '\0';
    size = i + 1;
    while (i >= 0)
    {
        ptr[i] = mem[i];
        i--;
    }
    //free(mem);
    delete[] mem;
    mem = ptr;
    return;
}