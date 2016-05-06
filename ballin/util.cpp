#include "util.h"
#include <typeinfo>
#include <iostream>

util::util()
{

}

util::util(Player& p, std::vector<Segment*>& segmentVector, std::vector<Element*>& objects)//, std::vector<TriangleSoup>* obstacleVector)
{
    player = &p;
    init(segmentVector, objects);
}

//Sort collision vectors on constructor call
void util::init(std::vector<Segment*>& segmentVector, std::vector<Element*>& elementVector)
{
    for(int i = 0; i < segmentVector.size(); ++i)
    {
        nodeVector.push_back(new node());
        nodeVector.at(i)->segment = segmentVector.at(i);

        for(int p = 0; p < elementVector.size(); ++p)
        {
            float objectZPos = elementVector.at(p)->getZ();
            float* boundaries = nodeVector.at(i)->segment->getBoundaries();
            if(objectZPos>=boundaries[0] && objectZPos<=boundaries[1])
            {
                nodeVector.at(i)->children.push_back(elementVector.at(p));
            }
        }
    }
}

//Kollar kollision mellan en player samt objekt i nodeVector
void util::checkCollision(bool jumpFlag)
{
    //std::cout << nodeVector.size() << std::endl;
    //KALLAR PÅ EN ACTION om kollision är sann
    if(!jumpFlag)
    {

        //{xPos, yPos, zPos, xsize, ysize, zsize[0], zsize[1], zsize[2], zDif[0], zDif[1], zDif[2], laneMargin}
        float playerPosX = player->getX();
        float playerPosZ = player->getZ();

        float* s1Boundaries = nodeVector.at(0)->segment->getCollisionData();
        float lanePositions [3] = {-s1Boundaries[11], 0.0f, s1Boundaries[11]};

        for(int i = 0; i < 3; ++i)
        {
            if(playerPosX == lanePositions[i] && !(playerPosZ <= (s1Boundaries[2] + s1Boundaries[8+i] + s1Boundaries[5+i]) && playerPosZ >= (s1Boundaries[2] + s1Boundaries[8+i] - s1Boundaries[5+i])))
            {
                std::cout << glfwGetTime() << std::endl;
                //nodeVector.front()->segment->performeAction();
                break;
            }
        }
    }
    else{
        std::cout << "JUMPING" << std::endl;
    }
}


void util::updateNodeVector(std::vector<Element*>& elementVector)
{
    //Lägger första noden längst bak
    node* tempNode = nodeVector.front();
    for(int i = 0; i < nodeVector.size()-1; ++i)
    {
        nodeVector.at(i) = nodeVector.at(i+1);
    }
    nodeVector.back() = tempNode;

    //Ta bort alla element i children då nya kan ha slumpgenererats
    nodeVector.back()->children.clear();

    //Kollar vilka nya objekt som ska appendas till children.
        //KAN FÖRBÄTTRAS (går igenom onödigt många, typ)
    for(int p = 0; p < elementVector.size(); ++p)
    {
        float objectZPos = elementVector.at(p)->getZ();
        float* boundaries = nodeVector.back()->segment->getBoundaries();
        if(objectZPos>=boundaries[0] && objectZPos<=boundaries[1])
        {
            nodeVector.back()->children.push_back(elementVector.at(p));
        }
    }

    //std::cout << "NodeVector: " << nodeVector.front()->segment << std::endl;
}

