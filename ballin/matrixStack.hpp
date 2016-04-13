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

    //Creates a rotation matrix and multiplies it with current
    void rotX(float angle);
    void rotY(float angle);
    void rotZ(float angle);

    //Creates a translation matrix and multiplies it with current
    void translate(float x, float y, float z);

    //Creates a scaling matrix and multiplies it with current
    void scale(float factor);
    void scale(float x, float y, float z);

    int getDepth();


private:

    //Variables
    Matrix *current;

    //Functions

};
