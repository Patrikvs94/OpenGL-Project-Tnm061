#include "Player.hpp"
#include <iostream>

const float Player::G = 9.82f;

Player::Player(): Element(0.0f,0.0f,0.0f), moveLength(laneMargin), jumpHeight(2.0f)
{
    mesh.createSphere(1.0, 30);
}

//Move the player one step to the right
void Player::moveRight(float t,float T)
{
    xPos += (laneMargin/ T) * t;
    if(xPos > laneMargin)
    {
        xPos = laneMargin;
    }

}

//Move the player one step to the left
void Player::moveLeft(float t,float T)
{
    xPos -= (laneMargin / T) * t;
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
