#ifndef SEGMENT_H
#define SEGMENT_H

#include "Element.h"
#include "TriangleSoup.hpp"
#include "matrixStack.hpp"
#include "Shader.hpp"

class Segment : public Element
{
    public:

        Segment();

        bool visible();             //Checks if the segment can be seen in viewport
        void moveToBack(float z);   //Moves the segment to the back of the line
        void reInit();              //Fixes a new version of the segment

        void render(MatrixStack* p, Shader* shader);
        void localTranslate(MatrixStack* p);

    protected:

    private:
        //Array with three blocks of class TriangleSoup
        TriangleSoup Blocks[3];

        //Block dimensions
        static const float xsize;
        static const float ysize;
        static const float zsize;
};

#endif // SEGMENT_H
