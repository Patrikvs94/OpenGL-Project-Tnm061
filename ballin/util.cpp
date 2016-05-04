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
            float* boundaries = nodeVector.at(i)->segment->getBoundaries();
            if(objectZPos>=boundaries[0] && objectZPos<=boundaries[1])
            {
                nodeVector.at(i)->children.push_back(elementVector->at(p));
            }
        }
    }


}


void util::checkCollision()
{
    //std::cout << nodeVector.size() << std::endl;
}

void util::updateCollisionVectors()
{
    //CHECK COLLECTABLES VEC AND OBSTICLE VEC
}

