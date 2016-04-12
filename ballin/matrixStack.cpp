#include "Matrix.hpp"
#include "matrixStack.hpp"

matrixStack::matrixStack(){
    Matrix *current = new Matrix();
}

matrixStack::push(){
    Matrix *temp = current;
    Matrix *newMatrix = new Matrix(current);
    current = newMatrix;
    current->prev = temp;
}

matrixStack::pop(){
    Matrix *temp = current;
    current = temp->prev;
    delete temp;
}

matrixStack::~matrixStack(){

}



