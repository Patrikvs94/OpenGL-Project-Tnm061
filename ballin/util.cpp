#include "util.h"

util::util()
{

}

util::util(std::vector<Segment>* segmentVector, std::vector<TriangleSoup>* obstacleVector)
{
    collisionSegments =  segmentVector;
    collisionObstacles = obstacleVector;

    init();

}

//Sort collision vectors on constructor call
void util::init()
{

}

//MIGHT BE REDUNDANT
void util::getRelevantObjects(TriangleSoup* refPoint)
{

}

bool util::checkCollision(float* player, float* object)
{


}

//TAKE IN WHATEVER
void util::updateCollisionVector()
{

}


