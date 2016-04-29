#ifndef UTIL_H
#define UTIL_H

#include "Segment.h"    //INCLUDES TRIANGLESOUOP
#include <vector>


class util
{
    public:
        util();
        util(std::vector<Segment>* segmentVector, std::vector<TriangleSoup>* obstacleVector);
        void init();                                        //Init on first run
        void getRelevantObjects(TriangleSoup* refPoint);    //Finds relevant objects to check collision with
        bool checkCollision(float* player, float* object);  //Checks collision between two objects
        void updateCollisionVector();                        //Put inObject in right place and adjust accordingly.

    protected:
    private:
        std::vector<Segment>* collisionSegments;             //Vector that holds all segments used when checking collision
        std::vector<TriangleSoup>* collisionObstacles;       //Vector that holds all objects used when checking collision
};

#endif // UTIL_H
