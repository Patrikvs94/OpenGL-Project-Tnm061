#ifndef WALLS_H
#define WALLS_H

#include<vector>
#include<TriangleSoup.hpp>
#include <ctime>


struct wallBlock{
    TriangleSoup* obj;
    float velocity;
};

class walls
{
    public:
        walls();

        static const int rows = 4;
        static const int cols = 6;
        static const float xSize;
        static const float ySize;
        static const float zSize;

    protected:
    private:
        void init();
        void randStartPos();
        void updateWalls(double dt);
        std::vector<wallBlock*> rightWall;
        std::vector<wallBlock*> leftWall;
};

#endif // WALLS_H
