#include "Matrix.hpp"
#include "matrixStack.hpp"

matrixStack::matrixStack(){
    current = new Matrix();
}

void matrixStack::push(){
    Matrix *temp = current;
    Matrix *newMatrix = new Matrix(*current);
    current = newMatrix;
    current->prev = temp;
}

void matrixStack::pop(){
    Matrix *temp = current;
    current = temp->prev;
    delete temp;
}

matrixStack::~matrixStack(){
    Matrix *toBeDeleted=current;
    while(toBeDeleted!=nullptr)
    {
        current=current->prev;
        delete toBeDeleted;
        toBeDeleted=current;
    }
    
}


void matrixStack::rotX(float angle){
    Matrix rx;
    rx(2,2)=cosf(angle);
    rx(2,3)=-sinf(angle);
    rx(3,2)=sinf(angle);
    rx(3,3)=cosf(angle);
    *current*=rx;
}

void matrixStack::rotY(float angle){
    Matrix ry;
    ry(1,1)=cosf(angle);
    ry(1,3)=sinf(angle);
    ry(3,1)=-sinf(angle);
    ry(3,3)=cosf(angle);
    *current*=ry;
}

void matrixStack::rotZ(float angle){
    Matrix rz;
    rz(1,1)=cosf(angle);
    rz(1,2)=-sinf(angle);
    rz(2,1)=sinf(angle);
    rz(2,2)=cosf(angle);
    *current*=rz;
}

void matrixStack::translate(float x, float y, float z){
    Matrix t;
    t(1,1)=x;
    t(1,2)=y;
    t(1,3)=z;
    *current*=t;
}

void matrixStack::scale(float factor){
    Matrix s;
    s(1,1)= factor;
    s(2,2)= factor;
    s(3,3)= factor;
    *current*=s;
}

void matrixStack::scale(float x, float y, float z){
    Matrix s;
    s(1,1)= x;
    s(2,2)= y;
    s(3,3)= z;
    *current*=s;
}

int matrixStack::getDepth(){
    int depth = 0;

    //STUFF

    return depth;
}
