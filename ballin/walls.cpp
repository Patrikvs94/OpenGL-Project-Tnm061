#include "walls.h"
#include<iostream>

const float walls::xSize = 1.5f;
const float walls::ySize = 1.5f;
const float walls::zSize = 1.5f;
const float walls::span = 0.5f;
const float walls::scaler = 0.5f;
float walls::t = 0.0f;

walls::walls(float rp[3], float lp[3], float gs)
{
    gameSpeed = gs;
    rightWallOrigin = new float[3]{rp[0], rp[1], rp[2]};
    leftWallOrigin = new float[3]{lp[0], lp[1], lp[2]};
    srand(time(NULL));
    init();
}

walls::~walls()
{
    for(int i=0;i<rightWall.size();++i)
    {
        delete rightWall.at(i)->obj;
        delete rightWall.at(i)->positions;
        delete rightWall.at(i);
    }

    for(int i=0;i<leftWall.size();++i)
    {
        delete leftWall.at(i)->obj;
        delete leftWall.at(i)->positions;
        delete leftWall.at(i);
    }
}

void walls::init()
{
    for(int i = 0; i < rows; ++i)
    {
        for(int p = 0; p < cols; ++p)
        {
            rightWall.push_back(new wallBlock);
            leftWall.push_back(new wallBlock);
            int vecPos = rightWall.size()-1;

            rightWall.at(vecPos)->obj = new TriangleSoup();
            leftWall.at(vecPos)->obj = new TriangleSoup();
            rightWall.at(vecPos)->obj->createBox(xSize, ySize, zSize);
            leftWall.at(vecPos)->obj->createBox(xSize, ySize, zSize);
            rightWall.at(vecPos)->positions = new float[3]{rightWallOrigin[0] + randStartPos()-xSize, rightWallOrigin[1] + (i*2*ySize)-ySize, rightWallOrigin[2] - (p*2*zSize) - zSize};
            leftWall.at(vecPos)->positions = new float[3]{leftWallOrigin[0] + randStartPos()+xSize, leftWallOrigin[1] + (i*2*ySize)-ySize, leftWallOrigin[2] - (p*2*zSize) - zSize};

            //FULHACK FÖR ATT UNDVIKA DUBBLA LIKNANDE FUNKTIONER
            rightWall.at(vecPos)->velocity = randStartPos() * gameSpeed;
            leftWall.at(vecPos)->velocity = randStartPos() * gameSpeed;
        }
    }
}

float walls::randStartPos()
{
    return ((((float) rand()) / (float) RAND_MAX) - 0.5f) * span; //    -1 to 1
}

void walls::updateWalls(float dt)
{
    t += dt;
    for(int i = 0; i < rows; ++i)
    {
        for(int p = 0; p < cols; ++p)
        {
            rightWall.at((cols*i)+p)->positions[0] = rightWallOrigin[0] + (scaler*sin(rightWall.at((cols*i)+p)->velocity * t));
            leftWall.at((cols*i)+p)->positions[0] = leftWallOrigin[0] + (scaler*sin(leftWall.at((cols*i)+p)->velocity * t));

            rightWall.at((cols*i)+p)->positions[2] += gameSpeed*dt;
            leftWall.at((cols*i)+p)->positions[2] += gameSpeed*dt;
        }
    }
    checkAndMove();
}

void walls::render(MatrixStack& inStack, GLint& location_MV, GLuint& texture, GLuint& normal, float dt)
{
    inStack.push();

    for(int i = 0; i < rows; ++i)
    {
        for(int p = 0; p < cols; ++p)
        {
            glBindTexture(GL_TEXTURE_2D, texture);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, normal);
            glActiveTexture(GL_TEXTURE0);

            inStack.push();
                inStack.translate(rightWall.at((cols*i)+p)->positions[0],rightWall.at((cols*i)+p)->positions[1],rightWall.at((cols*i)+p)->positions[2]);
                glUniformMatrix4fv(location_MV, 1, GL_FALSE, inStack.getCurrentMatrix());
                rightWall.at((cols*i)+p)->obj->render();
            inStack.pop();

            inStack.push();
                inStack.translate(leftWall.at((cols*i)+p)->positions[0],leftWall.at((cols*i)+p)->positions[1],leftWall.at((cols*i)+p)->positions[2]);
                glUniformMatrix4fv(location_MV, 1, GL_FALSE, inStack.getCurrentMatrix());
                leftWall.at((cols*i)+p)->obj->render();
            inStack.pop();
        }
    }

    inStack.pop();

    updateWalls(dt);
}

void walls::checkAndMove()
{
    if(rightWall.at(0)->positions[2] > 5.0f)
    {
        int c = 0;
        while(c < rows)
        {
            wallBlock *rT = rightWall.at(c*cols);
            wallBlock *lT = leftWall.at(c*cols);

            float rightNewPos = rT->positions[2] - cols*2*zSize;
            float leftNewPos = lT->positions[2] - cols*2*zSize;

            rightWall.erase(rightWall.begin() + (c*cols));
            leftWall.erase(leftWall.begin() + (c*cols));

            rightWall.insert(rightWall.begin() + (c*cols) + (cols-1), rT);
            leftWall.insert(leftWall.begin() + (c*cols) + (cols-1), lT);

            rightWall.at((c*cols) + cols-1)->positions[2] = rightNewPos;
            leftWall.at((c*cols) + cols-1)->positions[2] = leftNewPos;

            c++;
        }
    }
}
