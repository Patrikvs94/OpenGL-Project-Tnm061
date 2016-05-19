#include "obstacles.h"

const float obstacles::xSize = 1.0f;
const float obstacles::ySize = 10.0f;
const float obstacles::zSize = 1.0f;

obstacles::obstacles()
{

}

obstacles::obstacles(float x, float y, float z, std::vector<Segment*>& segmentVector)
{
    //HOLY SHIT FIX
    //segVec = &segmentVector;
    srand(time(NULL));
    init();
}

void obstacles::createObstacle()
{

}

void obstacles::updatePositon()
{

}

void obstacles::init()
{
    for(int i = 0; i < maxNumber; ++i)
    {
        if((((float) rand()) / (float) RAND_MAX) > 0.5f)
        {
            items.push_back(new item());
            items.at(items.size()-1)->pillar = new TriangleSoup();
            items.at(items.size()-1)->pillar->createBox(xSize, ySize, zSize);
            items.at(items.size()-1)->hitBozSize = new float[3]{xSize, ySize, zSize};
            items.at(items.size()-1)->positions = new float[3]{};
        }
    }
}

void obstacles::render()
{

}

float* obstacles::getCollisionData()
{

    return new float[12];
}

void obstacles::performAction(bool& gameOver)
{

}
