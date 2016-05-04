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
        void setZPos(float pos);
        float getLength();

        float* getCollisionData(); //Returns array with [xPos, yPos, zPos, zsize, ysize,zsize]
                                        //LENGTH OF OBJECT IS zsize * 2;


        //Block dimensions
        static const float xsize;
        static const float ysize;
    
        static const float segmentMax;
        static const float segmentMin;

    protected:

    private:
        //Array with three blocks of class TriangleSoup
        TriangleSoup Blocks[3];
        float zsize[3];
        float zDif[3];
        float zMax;

};


/*
    float* Segment::getBoundries()
    {
        float* boundries = new float[2]{getZ()-zMax, getZ()+zMax};  // [LOWER, UPPER]
        return boundries;
    }

*/

#endif // SEGMENT_H
