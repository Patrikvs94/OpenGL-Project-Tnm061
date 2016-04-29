#ifndef Player_hpp
#define Player_hpp

#include "Element.h"

//A class for handling the playable (interactive) object
class Player : public Element
{
    public:

        Player();
        Player(TriangleSoup& model, float jump = 2.0f);

        float moveRight(float xPos);
        float moveLeft(float xPos);
        float jump(float yPos);
        void render(MatrixStack& p, GLint& location_MV, GLuint& texture);

    protected:

    private:
        float jumpHeight;
        float moveLength;
        TriangleSoup mesh;


};

#endif /* Player_hpp */
