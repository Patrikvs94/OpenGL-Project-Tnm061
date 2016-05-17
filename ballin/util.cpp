#include "util.h"
#include <typeinfo>
#include <iostream>

util::util()
{
    std::cout << "util::util() - Default constructor should not be called." << std::endl;
}

util::util(Player& p, std::vector<Segment*>& segmentVector, std::vector<Collectibles*>& objects)//, std::vector<TriangleSoup>* obstacleVector)
{
    player = &p;
    init(segmentVector, objects);
}

//Sort collision vectors on constructor call
void util::init(std::vector<Segment*>& segmentVector, std::vector<Collectibles*>& collVector)
{
    for(int i = 0; i < segmentVector.size(); ++i)
    {
        nodeVector.push_back(new node());
        nodeVector.at(i)->segment = segmentVector.at(i);

        for(int p = 0; p < collVector.size(); ++p)
        {
            float objectZPos = collVector.at(p)->getZ();
            float* boundaries = nodeVector.at(i)->segment->getBoundaries();
            if(objectZPos>=boundaries[0] && objectZPos<=boundaries[1])
            {
                nodeVector.at(i)->children.push_back(collVector.at(p));
            }
        }
    }
}

//Kollar kollision mellan en player samt objekt i nodeVector
void util::checkCollision(bool jumpFlag, bool& gameOver, bool& invincible)
{
    if(!jumpFlag)
    {

        //{xPos, yPos, zPos, xsize, ysize, zsize[0], zsize[1], zsize[2], zDif[0], zDif[1], zDif[2], laneMargin}
        float playerPosX = player->getX();
        float playerPosZ = player->getZ();
        int q = 0;
        int index = 3;

        for(int i = 0; i < nodeVector.size(); ++i)
        {
            float* segBound = nodeVector.at(i)->segment->getBoundaries();
            if(playerPosZ <= segBound[1] && playerPosZ>= segBound[0])
            {
                q = i;
                break;
            }
            delete segBound;
        }

        float* s1Boundaries = nodeVector.at(q)->segment->getCollisionData();
        float lanePositions [3] = {-s1Boundaries[11], 0.0f, s1Boundaries[11]};

        for(int i = 0; i < 3; ++i)
        {
            if(playerPosX == lanePositions[i])
            {
                index = i;
            }
        }

        if(playerPosX == lanePositions[index] && !(playerPosZ <= (s1Boundaries[2] + s1Boundaries[8+index] + s1Boundaries[5+index]) && playerPosZ >= (s1Boundaries[2] + s1Boundaries[8+index] - s1Boundaries[5+index])))
        {
            if(!invincible)
            {
                nodeVector.at(index)->segment->performAction(gameOver);
            }
        }
        delete s1Boundaries;

    }
    else{
        //std::cout << "CHECK COLLISION WITH OTHER OBJECTS" << std::endl;
    }
}


void util::updateNodeVector(std::vector<Collectibles*>& collVector)
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
    for(int p = 0; p < collVector.size(); ++p)
    {
        float objectZPos = collVector.at(p)->getZ();
        float* boundaries = nodeVector.back()->segment->getBoundaries();
        if(objectZPos>=boundaries[0] && objectZPos<=boundaries[1])
        {
            nodeVector.back()->children.push_back(collVector.at(p));
        }
    }
}

void util::logPlayerPosition(Player& p, double t, float gameSpeed)
{
    double dt = t-deltaLogTime;
    if(dt >= (1.0/logRate))
    {
        deltaLogTime = t;
        if(positionData.empty())
        {
            positionData.push_back(new float[3] {p.getX(), p.getY() + p.getRadius(), p.getZ() + p.getRadius()});
        }
        else
        {
            if(positionData.size() == maxLogSize)
            {
                delete positionData.at(maxLogSize-1);
                positionData.erase(positionData.begin() + positionData.size()-1);
            }
            positionData.insert(positionData.begin(), new float[3] {p.getX(), p.getY() + p.getRadius(), p.getZ() + p.getRadius()});
            updateLogData(dt, gameSpeed);
        }
    }
}

void util::updateLogData(float dt, float gameSpeed)
{
    for(int i = 1; i < positionData.size(); ++i)
    {
        //index 2 holds z-values
        positionData.at(i)[2] *= (gameSpeed*dt);
    }
}
