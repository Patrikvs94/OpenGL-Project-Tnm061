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


    protected:
    private:
        Player* player;
        std::vector<node*> nodeVector;
};

#endif // UTIL_H
