#include "Segment.h"

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

Segment::~Segment()
{
    //dtor
}

void Segment::render()
{
    
}

void Segment::localTranslate(MatrixStack* p)
{
    p->translate(-(xsize + laneMargin), 0.0f, 0.0f);
    p->push();
    p->translate((xsize + laneMargin), 0.0f, 0.0f);
    p->push();
    p->translate((xsize + laneMargin), 0.0f, 0.0f);
    p->push();
}





