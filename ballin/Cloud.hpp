#include "Element.h"
#include <ctime>
#include <chrono>
#include <random>
#include <cmath>
#include "particle.hpp"
class Cloud
{
    public:

    Cloud();
    //renders the particles.
    void renderParticles(MatrixStack &MV, GLint& location_MV, GLuint& texture,GLFWwindow *window);


    private:
     //set the "box" which the particles are allowed to be in
    void handleBox(int i ,int maxX ,int maxY ,int maxZ);
    //handle key input
    void keyHandler(GLFWwindow *window);
    //max amount of particles.
    static const int maxParticles = 250;
    //the amount of particles in an array.
    particle *particleCount[maxParticles];
    //used for calculating elapsed time.
    float lastT;
    //calculate delta time
    float elapsedTime();
        //update the particles
    void updateParticles(float dtX ,float dtY ,float dtZ);
    //initlalize stuff.
    void randomizeParticles();


};
