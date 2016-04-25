#include "Segment.h"
#include <iostream>

const float Segment::xsize = 0.1f;
const float Segment::ysize = 0.1f;
const float Segment::zsize = 0.1f;


Segment::Segment()
{
    //Creating the 3 lanes with constant dimensions
    Blocks[0].createBox(xsize, ysize, zsize);
    Blocks[1].createBox(xsize, ysize, zsize);
    Blocks[2].createBox(xsize, ysize, zsize);


}

//take shader and matrixstack and render entire segment
void Segment::render(MatrixStack& p, GLint& location_MV)
{
    
    localTranslate(p);
    glUniformMatrix4fv( location_MV, 1, GL_FALSE, p.getCurrentMatrix() );
    Blocks[0].render();
    p.pop();
    glUniformMatrix4fv( location_MV, 1, GL_FALSE, p.getCurrentMatrix() );
    Blocks[1].render();
    p.pop();
    glUniformMatrix4fv( location_MV, 1, GL_FALSE, p.getCurrentMatrix() );
    Blocks[2].render();
    p.pop();

    
}

//adds local translations so matrixstack
void Segment::localTranslate(MatrixStack& p)
{
    p.translate(-1.0f, 0.0f, 0.0f);
    p.push();
    p.translate(1.0f, 0.0f, 0.0f);
    p.push();
    p.translate(1.0f, 0.0f, 0.0f);
    p.push();
}





