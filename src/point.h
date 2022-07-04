#ifndef POINT_H
#define POINT_H

/// Classe représentant un point à 3 coordonnées.
class Point
{
public:
    /// Coordonnée X.
    double x;
    /// Coordonnée Y.
    double y;
    /// Coordonnée Z.
    double z;

    /// Constructeur par défaut.
    Point();
    /// Constructeur à partir des coordonnées du point.
    Point(const double x, const double y, const double z);
};

#endif // POINT_H
