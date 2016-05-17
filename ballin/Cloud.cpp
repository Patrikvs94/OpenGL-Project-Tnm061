#include "Cloud.hpp"

Cloud::Cloud()
{
    //initialize lastTime
    lastT = (float) glfwGetTime();
    //randomize the particle positions
    randomizeParticles();
}
void Cloud::handleBox(int i ,int maxX ,int maxY ,int maxZ)
{
        if(particleCount[i]->xPos >= maxX) //10
        {
            particleCount[i]->xPos = 28 * ((float)rand()) / (float)RAND_MAX - 14;
            particleCount[i]->yPos = 20 * ((float)rand()) / (float)RAND_MAX  - 10;
            particleCount[i]->zPos = 4 * ((float)rand()) / (float)RAND_MAX - 2;
        }
        //if it goes over x = 8, randomize the position of the particle
        if(particleCount[i]->yPos >= maxY) //10
        {
            particleCount[i]->xPos = 28 * ((float)rand()) / (float)RAND_MAX - 14;
            particleCount[i]->yPos = 20 * ((float)rand()) / (float)RAND_MAX  - 10;
            particleCount[i]->zPos = 4 * ((float)rand()) / (float)RAND_MAX - 2;
        }
        if(particleCount[i]->zPos >= maxZ) //4
        {
            particleCount[i]->xPos = 28 * ((float)rand()) / (float)RAND_MAX - 14;
            particleCount[i]->yPos = 20 * ((float)rand()) / (float)RAND_MAX  - 10;
            particleCount[i]->zPos = 4 * ((float)rand()) / (float)RAND_MAX - 2;
        }
}
void Cloud::keyHandler(GLFWwindow *window)
{
        if(glfwGetKey(window, GLFW_KEY_RIGHT))
        {
        updateParticles(3*sin(-elapsedTime() * 2),0.0f, 0.0f);
        }
        if(glfwGetKey(window, GLFW_KEY_UP))
        {
        updateParticles(0.0f ,3*sin(elapsedTime() * 2), 0.0f);
        }
        if(glfwGetKey(window, GLFW_KEY_LEFT))
        {
        updateParticles(3*sin(elapsedTime() * 2),0.0f, 0.0f);
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
    srand(time(NULL));
    for(int i = 0; i < maxParticles; i++)
    {
        particleCount[i] = new particle;
        //set the positions with a certain distribution

        particleCount[i]->xPos = 28 * ((float)rand()) / (float)RAND_MAX - 14;
        particleCount[i]->yPos = 20 * ((float)rand()) / (float)RAND_MAX  - 10;
        particleCount[i]->zPos = 4 * ((float)rand()) / (float)RAND_MAX - 2;;

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
        //delete the life of the old particles
        delete particleCount[i];
        //create a new particle
        particleCount[i] = new particle;
        //move the new particle
        particleCount[i]->xPos = xTemp + dtX;
        particleCount[i]->yPos = yTemp + dtY;
        particleCount[i]->zPos = zTemp + dtZ;
        particleCount[i]->createParticle();
    }
}

void Cloud::renderParticles(MatrixStack &MV, GLint& location_MV, GLuint& texture,GLFWwindow *window)
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
        handleBox(i, 10, 10, 4);

      //bind the texture
     glBindTexture(GL_TEXTURE_2D, texture);
     //render the pixel
     particleCount[i]->render();

     MV.pop();

    }
    //kill and update particle position, dont do this in the rendering loop!!
    updateParticles(0.0f, 0.0f, 2*elapsedTime());
    keyHandler(window);

    MV.pop(); //restore init matrix.
}

