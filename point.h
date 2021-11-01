#ifndef POINT_H
#define POINT_H

/**
 * @brief Classe représentant un point à 3 coordonnées.
 */
class Point
{
public:
    /// Coordonnée X.
    int x;
    /// Coordonnée Y.
    int y;
    /// Coordonnée Z.
    int z;

    /// Constructeur par défaut.
    Point();
    /// Constructeur à partir des coordonnées du point.
    Point(int x, int y, int z);
};

#endif // POINT_H
