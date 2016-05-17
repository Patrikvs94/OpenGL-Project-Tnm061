#include <GLFW/glfw3.h>
#include <iostream>
#ifdef __WIN32__
#include <GL/glext.h>
#endif

#include "tnm061.hpp"  // To be able to use OpenGL extensions
class particle {

private:

    friend class Cloud;
    GLuint vao;          // Vertex array object, the main handle for geometry
    int nverts; // Number of vertices in the vertex array
    int ntris;  // Number of triangles
    GLuint vertexbuffer; // Buffer ID to bind to GL_ARRAY_BUFFER
    GLuint indexbuffer;  // Buffer ID to bind to GL_ELEMENT_ARRAY_BUFFER
    GLfloat *vertexarray; // Vertex array on interleaved format: x y z nx ny nz s t
    GLuint *indexarray;   // Element index array.

    //positions of the pixels
    float xPos;
    float yPos;
    float zPos;
    //constructor
    particle();
    //destructor
    ~particle();

// Clean up allocated data in a triangleSoup object
void clean();
//create the pixel
void createParticle();
//render the pixel
void render();


};

