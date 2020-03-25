#include "matrix.h"


Matrix::Proxy::Proxy(size_t m_cols, int* r) : num_cols(m_cols) , row(r) { }

int& Matrix::Proxy::operator[](size_t i) {
    if(i >= num_cols) {
        throw std::out_of_range("");
    }
    return row[i];
}      
const int& Matrix::Proxy::operator[](size_t i) const {
    if(i >= num_cols) {
        throw std::out_of_range("");
    }
    return row[i];
}

Matrix::Proxy Matrix::operator[](size_t i) {
    if(i >= this->rows) {
        throw std::out_of_range("");
    }
    return Proxy(this->cols, matr[i]);
}
const Matrix::Proxy Matrix::operator[](size_t i) const {
    if(i >= this->rows) {
        throw std::out_of_range("");
    }
    return Proxy(this->cols, matr[i]);
}

Matrix::Matrix(const size_t a, const size_t b) : rows(a), cols(b){
    matr = new int*[rows];
    for(int i=0; i<cols; i++){
        matr[i] = new int[cols];
    }
}

Matrix::~Matrix(){
    for(int i = 0; i < this->cols; i++){
        delete[] matr[i];
    }
    delete[] matr;
}

size_t Matrix::getRows() const{
    return this->rows;
}

size_t Matrix::getColumns() const{
    return this->cols;
}

bool Matrix::operator==(const Matrix& other) const{
    if (this == &other)
        return true;
    
    if ((this->cols != other.getColumns()) || (this->rows != other.getRows()))
        return false;
    
    for (int i = 0; i < this->rows; ++i){
        for(int j = 0; j < this->cols; ++j){
            if(matr[i][j]!=other.matr[i][j])
                return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const{
    return !(*this == other);
}

Matrix& Matrix::operator*=(int n){
    for(int i = 0; i < this->rows; ++i) {
        for(int j = 0; j < this->cols; ++j) {
            matr[i][j] *= n;
        }
    }
    return *this;
}