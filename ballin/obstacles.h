#ifndef OBSTACLES_H
#define OBSTACLES_H

#include "Element.h"
#include "Segment.h"

#include<vector>
#include<ctime>
#include<random>
#include<cmath>
#include<iostream>

struct item{
    TriangleSoup* pillar;
    float* positions;
    float* hitBoxSize;
    ~item()
    {
        delete pillar;
        delete positions;
        delete hitBoxSize;
    }
};

class obstacles : public Element
{
    public:
        obstacles();
        obstacles(std::vector<Segment*>& segmentVector);
        void updatePositon(float zChange);
        void render(MatrixStack& p, GLint& location_MV, GLuint& texture, GLuint& normal);
        void reInit();
        void countDown(float dt);

    protected:
    private:
        static bool goodToGo;
        static float t;
        static const float xSize;
        static const float ySize;
        static const float zSize;
        static std::vector<Segment*>* segVec;
        static const float threshold;
        static const float zNear;

        static int maxNumber;
        std::vector<item*> items;

        void performAction(bool& gameOver);
        float* getCollisionData();
        int randPos();
        void checkAndMove();
        void createPillar(int segVecIndex);
};

#endif // OBSTACLES_H
