#include "Element.h"

//Constructor
Element::Element()
{

}

Element::Element(float x, float y, float z): xPos(x), yPos(y),zPos(z){}

//Destructor
Element::~Element()
{

}

float Element::getX()
{
    return xPos;
}

float Element::getY()
{
    return yPos;
}

float Element::getZ()
{
    return zPos;
}
