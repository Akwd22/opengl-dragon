#ifndef FACETTE_H
#define FACETTE_H

#include "point.h"

class Facette
{
    public:
        Point & p1;
        Point & p2;
        Point & p3;
        Point & p4;

        Facette(Point & p1, Point & p2, Point & p3, Point & p4);
};

#endif // FACETTE_H
