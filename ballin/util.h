#ifndef UTIL_H
#define UTIL_H

#include "Segment.h"    //INCLUDES TRIANGLESOUOP
#include <vector>
#include "Player.hpp"


class util
{
    public:
        util();
        util(Player* p, std::vector<Segment*>* segmentVector);//, std::vector<TriangleSoup>* obstacleVector);
        void init(std::vector<Segment*>* segmentVector);                                        //Init on first run
        //std::vector<std::vector<Element*>> sendToCheck();    //Finds relevant objects to check collision with
        bool checkCollision();  //Checks collision between two objects
        void updateCollisionVectors();                     //Put inObject in right place and adjust accordingly.
        std::vector<Element*> sendToCheck();

    protected:
    private:
        std::vector<Segment*> collisionSegments;             //Vector that holds all segments used when checking collision
        Player* player;
        //CREATE VECTOR FOR OBSTICLE AND COLLECTABLE
};

#endif // UTIL_H
