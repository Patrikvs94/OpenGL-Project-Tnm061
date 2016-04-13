#include "Matrix.hpp"

Matrix::Matrix(){
    reset();
    prev =nullptr;
}

Matrix::Matrix(const Matrix& M ){
    prev=M.prev;
    for(int row=1; row<=4; ++row)
    {
        for(int col=1; col<=4; ++col)
        {
            (*this)(row, col)= M(row, col);
        }
    }
    
}


void Matrix::reset(){
    m[0]=1.0f;  m[4]=0.0f;  m[8]=0.0f;  m[12]=0.0f;
    m[1]=0.0f;  m[5]=1.0f;  m[9]=0.0f;  m[13]=0.0f;
    m[2]=0.0f;  m[6]=0.0f;  m[10]=1.0f; m[14]=0.0f;
    m[3]=0.0f;  m[7]=0.0f;  m[11]=0.0f; m[15]=1.0f;
}

float& Matrix::operator()(const int row, const int col){
    return m[(row-1)+(col-1)*4];
}

const float& Matrix::operator()(const int row, const int col) const{
    return m[(row-1)+(col-1)*4];
}

Matrix& Matrix::operator*(const Matrix& M){
    Matrix* product= new Matrix();
    product->prev=prev;
    for(int row=1; row<=4; ++row)
    {
        for(int col=1; col<=4; ++col)
        {
            (*product)(row, col) =
            (*this)(row, 1)*M(1, col) + (*this)(row, 2)*M(2, col) +
            (*this)(row, 3)*M(3, col) + (*this)(row, 4)*M(4, col);
        }
    }
    return  *product;
}

Matrix& Matrix::operator*=(const Matrix& M)
{
    *this=(*this)*M;
    return *this;
}