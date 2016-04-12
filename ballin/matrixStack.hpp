#include "Matrix.hpp"

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
    void translate(int x, int y, int z);
    void scale(float factor);
    int getDepth();


private:

    //Variables

    //Functions

}
