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

//Do things based on the operative system
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
#include "Player.hpp"
#include "util.h"
#include "Collectibles.h"
#include "Cloud.hpp"
#include "walls.h"

#include <ctime>
#include <vector>

/* --- FUNCTION DECLARATIONS -------- */
//Function definitions and explanations is found in the bottom of this file.
void setupViewport(GLFWwindow *window, GLfloat *P);
void mat4perspective(float M[], float vfov, float aspect, float znear, float zfar);
void handleInput(Player &player, bool &lFlag, bool &rFlag, bool &jFlag, float horizontalTime, float jTime, float deltaTime, Cloud &t);


/* ------ MAIN FUNCTION --------------*/

int main(int argc, char *argv[]) {

    Texture earthTexture, segmentTexture,fireTexture, wallTexture;
    Texture segmentNormals, earthNormals, wallNormals;
    Shader shader, particleShader;

 	GLint location_time, location_MV, location_P, location_tex, location_norm, location_l_pos;; // Shader uniforms
    GLint Plocation_time, Plocation_MV, Plocation_P, Plocation_Color;
    float time = (float)glfwGetTime();
	double fps = 0.0;
	float gameSpeed = 10.0f;
    float T = 1.5f;         //Maximal time it can jump until it descends.
    float scaleTime = 0.15f;
    const int numberOfSegments = 7;
    float segmentDistance = 0.0f;

    //Variables used for animation
    double jumpTime       = glfwGetTime(); //when the player jumps
    double currentTime    = glfwGetTime(); // when the renderingloop repeats
    double horizontalTime = glfwGetTime(); // when the player moves left/right
    double deltaTime      = 0.0; // The time between the current and last frame
    double chargeTime     = glfwGetTime();

    bool jumpFlag  = false;
    bool leftFlag  = false;
    bool rightFlag = false;
    bool gameOver = false;
    bool invincible = true;

    MatrixStack MVstack; // The matrix stack we are going to use to set MV

    const GLFWvidmode *vidmode;  // GLFW struct to hold information about the display
	GLFWwindow *window;    // GLFW struct to hold information about the window

    std::vector<Segment*> Segments; // vector containing all the segments

    // Initialise GLFW
    glfwInit();

    // Determine the desktop size
    vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    // Make sure we are getting a GL context of at least version 3.3 and exclude
    // old and irrelevant content (we just put it in a void-function)
	//void getRelevantGlContent();
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

    //Create perspective matrix with fov = 1 rad, aspect = 1, znear = 3 and zfar = 75.
	mat4perspective(P, 1.0f, aspectRatio, 3.0f, 75.0f);

    // Intialize the matrix to an identity transformation
    MVstack.init();

    // Create a shader program object from GLSL code in two files
	shader.createShader("vertexshader.glsl", "fragmentshader.glsl");
    particleShader.createShader("vertexshader_particles.glsl", "fragmentshader_particles.glsl");

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST); // Use the Z buffer
    glEnable(GL_CULL_FACE);  // Use back face culling
    glCullFace(GL_BACK);


    // Read the texture data from file and upload it to the GPU
    earthTexture.createTexture("textures/energy.tga");
    earthNormals.createTexture("textures/red_norm.tga");
    segmentTexture.createTexture("textures/scifi.tga");
    segmentNormals.createTexture("textures/coble_norm.tga");
    fireTexture.createTexture("textures/fire.tga");
    wallTexture.createTexture("textures/brickwall.tga");
    wallNormals.createTexture("textures/brickwall_normal.tga");

	location_MV = glGetUniformLocation( shader.programID, "MV" );
	location_P = glGetUniformLocation( shader.programID, "P" );
	location_time = glGetUniformLocation( shader.programID, "time" );
	location_tex = glGetUniformLocation( shader.programID, "tex" );
    location_norm = glGetUniformLocation( shader.programID, "norm" );
    location_l_pos = glGetUniformLocation( shader.programID, "l_pos" );

    Plocation_MV = glGetUniformLocation( particleShader.programID, "MV" );
    Plocation_P = glGetUniformLocation( particleShader.programID, "P" );
    Plocation_time = glGetUniformLocation( particleShader.programID, "time" );


    // Declaring objects of type TriangleSoup after all GLFW nonsense is complete
    Cloud Particles;
    Player ballin;
    Collectibles coin;
    walls *demWalls;

    //Loop used for "initializing the Segment-vector"
    float zPosition= 0.0f;
    Segments.push_back(new Segment());
    for(int i = 1; i < numberOfSegments; i++)
    {
        Segments.push_back(new Segment());
        zPosition-=(Segments.at(i-1)->getLength()+Segments.at(i)->getLength()+segmentDistance);
        Segments.at(i)->changeZPos(zPosition);
    }

    //DEBUG FOR UTIL
    std::vector<Collectibles*> tempShit;
    util tempUtil(ballin, Segments, tempShit);

    //WALLS
    float rightOrigin[3]{-12.0f, -20.0f, 1.0f};
    float leftOrigin[3]{12.0f, -20.0f, 1.0f};
    demWalls = new walls(rightOrigin, leftOrigin);

    // Main loop
    while(!glfwWindowShouldClose(window) && !gameOver)
    {
        deltaTime   = glfwGetTime()-currentTime; //calculate time since last frame
        currentTime = glfwGetTime();

        if(glfwGetTime()-chargeTime > 5.0 && !jumpFlag)
        {
            ballin.addCharge();
            chargeTime=glfwGetTime();
        }

        if(glfwGetTime() > 1.0f) //we want the first segments to have no gaps
            segmentDistance = 1.0f;

        // Calculate and update the frames per second (FPS) display
        fps = tnm061::displayFPS(window);

		// Set the clear color and depth, and clear the buffers for drawing
        glClearColor(0.4, 0.4, 0.4, 1.0);       //Background color, should be the same as the fog!
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set up the viewport
        setupViewport(window, P);

		// Handle keyboard input (cannot press a key if the time since last press is less than 0,2 sec)
        if(glfwGetKey(window, GLFW_KEY_RIGHT) && !rightFlag && !leftFlag)
        {
            if(!jumpFlag)
            {
                horizontalTime = glfwGetTime();
                rightFlag = true;
            }
            else if((jumpFlag && ((glfwGetTime()-jumpTime )<(0.7*T-scaleTime*T)) && ballin.gotCharges()))
            {
                horizontalTime = glfwGetTime();
                rightFlag = true;
                ballin.removeCharge();
            }
        }
        if(glfwGetKey(window, GLFW_KEY_LEFT) && !leftFlag && !rightFlag)
        {
            if(!jumpFlag)
            {
                horizontalTime = glfwGetTime();
                leftFlag = true;
            }
            else if((jumpFlag && ((glfwGetTime()-jumpTime )<(0.7*T-scaleTime*T)) && ballin.gotCharges()))
            {
                horizontalTime = glfwGetTime();
                leftFlag = true;
                ballin.removeCharge();
            }
        }
        if(glfwGetKey(window, GLFW_KEY_UP) && jumpFlag == false)
        {
            jumpTime = glfwGetTime();
            jumpFlag = true;
        }

        //Do something based on the keyboard input (i.e. jump or move sideways)
        handleInput(ballin, leftFlag, rightFlag, jumpFlag, horizontalTime, jumpTime, deltaTime,Particles);

		// Activate our shader program.
		glUseProgram( particleShader.programID );

        // Copy the projection matrix P into the shader.
		glUniformMatrix4fv( Plocation_P, 1, GL_FALSE, P );


		// Update the uniform time variable.
		time = (float)glfwGetTime(); // Needed later as well
        glUniform1f( Plocation_time, time );

        // Draw the scene
        MVstack.push(); // Save the initial, untouched matrix

            // Modify MV according to user input
            // First, do the view transformations ("camera motion")
            MVstack.translate(0.0f, -2.0f, -10.0f);
            MVstack.rotX(M_PI/9);
            //render the particles
            Particles.renderParticles(MVstack,location_MV);
        glUseProgram(0);

        // Activate our shader program.
        glUseProgram( shader.programID );

        // Copy the projection matrix P into the shader.
        glUniformMatrix4fv( location_P, 1, GL_FALSE, P );

        // Tell the shader to use texture unit 0.
        glUniform1i ( location_tex , 0);
        glUniform1i ( location_norm , 1);

        // Update the uniform time variable.
        time = (float)glfwGetTime(); // Needed later as well
        glUniform1f( location_time, time );

            MVstack.push(); // Save the current matrix on the stack

            //We used the known int of 10 for testing purposes
            MVstack.push();

            //Sets z-coordinates for segments
            for(int i=0;i<Segments.size();++i)
            {
                Segments.at(i)->changeZPos(gameSpeed*(deltaTime));
            }

            //Moves the segment closest to the camera to the back if it reaches z=0
            if(Segments.at(0)->getZ()>10.0f)
            {
                Segment* temp = Segments.at(0);
                Segments.erase(Segments.begin());
                temp->reInit();
                temp->setZPos((Segments.at(Segments.size()-1)->getZ()) -(Segments.at(Segments.size()-1)->getLength() + temp->getLength() + segmentDistance));
                Segments.push_back(temp);
            }

            //render segments at correct positions
            for(int i = 0; i<Segments.size(); i++)
            {
                MVstack.push();
                MVstack.translate(0.0f, 0.0f, Segments.at(i)->getZ());
                Segments.at(i)->render(MVstack, location_MV, segmentTexture.texID,segmentNormals.texID);
                coin.render(MVstack, location_MV, earthTexture.texID);
                MVstack.pop();
            }

            MVstack.pop();

                // Render the player
                ballin.render(MVstack, location_MV, earthTexture.texID, time, gameSpeed, earthNormals.texID);
                demWalls->render(MVstack, location_MV, wallTexture.texID,wallNormals.texID, deltaTime);

            MVstack.pop(); // Restore the matrix we saved above

        MVstack.pop(); // Restore the initial, untouched matrix

        //COLLISION CHECKING
        if(glfwGetTime() >= 2.0)
        {
            tempUtil.checkCollision(jumpFlag, gameOver, invincible);
        }
        //tempUtil.logPlayerPosition(ballin, glfwGetTime(), gameSpeed);

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

    for(int i = 0; i < 20; ++i)
    {
        std::cout << "GAME OVER" << std::endl;
    }

    return 0;
}


