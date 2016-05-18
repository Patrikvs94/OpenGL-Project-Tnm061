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
        walls(float rightPositions[3], float leftPositions[3]);
        void render(MatrixStack& inStack, GLint& location_MV, GLuint& texture, GLuint& normal, float dt);

        static const int rows = 12;
        static const int cols = 14;
        static const float xSize;
        static const float ySize;
        static const float zSize;
        static const float span;
        static const float scaler;
        static const float speed;

    protected:
    private:
        walls();

        void init();
        float randStartPos();
        void updateWalls(float dt);
        std::vector<wallBlock*> rightWall;
        std::vector<wallBlock*> leftWall;

        float* rightWallOrigin;
        float* leftWallOrigin;

        static float t;
};

#endif // WALLS_H
