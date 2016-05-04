#include "Segment.h"
#include <iostream>


const float Segment::xsize = 1.0f;  //Note: Same as the radius of the player
const float Segment::ysize = 0.2f;
const float Segment::segmentMax = 5*xsize;
const float Segment::segmentMin = xsize;


Segment::Segment(): Element(0.0f,0.0f,0.0f)
{
    zMax=0.0f;
    for(int i=0;i<3;++i)
    {
        //Create 3 blocks with random lengths
        zsize[i] = (((float) rand()) / (float) RAND_MAX)*(segmentMax-segmentMin) + segmentMin;
        Blocks[i].createBox(xsize, ysize, zsize[i]);
        std::cout << zsize[i] << std::endl;
        if(zsize[i]>zMax)
        {
            zMax=zsize[i];
        }
    }
    for(int i=0;i<3;++i)
    {
        zDif[i]= (((float) rand()) / (float) RAND_MAX)*2*(zMax-zsize[i]) - (zMax-zsize[i]);
    }

}

//take shader and matrixstack and render entire segment
void Segment::render(MatrixStack& p, GLint& location_MV, GLuint& texture)
{
    p.push(); //Save the current matrix before performing multiplications

        p.translate(0.0f, -xsize, 0.0f); //Lower the segment
    
        p.translate(-laneMargin, 0.0f, 0.0f);
        glUniformMatrix4fv( location_MV, 1, GL_FALSE, p.getCurrentMatrix() );
        glBindTexture(GL_TEXTURE_2D, texture);
        Blocks[0].render(); //Draw the block

        p.translate(laneMargin, 0.0f, 0.0f);
        glUniformMatrix4fv( location_MV, 1, GL_FALSE, p.getCurrentMatrix() );
        Blocks[1].render(); //Draw the block

        p.translate(laneMargin, 0.0f, 0.0f);
        glUniformMatrix4fv( location_MV, 1, GL_FALSE, p.getCurrentMatrix() );
        Blocks[2].render(); //Draw the block

    p.pop(); //Restore the initial matrix
}
void Segment::changeZPos(float posChange)
{
    zPos += posChange;
}

void Segment::setZPos(float pos)
{
    zPos=pos;
}

float* Segment::getCollisionData()
{
    float* dataArray = new float[8] {xPos, yPos, zPos, xsize, ysize, zsize[0], zsize[1], zsize[2]};
    return dataArray;
}

float Segment::getLength()
{
    return zMax;
}


