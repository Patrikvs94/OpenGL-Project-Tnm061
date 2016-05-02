#include "Player.hpp"
#include <iostream>

Player::Player() : moveLength(laneMargin), jumpHeight(2.0)
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
float Player::jump(float yPos)
{
    if(yPos!=jumpHeight)
    {
        yPos+=jumpHeight;
    }
    return yPos;
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
