#include <iostream> 
#include <cstddef>

class Matrix{
    int** matr;
    const size_t rows, cols;

    public:
        class Proxy
        {
            size_t num_cols;
            int* row;
            public:
            Proxy(size_t m_cols, int* r);
            int& operator[](size_t i);       
            const int& operator[](size_t i) const;

        };
        Matrix(const size_t a, const size_t b);
        size_t getRows() const;
        size_t getColumns() const;
        Proxy operator[](size_t i);
        const Proxy operator[](size_t i) const;
        Matrix& operator*=(int n);
        bool operator==(const Matrix& other) const;
        bool operator!=(const Matrix& other) const;
        ~Matrix();
};