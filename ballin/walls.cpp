#include "walls.h"

const float walls::xSize = 3.0f;
const float walls::ySize = 2.0f;
const float walls::zSize = 2.0f;


walls::walls()
{
    srand(time(NULL));
    init();
}

void walls::init()
{
    for(int i = 0; i < rows; ++i)
    {
        for(int p = 0; p < cols; ++p)
        {

        }
    }
}

void walls::randStartPos()
{

}

void walls::updateWalls(double dt)
{

}
