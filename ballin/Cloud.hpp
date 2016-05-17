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
    void renderParticles(MatrixStack &MV, GLint& location_MV, GLuint& texture);
    //update the particles
    void updateParticles(float dtX ,float dtY ,float dtZ);

    private:
    //max amount of particles.
    static const int maxParticles = 250;
    //the amount of particles in an array.
    particle *particleCount[maxParticles];
    //used for calculating elapsed time.
    float lastT;
    //calculate delta time
    float elapsedTime();
    //initlalize stuff.
    void randomizeParticles();
    //set the "box" which the particles are allowed to be in
    void handleBox(int i ,int maxX ,int maxY ,int maxZ);

};
