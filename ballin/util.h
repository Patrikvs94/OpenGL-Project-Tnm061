#ifndef UTIL_H
#define UTIL_H

#include "Segment.h"
#include <vector>
#include "Player.hpp"

struct node{
    Segment* segment;
    std::vector<Element*> children;
};


class util
{
    public:
        util();
        util(Player& p, std::vector<Segment*>& segmentVector, std::vector<Element*>& objects);//, std::vector<TriangleSoup>* obstacleVector);
        void init(std::vector<Segment*>& segmentVector, std::vector<Element*>& objects);      //Init on first run
        void checkCollision(bool jumpFlag);  //Checks collision between two objects
        void updateNodeVector(std::vector<Element*>& elementVector); //UPDATES
        void logPlayerPosition(Player& p, double t, float gameSpeed);

    protected:
    private:
        Player* player;
        std::vector<node*> nodeVector;
        std::vector<float*> positionData;
        const int maxLogSize = 60;
        const double logRate = 60.0; //Logs/s (Hz)
            //OBS! MÅSTE KALLA PÅ DELETE MANUELLT OM ERASE ANVÄNDS.
        double deltaLogTime = 0.0;
        void updateLogData(float dt, float gameSpeed);
};

#endif // UTIL_H
