// File and console I/O for logging and error reporting
#include <iostream>

#define GLFW_INCLUDE_GLU

// System utilities
#include <cstdio>
#include <cstdlib>
#include <cmath>

#ifndef M_PI
#define M_PI (3.141592653589793)
#endif

// In MacOS X, tell GLFW to include the modern OpenGL headers.
// Windows does not want this, so we make this Mac-only.
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif

// In Linux, tell GLFW to include the modern OpenGL functions.
// Windows does not want this, so we make this Linux-only.
#ifdef __linux__
#define GL_GLEXT_PROTOTYPES
#endif

// GLFW 3.x, to handle the OpenGL window
#include <GLFW/glfw3.h>

// Windows installations usually lack an up-to-date OpenGL extension header,
// so make sure to supply your own, or at least make sure it's of a recent date.
#ifdef __WIN32__
#include <GL/glext.h>
#endif

// Headers for the other source files that make up this program.
#include "Texture.hpp"
#include "Rotator.hpp"
#include "Segment.h"
#include "Element.h"

/*
 * setupViewport() - set up the OpenGL viewport.
 * This should be done for each frame, to handle window resizing.
 * The "proper" way would be to set a "resize callback function"
 * using glfwSetWindowSizeCallback() and do these few operations
 * only when something changes, but let's keep it simple.
 * Besides, we want to change P when the aspect ratio changes.
 * A callback function would require P to be changed indirectly
 * in some manner, which is somewhat awkward in this case.
 */

//Function to create a 4x4 perspective matrix
void mat4perspective(float M[], float vfov, float aspect, float znear, float zfar);

void setupViewport(GLFWwindow *window, GLfloat *P);

float moveRightOnce(float xPos);
float moveLeftOnce(float xPos);


/*
 * main(argc, argv) - the standard C entry point for the program
 */
int main(int argc, char *argv[]) {

	TriangleSoup player;
    Texture earthTexture;
    Shader shader;

 	GLint location_time, location_MV, location_P, location_tex; // Shader uniforms
    float time;
	double fps = 0.0;

    MatrixStack MVstack; // The matrix stack we are going to use to set MV

    const GLFWvidmode *vidmode;  // GLFW struct to hold information about the display
	GLFWwindow *window;    // GLFW struct to hold information about the window

    // Initialise GLFW
    glfwInit();

    // Determine the desktop size
    vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	// Make sure we are getting a GL context of at least version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Exclude old legacy cruft from the context. We don't need it, and we don't want it.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Open a square window (aspect 1:1) to fill half the screen height
    window = glfwCreateWindow(vidmode->width/2, vidmode->height/2, "GLprimer", NULL, NULL);
    if (!window)
    {
        glfwTerminate(); // No window was opened, so we can't continue in any useful way
        return -1;
    }

    // Make the newly created window the "current context" for OpenGL
    // (This step is strictly required, or things will simply not work)
    glfwMakeContextCurrent(window);

    // Load the extensions for GLSL - note that this has to be done
    // *after* the window has been opened, or we won't have a GL context
    // to query for those extensions and connect to instances of them.
    tnm061::loadExtensions();

    printf("GL vendor:       %s\n", glGetString(GL_VENDOR));
    printf("GL renderer:     %s\n", glGetString(GL_RENDERER));
    printf("GL version:      %s\n", glGetString(GL_VERSION));
    printf("Desktop size:    %d x %d pixels\n", vidmode->width, vidmode->height);

    glfwSwapInterval(0); // Do not wait for screen refresh between frames

	// Perspective projection matrix
    GLfloat P[16];
    float aspectRatio = (vidmode->width)/(vidmode->height);

    //Create perspective matrix with fov = 1 rad, aspect = 1, znear = 3 and zfar = 10.
	mat4perspective(P, 1.0f, aspectRatio, 3.0f, 10.0f);

    // Intialize the matrix to an identity transformation
    MVstack.init();

	// Create geometry for rendering
	player.createSphere(0.7, 30);
	//player.readOBJ("meshes/trex.obj");    //If we want a more fancy mesh for the player

	// soupReadOBJ(&myShape, MESHFILENAME);
	player.printInfo();

	// Create a shader program object from GLSL code in two files
    
    #ifdef __WIN32__
	shader.createShader("vertexshader.glsl", "fragmentshader.glsl");
<<<<<<< HEAD


	glEnable(GL_TEXTURE_2D);

=======
    
    glEnable(GL_TEXTURE_2D);
    // Read the texture data from file and upload it to the GPU
    earthTexture.createTexture("textures/earth.tga");
    #endif
    
    #ifdef __APPLE__
    shader.createShader("/Users/olasteen/GitHub/TNM061---OpenGL-projekt/ballin/vertexshader.glsl", "/Users/olasteen/GitHub/TNM061---OpenGL-projekt/ballin/fragmentshader.glsl");
    
    glEnable(GL_TEXTURE_2D);
>>>>>>> origin/master
    // Read the texture data from file and upload it to the GPU
    earthTexture.createTexture("/Users/olasteen/GitHub/TNM061---OpenGL-projekt/ballin/textures/earth.tga");
    #endif

	location_MV = glGetUniformLocation( shader.programID, "MV" );
	location_P = glGetUniformLocation( shader.programID, "P" );
	location_time = glGetUniformLocation( shader.programID, "time" );
	location_tex = glGetUniformLocation( shader.programID, "tex" );

    int i = 0;
    float maxHeight = 0.0f;

    //Staring position of the player
    float transX = 0.0f;
    float transY = 0.0f;
    float transZ = 0.0f;

    // Main loop
    while(!glfwWindowShouldClose(window))
    {
        // Calculate and update the frames per second (FPS) display
        fps = tnm061::displayFPS(window);

		// Set the clear color and depth, and clear the buffers for drawing
        glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST); // Use the Z buffer
		glEnable(GL_CULL_FACE);  // Use back face culling
		glCullFace(GL_BACK);

        // Set up the viewport
        setupViewport(window, P);

		// Handle keyboard input
        if(glfwGetKey(window, GLFW_KEY_RIGHT))
            {
                transX = moveRightOnce(transX);
            }
        if(glfwGetKey(window, GLFW_KEY_LEFT))
            {
                transX = moveLeftOnce(transX);
            }
        if(glfwGetKey(window, GLFW_KEY_UP))
            {
                transY = 0.005f;
            }

		// Activate our shader program.
		glUseProgram( shader.programID );

        // Copy the projection matrix P into the shader.
		glUniformMatrix4fv( location_P, 1, GL_FALSE, P );

        // Tell the shader to use texture unit 0.
		glUniform1i ( location_tex , 0);

		// Update the uniform time variable.
		time = (float)glfwGetTime(); // Needed later as well
        glUniform1f( location_time, time );

        // Draw the scene
        MVstack.push(); // Save the initial, untouched matrix

            // Modify MV according to user input
            // First, do the view transformations ("camera motion")
            MVstack.translate(0.0f, -0.5f, -5.0f);
            MVstack.rotX(M_PI/6);

            // Then, do the model transformations ("object motion")
            MVstack.push(); // Save the current matrix on the stack

                // Ball
                //MVstack.rotX(time);
                MVstack.rotX(-M_PI/2); // Orient the poles along Y axis instead of Z
                MVstack.scale(0.5f); // Scale player
                MVstack.translate(transX, transY, transZ);
                // Update the transformation matrix in the shader
                glUniformMatrix4fv( location_MV, 1, GL_FALSE, MVstack.getCurrentMatrix() );
                // Render the geometry to draw the sun
                glBindTexture(GL_TEXTURE_2D, earthTexture.texID);
                player.render();

            MVstack.pop(); // Restore the matrix we saved above

        MVstack.pop(); // Restore the initial, untouched matrix

		// Play nice and deactivate the shader program
		glUseProgram(0);

		// Swap buffers, i.e. display the image and prepare for next frame.
        glfwSwapBuffers(window);

		// Poll events (read keyboard and mouse input)
		glfwPollEvents();

        // Exit if the ESC key is pressed (and also if the window is closed).
        if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
          glfwSetWindowShouldClose(window, GL_TRUE);
        }

    }

    // Close the OpenGL window and terminate GLFW.
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

