#ifndef UTIL_H
#define UTIL_H

#include "Segment.h"
#include <vector>
#include "Player.hpp"
#include "Collectibles.h"
#include "obstacles.h"
#include "matrixStack.hpp"

struct node{
    Segment* segment;
    std::vector<Collectibles*> children;
    item* pillar = nullptr;
};


class util
{
    public:
        util(Player& p, std::vector<Segment*>& segmentVector, std::vector<Collectibles*>& collVector, obstacles* obs);//, std::vector<TriangleSoup>* obstacleVector);
        ~util();
        void init(std::vector<Segment*>& segmentVector, std::vector<Collectibles*>& collObjects);      //Init on first run
        void checkCollision(bool jumpFlag, bool& gameOver, bool& invincible);  //Checks collision between two objects
        void updateNodeVector(std::vector<Collectibles*>& collVector); //UPDATES
        void logPlayerPosition(Player& p, double t, float gameSpeed);
        void renderCharges(MatrixStack& p, GLint& location_MV, GLuint& texture, GLuint& normal);

    protected:
    private:
        util(); //Disable default constructor
        Player* player;
        std::vector<node*> nodeVector;
        std::vector<float*> positionData;
        const int maxLogSize = 10;
        const double logRate = 60.0; //Logs/s (Hz)
            //OBS! MÅSTE KALLA PÅ DELETE MANUELLT OM ERASE ANVÄNDS.
        double deltaLogTime = 0.0;
        obstacles* obs;
        void updateLogData(float dt, float gameSpeed);
        void commonCollision(bool& invincible, int nodeVectorIndex, bool& gameOver);
        std::vector<TriangleSoup*> chargesVector;
};

#endif // UTIL_H
