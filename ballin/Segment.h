#ifndef SEGMENT_H
#define SEGMENT_H

#include "Element.h"

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
        void setZPos(float pos);

        float* getCollisionData(); //Returns array with [xPos, yPos, zPos, zsize]
                                        //LENGTH OF OBJECT IS zsize * 2;


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

};

#endif // SEGMENT_H
