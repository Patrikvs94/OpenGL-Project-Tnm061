//#include <GLFW/glfw3.h> // Oklart om detta behövs

#ifndef Matrix_hpp
#define Matrix_hpp

#endif /* Matrix_hpp */


class Matrix
{
    friend class matrixStack;
    
private:
    // array containing values of matrix
    float m[16];
    //Pointer to previous Matrix in MatrixStack
    Matrix *prev;
    
public:
    //Default constructor
    Matrix();
    //Copy constructor
    Matrix (const Matrix& M);
    
    //Matrix multiplication
    Matrix& operator*(const Matrix& M);
    Matrix& operator*=(const Matrix& M);
    
    //gives value at (row,col) 1 <= row,col <=4
    const float& operator()(const int row, const int col) const;
    float& operator()(const int row, const int col);
    
    //resets matrix to unit-matrix
    void reset();
    
};

