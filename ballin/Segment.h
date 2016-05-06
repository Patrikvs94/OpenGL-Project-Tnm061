#ifndef SEGMENT_H
#define SEGMENT_H

#include "Element.h"
#include <ctime>

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
        void randomize();

        float* getCollisionData(); //Returns array with [xPos, yPos, zPos, zsize, ysize,zsize]
                                        //LENGTH OF OBJECT IS zsize * 2;

        float* getBoundaries(); //returns lower and upper bounderies
        void performeAction();

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

#endif // SEGMENT_H
