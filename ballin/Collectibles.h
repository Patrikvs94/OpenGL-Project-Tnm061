#ifndef COLLECTIBLES_H
#define COLLECTIBLES_H

#ifndef M_PI
#define M_PI (3.141592653589793)
#endif

#include "Element.h"


class Collectibles : public Element
{
    public:
        Collectibles();

        //Temporary render function
        void render(MatrixStack& p, GLint& location_MV, GLuint& texture);
        float* getCollisionData();
        void performeAction();

        //Collectible dimensions
        static const float coinX;
        static const float coinY;
        static const float coinZ;

    private:

        //Temporarily only one "coin collectible"
        TriangleSoup coin;
};

#endif // COLLECTIBLES_H
