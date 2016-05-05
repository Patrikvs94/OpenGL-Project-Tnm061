#ifndef UTIL_H
#define UTIL_H

#include "Segment.h"    //INCLUDES TRIANGLESOUOP
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
        //SKRIV OM SÅ ATT MAN TAR IN REFERENCER ISTÄLLET.... FETT JOBBIGT DOCK.....
        util(Player* p, std::vector<Segment*>* segmentVector, std::vector<Element*>* objects);//, std::vector<TriangleSoup>* obstacleVector);
        void init(std::vector<Segment*>* segmentVector, std::vector<Element*>* objects);      //Init on first run
        void checkCollision();  //Checks collision between two objects
        void updateCollisionVectors(); //UPDATES


    protected:
    private:
        std::vector<Segment*> collisionSegments;             //Vector that holds all segments used when checking collision
        Player* player;
        std::vector<node*> nodeVector;
        //CREATE VECTOR FOR OBSTICLE AND COLLECTABLE
};

#endif // UTIL_H
