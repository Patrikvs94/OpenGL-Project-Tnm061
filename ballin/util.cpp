#include "util.h"
#include <typeinfo>
#include <iostream>

util::util()
{

}

util::util(Player* p, std::vector<Segment*>* segmentVector, std::vector<Element*>* objects)//, std::vector<TriangleSoup>* obstacleVector)
{
    player = p;
    init(segmentVector, objects);
}

//Sort collision vectors on constructor call
void util::init(std::vector<Segment*>* segmentVector, std::vector<Element*>* elementVector)
{
    for(int i = 0; i < segmentVector->size(); ++i)
    {
        nodeVector.push_back(new node());
        nodeVector.at(i)->segment = segmentVector->at(i);

        for(int p = 0; p < elementVector->size(); ++p)
        {
            float objectZPos = elementVector->at(p)->getZ();
            //WE NEED A GET BOUNDRIES
            float boundries* = nodeVector.at(i)->segment->getBoundries();
            if(objectZPos>=boundries[0] && objectZPos<=boudries[1])
            {
                children.push_back(elementVector->at(p));
            }
        }
    }
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
    //CHECK COLLECTABLES VEC AND OBSTICLE VEC
}

