#include "Matrix.hpp"
#include <cmath>

class matrixStack {

public:

    //Variables

    //Constructor
    matrixStack();

    //Destructor
    ~matrixStack();

    //Functions
    void pop();
    void push();
    void rotX(float angle);
    void rotY(float angle);
    void rotZ(float angle);
    void translate(float x, float y, float z);
    void scale(float factor);
    void scale(float x, float y, float z);
    int getDepth();


private:

    //Variables
    Matrix *current;

    //Functions

};