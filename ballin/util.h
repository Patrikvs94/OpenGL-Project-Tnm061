#ifndef UTIL_H
#define UTIL_H

#include "TriangleSoup.hpp"
#include <vector>


class util
{
    public:
        util();
        void getRelevantObjects(TriangleSoup* refPoint);    //Finds relevant objects to check collision with
        bool checkCollision(float* player, float* object);  //Checks collision between two objects
        void sortCollisionArray(TriangleSoup* inObject);      //Put inObject in right place and adjust accordingly.

    protected:
    private:
        std::vector<TriangleSoup> collisionArray;
};

#endif // UTIL_H
