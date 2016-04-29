#include "util.h"
#include <typeinfo>
#include <iostream>

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

bool util::checkCollision(Player* player, Element* object)
{
    //FETASTE DEBUG
    std::cout << typeid(object).name() << std::endl;
}

void util::updateCollisionVector()
{
    Segment* temp = collisionSegments.at(0);
    for(int i = 1; i < collisionSegments.size(); ++i)
    {
        collisionSegments.at(i-1) = collisionSegments.at(i);
    }
    collisionSegments.at(collisionSegments.size()-1) = temp;
}


