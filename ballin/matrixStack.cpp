#include "Matrix.hpp"
#include "matrixStack.hpp"

matrixStack::matrixStack(){
    Matrix *current = new Matrix();
}

void matrixStack::push(){
    Matrix *temp = current;
    Matrix *newMatrix = new Matrix(current);
    current = newMatrix;
    current->prev = temp;
}

void matrixStack::pop(){
    Matrix *temp = current;
    current = temp->prev;
    delete temp;
}

matrixStack::~matrixStack(){

}

int matrixStack::getDepth(){
    int depth = 0;

    //STUFF

    return depth;
}
