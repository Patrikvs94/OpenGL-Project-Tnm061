#include "util.h"
#include <typeinfo>
#include <iostream>

util::util()
{
    std::cout << "util::util() - Default constructor should not be called." << std::endl;
}

util::util(Player& p, std::vector<Segment*>& segmentVector, std::vector<Collectibles*>& collVector, obstacles* ob)//, std::vector<TriangleSoup>* obstacleVector)
{
    player = &p;
    obs = ob;
    init(segmentVector, collVector);
}

util::~util()
{
    for(int i=0; i<nodeVector.size();++i)
    {
        delete nodeVector.at(i)->segment;
        for(int j=0;j<nodeVector.at(i)->children.size();++j)
        {
            delete nodeVector.at(i)->children.at(j);
        }
    }
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
            delete boundaries;
        }
        for(int q = 0; q < obs->items.size(); ++q)
        {
            float pillarZPos = obs->items.at(q)->positions[2];
            float* boundaries = nodeVector.at(i)->segment->getBoundaries();
            if(pillarZPos>=boundaries[0] && pillarZPos<=boundaries[1])
            {
                nodeVector.at(i)->pillar = obs->items.at(q);
            }
            delete boundaries;
        }
    }
    for(int i = 0; i < player->maxCharges; ++i)
    {
        chargesVector.push_back(new TriangleSoup());
        chargesVector.at(i)->createBox(0.4f,0.4f,0.01f);
    }
}

//Kollar kollision mellan en player samt objekt i nodeVector
void util::checkCollision(bool jumpFlag, bool& gameOver, bool& invincible)
{
    if(!jumpFlag && !invincible)
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
            nodeVector.at(index)->segment->performAction(gameOver);
        }
        delete s1Boundaries;

        commonCollision(invincible, q, gameOver);
    }
    else
    {
        int q = 0;
        float playerPosZ = player->getZ();
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
        commonCollision(invincible,q, gameOver);
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
    nodeVector.back()->pillar = nullptr;

    //Kollar vilka nya objekt som ska appendas till children.
    for(int p = 0; p < collVector.size(); ++p)
    {
        float objectZPos = collVector.at(p)->getZ();
        float* boundaries = nodeVector.back()->segment->getBoundaries();
        if(objectZPos>=boundaries[0] && objectZPos<=boundaries[1])
        {
            nodeVector.back()->children.push_back(collVector.at(p));
        }
        delete boundaries;
    }
    for(int q = 0; q < obs->items.size(); ++q)
    {
        float pillarZPos = obs->items.at(q)->positions[2];
        float* boundaries = nodeVector.back()->segment->getBoundaries();
        if(pillarZPos>=boundaries[0] && pillarZPos<=boundaries[1])
        {
            nodeVector.back()->pillar = obs->items.at(q);
        }
        delete boundaries;
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

//EFTERBLIVET pga tidsbrist + felimplementation av obstacles...
void util::commonCollision(bool& invincible, int nodeVectorIndex, bool& gameOver)
{
    if(!invincible)
    {
        if(nodeVector.at(nodeVectorIndex)->pillar != nullptr)
        {
            float* obsPositions = nodeVector.at(nodeVectorIndex)->pillar->positions;
            float* hitboxData = nodeVector.at(nodeVectorIndex)->pillar->hitBoxSize;

            float r = player->getRadius();
            float pp[3]{player->getX(), player->getY(), player->getZ()};

            if((pp[0]+r >= obsPositions[0]-hitboxData[0] && pp[0]-r <= obsPositions[0]+hitboxData[0]) && (pp[1]-r <= obsPositions[1]+hitboxData[1]) && (pp[2]-r <= obsPositions[2]+hitboxData[2]))
            {
                std::cout << "CALLED" << std::endl;
                obs->performAction(gameOver);
            }

        }
    }
}

void util::renderCharges(MatrixStack& p, GLint& location_MV, GLuint& texture, GLuint& normal)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, normal);
    glActiveTexture(GL_TEXTURE0);

    for(int i = 0; i < player->getCurrentCharges(); ++i)
    {
        p.push();
            p.translate(-7.8f + i*1.2f, 6.0f, -1.0f);
            p.rotX(-M_PI/9.0);
            glUniformMatrix4fv( location_MV, 1, GL_FALSE, p.getCurrentMatrix());
            chargesVector.at(i)->render();
        p.pop();
    }

}
