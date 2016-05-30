#include "lightsource.hpp"


lightsource::lightsource()
{
    pos=new cordinate;
    pos->x=0.0f;
    pos->y=0.0f;
    pos->z=0.0f;
    tex.createTexture("textures/red.tga");
    norm.createTexture("textures/red_norm.tga");
    sphere.createSphere(0.5f, 2);
}

void lightsource::setX(float x)
{
    pos->x=x;
}

void lightsource::setY(float y)
{
    pos->y=y;
}

void lightsource::setZ(float z)
{
    pos->z=z;
}

cordinate* lightsource::cordinates()
{
    return pos;
}

void lightsource::setupLight(GLint location_l)
{
    glUniform3fv(location_l, 1, (const GLfloat*)pos);
    
}

void lightsource::renderlight(MatrixStack& MV, GLint location_MV)
{
    MV.push();
    MV.translate(pos->x, pos->y, pos->z);
    glUniformMatrix4fv( location_MV, 1, GL_FALSE, MV.getCurrentMatrix() );
    glBindTexture(GL_TEXTURE_2D, tex.texID);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, norm.texID);
    glActiveTexture(GL_TEXTURE0);
    sphere.render();
    MV.pop();
}

