#ifndef ELEMENT_H
#define ELEMENT_H

#include "TriangleSoup.hpp"
#include "matrixStack.hpp"
#include "Shader.hpp"

class Element
{
    public:
        Element();
        Element(float x, float y, float z);
        virtual ~Element();
        virtual float* getCollisionData() = 0;

        float getX();
        float getY();
        float getZ();

    protected:
        //The distance between two lanes
        static const int laneMargin = 3.0f;

        float xPos;
        float yPos;
        float zPos;

    private:
};

#endif // ELEMENT_H
