#ifndef WALLS_H
#define WALLS_H

#include<vector>
#include<ctime>
#include<random>
#include<cmath>

#include "TriangleSoup.hpp"
#include "MatrixStack.hpp"


struct wallBlock{
    TriangleSoup* obj;
    float velocity;
    float* positions;
};

class walls
{
    public:
        walls(float rightPositions[3], float leftPositions[3], float gameSpeed);
        ~walls();
        void render(MatrixStack& inStack, GLint& location_MV, GLuint& texture, GLuint& normal, float dt);

    protected:
    private:
        walls();

        void init();
        float randStartPos();
        void updateWalls(float dt);
        void checkAndMove();

        std::vector<wallBlock*> rightWall;
        std::vector<wallBlock*> leftWall;

        float* rightWallOrigin;
        float* leftWallOrigin;
        float gameSpeed;

        static float t;
        static float countUp;
        static const int rows = 12; //STOCK = 12
        static const int cols = 17; //STOCK = 14
        static const float xSize;
        static const float ySize;
        static const float zSize;
        static const float span;
        static const float scaler;
        static const float startTime;
};

#endif // WALLS_H
