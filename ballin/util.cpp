#include "util.h"
#include <typeinfo>
#include <iostream>

util::util()
{

}

util::util(Player* p, std::vector<Segment*>* segmentVector)//, std::vector<TriangleSoup>* obstacleVector)
{
    player = p;
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

/*
std::vector<std::vector<Element*>> util::sendToCheck()
{

    //Check Element-arrays and the return objects
        //this will return arrays in arrays (due to obsticels and collectables)

    //CREATE VECTORS
    std::vector<Element*> tempSeg;
    //std::vector<Element*> tempObst;
    //std::vector<Element*> tempCollect;

    std::vector<std::vector<Element*>> returnVec;

    Segment* s1 = collisionSegments.at(0);
    Segment* s2 = collisionSegments.at(1);
    //Kolla antalet som behövs för collectable and obstacle

    tempSeg.push_back(s1);
    tempSeg.push_back(s2);

    returnVec.push_back(tempSeg);

    //RETURNS ARRAY OF ALL TO BE CHECKED
    return returnVec;



}
*/

std::vector<Element*> util::sendToCheck()
{
    std::vector<Element*> abc;
    return abc;
}


bool util::checkCollision()
{
    //Calls sendToCheck
    //THIS WILL CHECK COLLISION
        //THIS IS CALLED FROM CILLISION FUNCTION IN ELEMTNS SUBCLASSES

    return true;
}

void util::updateCollisionVectors()
{
    Segment* temp = collisionSegments.at(0);
    for(int i = 1; i < collisionSegments.size(); ++i)
    {
        collisionSegments.at(i-1) = collisionSegments.at(i);
    }
    collisionSegments.at(collisionSegments.size()-1) = temp;

    //CHECK COLLECTABLES VEC AND OBSTICLE VEC
}

