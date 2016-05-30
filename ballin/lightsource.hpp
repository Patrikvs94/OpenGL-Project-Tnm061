
#ifndef LIGHTSOURCE_HPP
#define LIGHTSOURCE_HPP

#include <stdio.h>
#include "TriangleSoup.hpp"
#include "Texture.hpp"
#include "matrixstack.hpp"

struct cordinate {
    float x,y,z;
};

class lightsource
{
private:
    cordinate* pos;
    Texture tex, norm;
    TriangleSoup sphere;
    
public:
    lightsource();
    ~lightsource();
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    cordinate* cordinates();
    void setupLight(GLint location_l);
    void renderlight(MatrixStack& MV, GLint location_MV);
    
    
    
};


#endif /* lightsource_hpp */
