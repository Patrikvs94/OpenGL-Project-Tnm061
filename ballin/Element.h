#ifndef ELEMENT_H
#define ELEMENT_H

#include "TriangleSoup.hpp"
#include "matrixStack.hpp"
#include "Shader.hpp"

class Element
{
    public:
        Element();
        virtual ~Element();


    protected:
        //The distance between two lanes
        static const int laneMargin = 3.0f;

    private:
};

#endif // ELEMENT_H
