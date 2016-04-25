#include "Segment.h"
#include <iostream>

const float Segment::xsize = 0.6f;
const float Segment::ysize = 0.6f;
const float Segment::zsize = 3.0f;


Segment::Segment()
{
    //Creating the 3 lanes with constant dimensions
    Blocks[0].createBox(xsize, ysize, zsize);
    Blocks[1].createBox(xsize, ysize, zsize);
    Blocks[2].createBox(xsize, ysize, zsize);


}

//take shader and matrixstack and render entire segment
void Segment::render(MatrixStack& p, Shader& shader)
{
    
    GLint location_MV = glGetUniformLocation( shader.programID, "MV" );
    glUniformMatrix4fv( location_MV, 1, GL_FALSE, p.getCurrentMatrix() );
    localTranslate(p);
    Blocks[0].render();
    p.pop();
    Blocks[1].render();
    p.pop();
    Blocks[2].render();
    p.pop();
    
}

//adds local translations so matrixstack
void Segment::localTranslate(MatrixStack& p)
{
    p.translate(-(xsize + laneMargin), 0.0f, 0.0f);
    p.push();
    p.translate((xsize + laneMargin), 0.0f, 0.0f);
    p.push();
    p.translate((xsize + laneMargin), 0.0f, 0.0f);
    p.push();
}





