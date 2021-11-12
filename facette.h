#ifndef FACETTE_H
#define FACETTE_H

#include "point.h"

/**
 * @brief Classe représentant une facette à 4 points.
 */
class Facette
{
public:
    /// Point bas-gauche.
    Point &p1;
    /// Point bas-droit.
    Point &p2;
    /// Point haut-droit.
    Point &p3;
    /// Point haut-gauche.
    Point &p4;

    /// Constructeur à partir des 4 points de la facette.
    Facette(Point &p1, Point &p2, Point &p3, Point &p4);
};

#endif // FACETTE_H
