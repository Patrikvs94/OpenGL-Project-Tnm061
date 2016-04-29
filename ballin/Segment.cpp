#include "Segment.h"
#include <iostream>

<<<<<<< HEAD
const float Segment::xsize = 1.0f;  //Note: Same as the radius of the player
const float Segment::ysize = 0.2f;
const float Segment::zsize = 4*xsize;
=======
const float Segment::xsize = 0.3f;
const float Segment::ysize = 0.1f;
const float Segment::zsize = 1.0f;

>>>>>>> origin/master

Segment::Segment()
{
    //Creating the 3 lanes with constant dimensions
    Blocks[0].createBox(xsize, ysize, zsize);
    Blocks[1].createBox(xsize, ysize, zsize);
    Blocks[2].createBox(xsize, ysize, zsize);

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