/*--------- FUNCTION DEFINITIONS -----------------------*/

//vfov is the vertical field of view (in the y direction)
//aspect is the aspect ratio of the viewport (width/height)
//znear is the distance to near clip plane (znear > 0)
//zfar is the distance to the far clip plane (zfar > znear)
void mat4perspective(float M[], float vfov, float aspect, float znear, float zfar){

    float f = 1/tan(vfov/2); //cot(vfov/2)
    float A = -(zfar+znear)/(zfar-znear);
    float B = -(2*znear*zfar)/(zfar-znear);

    M[0] = f/aspect; M[4] = 0; M[8]  = 0;  M[12] = 0;
    M[1] = 0;        M[5] = f; M[9]  = 0;  M[13] = 0;
    M[2] = 0;        M[6] = 0; M[10] = A;  M[14] = B;
    M[3] = 0;        M[7] = 0; M[11] = -1; M[15] = 0;
}

void setupViewport(GLFWwindow *window, GLfloat *P) {

    int width, height;

    // Get window size. It may start out different from the requested
    // size, and will change if the user resizes the window.
    glfwGetWindowSize( window, &width, &height );

    // Ugly hack: adjust perspective matrix for non-square aspect ratios
    P[0] = P[5]*height/width;

    // Set viewport. This is the pixel rectangle we want to draw into.
    glViewport( 0, 0, width, height ); // The entire window
}

/* Testing movement */
float moveRightOnce(float xPos)
{
    bool once = true;

    while(once) //Loop to only move the object once
    {
        if(xPos < -1.0f)
            xPos = 0.0f;
        else if(xPos > 1.0f)
            xPos = xPos;
        else
            xPos = 5.0f;

        once = false;
    }
    return xPos;
}

float moveLeftOnce(float xPos)
{
    bool once = true;

    while(once) //Loop to only move the object once
    {
        once = false;

        if(xPos < 0.0f)
            xPos = xPos;
        else if(xPos > 0.0f)
            xPos = 0.0f;
        else
            xPos = -5.0f;


    }
    return xPos;
}
