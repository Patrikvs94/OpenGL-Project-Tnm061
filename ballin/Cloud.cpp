#include "Cloud.hpp"

Cloud::Cloud()
{
    //initialize lastTime
    lastT = (float) glfwGetTime();
    //randomize the particle positions
    randomizeParticles();
}

Cloud::~Cloud()
{
    for(int i=0; i<maxParticles; ++i)
    {
        delete particleCount[i];
    }
}

void Cloud::handleBox(int i ,int maxX ,int maxY ,int maxZ)
{
        if(particleCount[i]->xPos >= maxX)
        {
            particleCount[i]->xPos = 20 * ((float)rand()) / (float)RAND_MAX - 10;
            particleCount[i]->yPos = 20 * ((float)rand()) / (float)RAND_MAX  - 10;
            particleCount[i]->zPos = 4 * ((float)rand()) / (float)RAND_MAX - 2;
        }
        //if it goes over maxY randomize the position of the particle
        if(particleCount[i]->yPos >= maxY)
        {
            particleCount[i]->xPos = 20 * ((float)rand()) / (float)RAND_MAX - 10;
            particleCount[i]->yPos = 20 * ((float)rand()) / (float)RAND_MAX  - 10;
            particleCount[i]->zPos = 4 * ((float)rand()) / (float)RAND_MAX - 2;
        }
        if(particleCount[i]->zPos >= maxZ)
        {
            particleCount[i]->xPos = 20 * ((float)rand()) / (float)RAND_MAX - 10;
            particleCount[i]->yPos = 20 * ((float)rand()) / (float)RAND_MAX  - 10;
            particleCount[i]->zPos = 4 * ((float)rand()) / (float)RAND_MAX - 2;
        }
}

//calculate delta time, pretty self explanatory code
float Cloud::elapsedTime()
{

	float currentT, elapsedT;

	currentT = (float) glfwGetTime();
	elapsedT = currentT - lastT;
	lastT = currentT;

	return elapsedT;

}

void Cloud::randomizeParticles()
{
    //init seed
    srand(time(NULL));
    for(int i = 0; i < maxParticles; i++)
    {
        particleCount[i] = new particle;
        //set the positions with a certain distribution

        particleCount[i]->xPos = 20 * ((float)rand()) / (float)RAND_MAX - 10;
        particleCount[i]->yPos = 20 * ((float)rand()) / (float)RAND_MAX  - 10;
        particleCount[i]->zPos = 4 * ((float)rand()) / (float)RAND_MAX - 2;
        //randomize the colors of the particles.
        particleCount[i]->xCol = ((float)rand()) / (float)RAND_MAX;
        particleCount[i]->yCol = ((float)rand()) / (float)RAND_MAX;
        particleCount[i]->zCol = ((float)rand()) / (float)RAND_MAX;
        //create a pixel
        particleCount[i]->createParticle();
    }


}
void Cloud::updateParticles(float dtX ,float dtY ,float dtZ) //dt = deltatime
{
    for(int i = 0; i < maxParticles; i++)
    {
        //set temporary positions
        float xTemp = particleCount[i]->xPos;
        float yTemp = particleCount[i]->yPos;
        float zTemp = particleCount[i]->zPos;
        //save the old color values
        float xColTemp = particleCount[i]->xCol;
        float yColTemp = particleCount[i]->yCol;
        float zColTemp = particleCount[i]->zCol;
        //delete the life of the old particles
        delete particleCount[i];
        //create a new particle
        particleCount[i] = new particle;
        //move the new particle
        particleCount[i]->xPos = xTemp + dtX;
        particleCount[i]->yPos = yTemp + dtY;
        particleCount[i]->zPos = zTemp + dtZ;
        //set the new color values ( which are the saved ones)
        particleCount[i]->xCol = xColTemp;
        particleCount[i]->yCol = yColTemp;
        particleCount[i]->zCol = zColTemp;
        particleCount[i]->createParticle();
    }
}

void Cloud::renderParticles(MatrixStack &MV, GLint& location_MV)
{


    MV.push(); //save the current matrix.

    /* ----- Render code -----*/

    //update the uniform value
    glUniformMatrix4fv(location_MV, 1, GL_FALSE, MV.getCurrentMatrix());
    for(int i = 0; i < maxParticles; i++)
    {
     //push current pixel
     MV.push();
        //if it goes over x = 10, y = 10, z = 4, randomize them again
        handleBox(i, 4, 10, 4);

     //render the pixel
     particleCount[i]->render();

     MV.pop();

    }
    //kill and update particle position, dont do this in the rendering loop!!
    updateParticles(0.0f, 0.0f, 10*elapsedTime());

    MV.pop(); //restore init matrix.
}