/*--------- FUNCTION DEFINITIONS -----------------------*/

/*
 * Function to set up the OpenGL viewport
 *
 * This should be done for each frame, to handle window resizing.
 * The "proper" way would be to set a "resize callback function"
 * using glfwSetWindowSizeCallback() and do these few operations
 * only when something changes, but let's keep it simple.
 * Besides, we want to change P when the aspect ratio changes.
 * A callback function would require P to be changed indirectly
 * in some manner, which is somewhat awkward in this case.
 */
void setupViewport(GLFWwindow *window, GLfloat *P) {

    int width, height;

    // Get window size. It may start out different from the requested
    // size, and will change if the user resizes the window.
    glfwGetFramebufferSize( window, &width, &height );
    //glfwGetWindowSize( window, &width, &height );

    // Ugly hack: adjust perspective matrix for non-square aspect ratios
    P[0] = P[5]*height/width;

    // Set viewport. This is the pixel rectangle we want to draw into.
    glViewport( 0, 0, width, height ); // The entire window
}

//Function to create a 4x4 perspective matrix:
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

//Function to handle the keyboard input to create movement of the player
void handleInput(Player &player, bool &lFlag, bool &rFlag, bool &jFlag, float horizontalTime, float jTime, float deltaTime,Cloud &t)
{
    float T = 1.5f;         //Maximal time it can jump until it descends.
    float scaleTime = 0.15f;

        if(jFlag) //player jumps
        {
            player.jump(glfwGetTime()-jTime,0.5*T);

            if(player.getY() == 0.0f)
                jFlag = false;
        }

        if(rFlag && !lFlag) //player moves to the right
        {
            player.moveRight(deltaTime,scaleTime * T);
            if(!jFlag)
            {
                player.jump(glfwGetTime() - horizontalTime,scaleTime * T);
                t.updateParticles(deltaTime, 0.0f, 0.0f);
            }

            if((glfwGetTime() - horizontalTime) >= scaleTime * T)
            {
                rFlag = false;
                player.alignPlayer();
            }
        }

        if(lFlag && !rFlag) //player moves to the left
        {
            player.moveLeft(deltaTime,scaleTime * T);
            if(!jFlag)
            {
                player.jump(glfwGetTime() - horizontalTime,scaleTime * T);
                t.updateParticles(-deltaTime, 0.0f, 0.0f);
            }

            if((glfwGetTime() - horizontalTime) >= scaleTime * T)
            {
                lFlag = false;
                player.alignPlayer();
            }
        }
        if(jFlag && rFlag)
        {
            t.updateParticles(deltaTime, 0.0f, 0.0f);
        }
        if(jFlag && lFlag)
        {
            t.updateParticles(-deltaTime, 0.0f, 0.0f);
        }
}

