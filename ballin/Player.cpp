#include "Player.hpp"
#include <iostream>

const float Player::G = 9.82f;

Player::Player() : moveLength(laneMargin), jumpHeight(2.0f)
{
    mesh.createSphere(1.0, 30);
}

//Move the player one step to the right
float Player::moveRight(float xPos)
{
    if(xPos!=moveLength)
    {
        xPos+=moveLength;
    }
    return xPos;
}

//Move the player one step to the left
float Player::moveLeft(float xPos)
{
    if(xPos!=-moveLength)
    {
        xPos-=moveLength;
    }
    return xPos;
}

//Make a jump!
float Player::jump(float t,float T)
{
    //"kastparabel" formeln.
    float ypos = G*T*0.5f*t - G * t*t*0.5f;
    if(ypos < 0.0f)
    {
        ypos = 0.0f;
    }
    return ypos;
}

void Player::render(MatrixStack& p, GLint& location_MV, GLuint& texture)
{
    p.push(); //Save the current matrix before performing multiplications

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
