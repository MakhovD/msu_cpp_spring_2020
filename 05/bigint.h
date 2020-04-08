#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

class BigInt{
    char* mem;
    int sign;
    int size;

    int count_size(int value);
    void delete_zeros();
public:
    BigInt();
    BigInt(int value);
    ~BigInt();

    BigInt(const BigInt& copied); //A a1; A a2 = a1;
    BigInt& operator=(const BigInt& copied);//A a1,a2; a2=a1

    BigInt(BigInt&& moved);
    BigInt& operator=(BigInt&& moved);

    bool operator==(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator<(const BigInt& other)const;
    bool operator<=(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;

    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator-() const;
    
    friend std::ostream& operator<<(std::ostream&, const BigInt& obj);
};
