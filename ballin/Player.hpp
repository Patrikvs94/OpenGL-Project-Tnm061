#ifndef Player_hpp
#define Player_hpp

#include "Element.h"

class Player : public Element
{
    public:

        Player();

        void render(MatrixStack& p, GLint& location_MV, GLuint& texture);

    protected:

    private:
        float jumpHeight;


};

#endif /* Player_hpp */
