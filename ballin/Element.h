#ifndef ELEMENT_H
#define ELEMENT_H


class Element
{
    public:
        Element();
        virtual ~Element();

    protected:
        //The distance between two lanes
        static const float laneMargin = 0.0f;

    private:
};

#endif // ELEMENT_H