#include "Player.hpp"
#include <iostream>

const float Player::G = 9.82f;
const int Player::maxCharges = 2;
bool Player::DEBUG = false;

Player::Player(): Element(0.0f,0.0f,0.0f), moveLength(laneMargin), gravityMultiplier(2.0f)
{
    radius = 1.0f;
    mesh.createSphere(radius, 30);
    currentCharges = 0;
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
// "t"is the time the jump began
// "T" is the duration of the jump
void Player::jump(float t,float T)
{
    //"kastparabel" formeln.
     yPos = gravityMultiplier*G*T*0.5f*t - gravityMultiplier*G * t*t*0.5f;
    if(yPos < 0.0f)
    {
        yPos = 0.0f;
    }
}

void Player::render(MatrixStack& p, GLint& location_MV, GLuint& texture, float time, float speed, GLuint& normal)
{
    p.push(); //Save the current matrix before performing multiplications

        p.translate(xPos, yPos, zPos);
        p.rotX(-speed*time*0.7);
        p.rotY(M_PI/2);
        glUniformMatrix4fv( location_MV, 1, GL_FALSE, p.getCurrentMatrix() );
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, normal);
        glActiveTexture(GL_TEXTURE0);
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

void Player::performAction(bool& gameOver)
{

}

void Player::alignPlayer()
{
    //right
    if(std::abs(xPos-laneMargin)<0.5f)
    {
        xPos=laneMargin;
    }
    //middle
    else if(std::abs(xPos)<0.5f)
    {
        xPos=0.0f;
    }
    //left
    else if(std::abs(xPos+laneMargin)<0.5f)
    {
        xPos=-laneMargin;
    }
}

void Player::addCharge()
{
    if(currentCharges < maxCharges)
    {
        ++currentCharges;
        if(DEBUG)
        {
            std::cout << "Added, " << this->currentCharges << " charges left." << std::endl;
        }
    }
    else
    {
        if(DEBUG)
        {
            std::cout << "Full" << std::endl;
        }
    }
}

void Player::removeCharge()
{
    if(currentCharges > 0)
    {
        --currentCharges;
        if(DEBUG)
        {
            std::cout << "Removed, " << this->currentCharges << " charges left." << std::endl;
        }
    }
    else
    {
        if(DEBUG)
        {
            std::cout << "Empty" << std::endl;
        }
    }
}

bool Player::gotCharges()
{
    return (currentCharges > 0);
}

float Player::getRadius()
{
    return radius;
}

void Player::setDebugMode(bool flag)
{
    DEBUG = flag;
}
