#include "util.h"

util::util()
{

}

util::util(std::vector<Segment*>* segmentVector)//, std::vector<TriangleSoup>* obstacleVector)
{
    init(segmentVector);

}

//Sort collision vectors on constructor call
void util::init(std::vector<Segment*>* segmentVector)
{
    for(int i = 0; i < segmentVector->size(); ++i)
    {
        collisionSegments.push_back(segmentVector->at(i));
    }
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


