#include "Player.hpp"
#include <iostream>

const float Player::G = 20.82f;

Player::Player(): Element(0.0f,0.0f,0.0f), moveLength(laneMargin), jumpHeight(2.0f)
{
    mesh.createSphere(1.0, 30);
    //mesh.readOBJ("meshes/trex.obj");    //If we want a more fancy mesh for the player

    //mesh.printInfo();     //Print out the vertex and triangle info, for debugging purposes
}

//Move the player one step to the right
void Player::moveRight(float t,float T) //WHAT DOES t and T mean???
{
    xPos += (laneMargin/ T) * t;
    angle += t;
    if(xPos > laneMargin)
    {
        xPos = laneMargin;
    }

}

//Move the player one step to the left
void Player::moveLeft(float t,float T)
{
    xPos -= (laneMargin / T) * t;
    angle -= t;

    if(xPos < -laneMargin)
    {
        xPos = -laneMargin;
    }
}

//Make a jump!
void Player::jump(float t,float T)
{
    //"kastparabel" formeln.
     yPos = G*T*0.5f*t - G * t*t*0.5f;
    if(yPos < 0.0f)
    {
        yPos = 0.0f;
    }
}

void Player::render(MatrixStack& p, GLint& location_MV, GLuint& texture, float time, float speed)
{
    p.push(); //Save the current matrix before performing multiplications

        p.translate(xPos, yPos, zPos);
        //p.rotZ(-5 * angle); //This does not quite work
        p.rotX(-speed*time*0.7);
        glUniformMatrix4fv( location_MV, 1, GL_FALSE, p.getCurrentMatrix() );
        glBindTexture(GL_TEXTURE_2D, texture);
        mesh.render(); //Draw the player

    p.pop(); //Restore the initial matrix
}

float* Player::getCollisionData()
{
    float* dataArray = new float[4]; //{return DATA
    return dataArray;
}

float Player::getAngle()
{
    return angle;
}

void Player::performeAction()
{


}
