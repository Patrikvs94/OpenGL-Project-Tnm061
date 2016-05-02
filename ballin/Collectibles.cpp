#include "Collectibles.h"
#include <iostream>

const float Collectibles::coinX = 0.5f;
const float Collectibles::coinY = 0.5f;
const float Collectibles::coinZ = 0.1f;

Collectibles::Collectibles()
{
    coin.createBox(coinX, coinY, coinZ);
}

float* Collectibles::getCollisionData()
{
    float* dataArray = new float [1];

    return dataArray;
}

void Collectibles::render(MatrixStack& p, GLint& location_MV, GLuint& texture)
{
    p.push(); //Save the current matrix before performing multiplications
        p.translate(-3.0f, 0.0f, 0.0f);
        p.rotY(M_PI/4*time);
        glUniformMatrix4fv( location_MV, 1, GL_FALSE, p.getCurrentMatrix() );
        glBindTexture(GL_TEXTURE_2D, texture);
        coin.render(); //Draw the player

    p.pop(); //Restore the initial matrix
}
