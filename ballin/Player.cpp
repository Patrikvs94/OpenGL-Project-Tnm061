#include "Player.hpp"

Player::Player(float jump) : moveLength(laneMargin), jumpHeight(jump)
{
    mesh->createSphere(1.0, 30);
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

}
