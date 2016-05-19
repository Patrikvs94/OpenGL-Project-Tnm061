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
    float* hitBozSize;
};

class obstacles : public Element
{
    public:
        obstacles();
        obstacles(float x, float y, float z, std::vector<Segment*>& segmentVector);
    protected:
    private:
        static const float xSize;
        static const float ySize;
        static const float zSize;
        static std::vector<Segment*> segVec;

        static const int maxNumber = 10;
        std::vector<item*> items;

        void createObstacle();
        void updatePositon();
        void init();
        void performAction(bool& gameOver);
        float* getCollisionData();

        void render();
};

#endif // OBSTACLES_H
