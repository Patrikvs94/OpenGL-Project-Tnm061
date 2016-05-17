#include "walls.h"

const float walls::xSize = 3.0f;
const float walls::ySize = 2.0f;
const float walls::zSize = 2.0f;
const float walls::span = 2.0f;
float walls::t = 0.0f;

walls::walls(float rp[3], float lp[3])
{
    rightWallOrigin = new float[3]{rp[0], rp[1], rp[2]};
    leftWallOrigin = new float[3]{lp[0], lp[1], lp[2]};
    srand(time(NULL));
    init();
}

void walls::init()
{
    for(int i = 0; i < rows; ++i)
    {
        for(int p = 0; p < cols; ++p)
        {
            rightWall.push_back(new wallBlock);
            leftWall.push_back(new wallBlock);
            int vecPos = rightWall.size()-1;

            rightWall.at(vecPos)->obj = new TriangleSoup();
            leftWall.at(vecPos)->obj = new TriangleSoup();
            rightWall.at(vecPos)->obj->createBox(xSize, ySize, zSize);
            leftWall.at(vecPos)->obj->createBox(xSize, ySize, zSize);
            rightWall.at(vecPos)->positions = new float[3]{rightWallOrigin[0] + randStartPos(), rightWallOrigin[1] + (i*2*ySize), rightWallOrigin[3] - (p*2*zSize)};
            leftWall.at(vecPos)->positions = new float[3]{leftWallOrigin[0] + randStartPos(), leftWallOrigin[1] + (i*2*ySize), leftWallOrigin[3] - (p*2*zSize)};

            //FULHACK FÖR ATT UNDVIKA DUBBLA LIKNANDE FUNKTIONER
            rightWall.at(vecPos)->velocity = randStartPos() * 2;
            leftWall.at(vecPos)->velocity = randStartPos() * 2;
        }
    }
}

float walls::randStartPos()
{
    return ((((float) rand()) / (float) RAND_MAX) - 0.5f) * span; //    -1 to 1
}

void walls::updateWalls(float dt)
{
    t += dt;
    for(int i = 0; i < rows; ++i)
    {
        for(int p = 0; p < cols; ++p)
        {
            rightWall.at((cols*i)+p)->positions[2] += (sin(rightWall.at((cols*i)+p)->velocity * t));
            leftWall.at((cols*i)+p)->positions[2] += (sin(leftWall.at((cols*i)+p)->velocity * t));
        }
    }
}
