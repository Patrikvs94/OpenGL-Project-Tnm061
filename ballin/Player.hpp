#ifndef Player_hpp
#define Player_hpp

#include "Element.h"

//A class for handling the playable (interactive) object
class Player : public Element
{
    public:

        Player();
        Player(TriangleSoup& model, float jump = 2.0f);

        void moveRight(float t,float T);
        void moveLeft(float t,float T);
        void alignPlayer();
        void jump(float t,float T);
        void render(MatrixStack& p, GLint& location_MV, GLuint& texture, float time, float speed, GLuint& normal);
        float getAngle();
        void addCharge();
        void removeCharge();
        bool gotCharges();
        float getRadius();
        int getCurrentCharges();
        static const int maxCharges;

        float* getCollisionData();
        void performAction(bool& gameOver);
        static void setDebugMode(bool flag);

    protected:

    private:
        float gravityMultiplier;
        float moveLength;
        TriangleSoup mesh;
        static const float G;
        int currentCharges;
        float angle;
        float radius;
        static bool debug;



};

#endif /* Player_hpp */
