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

        void render(MatrixStack& p, GLint& location_MV, GLuint& texture);
        void changeZPos(float posChange);
        float returnZ();

        //Block dimensions
        static const float xsize;
        static const float ysize;
        static const float zsize;

    protected:

    private:
        //Array with three blocks of class TriangleSoup
        TriangleSoup Blocks[3];



        float xPos;
        float yPos;
        float zPos;

        const float space = 2.0f;
};

#endif // SEGMENT_H
