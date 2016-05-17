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

        void render(MatrixStack& p, GLint& location_MV, GLuint& texture, GLuint& normal);
        void changeZPos(float posChange);
        void setZPos(float pos);
        float getLength();
        void randomize();           //A function to rescale the blocks in the segment (randomly)
        void shorten();             //Enable shorter segments, to increase difficulty

        float* getCollisionData(); //Returns array with [xPos, yPos, zPos, zsize, ysize,zsize]
                                        //LENGTH OF OBJECT IS zsize * 2;

        float* getBoundaries(); //returns lower and upper bounderies
        void performAction(bool& gameOver);

        //Block dimensions
        static const float xsize;
        static const float ysize;

    protected:

    private:
        //Array with three blocks of class TriangleSoup
        TriangleSoup Blocks[3];
        float zsize[3];
        float zDif[3];
        float zMax;
        float segmentMax;
        float segmentMin;

};

#endif // SEGMENT_H
