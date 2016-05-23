#include "obstacles.h"

const float obstacles::xSize = 1.0f;
const float obstacles::ySize = 40.0f;
const float obstacles::zSize = 1.0f;
const float obstacles::threshold = 0.9f;
const float obstacles::zNear = 10.0f;
const float obstacles::spawnTime = 0.0f;
float obstacles::t = 0.0f;
int obstacles::maxNumber;
std::vector<Segment*>* obstacles::segVec;
bool obstacles::goodToGo = false;

obstacles::obstacles()
{

}

obstacles::obstacles(std::vector<Segment*>& segmentVector)
{
    segVec =& segmentVector;
    maxNumber = segVec->size();
    srand(time(NULL));
}

void obstacles::updatePositon(float zChange)
{
    for(int i = 0; i < items.size(); ++i)
    {
        items.at(i)->positions[2] += zChange;
    }
}

void obstacles::render(MatrixStack& p, GLint& location_MV, GLuint& texture, GLuint& normal)
{
    if(goodToGo)
    {
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, normal);
        glActiveTexture(GL_TEXTURE0);

        p.push();
            for(int i = 0; i < items.size(); ++i)
            {
                p.push();
                    p.translate(items.at(i)->positions[0], items.at(i)->positions[1], items.at(i)->positions[2]);
                    glUniformMatrix4fv( location_MV, 1, GL_FALSE, p.getCurrentMatrix() );
                    items.at(i)->pillar->render();
                p.pop();
            }
        p.pop();

        if(items.size() > 0)
        {
          checkAndMove();
        }
    }
}

float* obstacles::getCollisionData()
{

    return new float[12];
}

void obstacles::performAction(bool& gameOver)
{
    gameOver = true;
    //std::cout << "DEATH BY PILLAR @ " << glfwGetTime() << std::endl;
}

int obstacles::randPos()
{
    return (rand() % 3 - 1)*3;
}

void obstacles::checkAndMove()
{
    if(items.at(0)->positions[2] > zNear)
    {
        delete items.at(0);
        items.erase(items.begin());
    }
}

void obstacles::countDown(float dt)
{
    t +=dt;
    if(t > spawnTime && !goodToGo)
    {
        goodToGo = true;
    }
}

void obstacles::createPillar(int segVecIndex)
{
    items.push_back(new item());
    int place = items.size()-1;
    items.at(place)->pillar = new TriangleSoup();
    items.at(place)->pillar->createBox(xSize, ySize, zSize);
    items.at(place)->hitBoxSize = new float[3]{xSize, ySize, zSize};
    items.at(items.size()-1)->positions = new float[3]{(float)randPos(), 0.0f, segVec->at(segVecIndex)->getZ()};
    //items.at(items.size()-1)->positions = new float[3]{randPos(), segVec->at(segVecIndex)->getY() + ySize - segVec->at(segVecIndex)->xsize, segVec->at(segVecIndex)->getZ()};
}

void obstacles::reInit()    //CALLED WHEN SEGMENT CHANGES
{
    int i = segVec->size()-1;
    if((((float) rand()) / (float) RAND_MAX) > threshold)
    {
        createPillar(i);
    }
}

bool obstacles::checkGoodToGo()
{
    return goodToGo;
}
