#include "formes.h"

#include <vector>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h> // Pour Mac OS X.
#else
#include <GL/glut.h> // Pour les autres systèmes.
#endif

#include "point.h"
#include "facette.h"

using namespace std;

void sphereTexCoord(const Point & p, const double rayon)
{
    float angle = 0.5 * atan2(p.z / rayon, p.x / rayon) / M_PI + 0.5;
    float hauteur = 0.5 * p.y / rayon + 0.5;
    glTexCoord2f(angle, hauteur);
}

void sphere(const double rayon)
{
    #define NB_MERIDIENS 24
    #define NB_PARALLELES 12

    // Points.
    vector<Point> points;

    for (unsigned int p = 0; p < NB_PARALLELES; p++)
    {
        for (unsigned int m = 0; m < NB_MERIDIENS; m++)
        {
            double theta = (m * 2 * M_PI) / NB_MERIDIENS;
            double phi = ((p * M_PI) / (NB_PARALLELES - 1)) - (M_PI / 2);

            Point p;
            p.x = rayon * cos(theta) * cos(phi);
            p.y = rayon * sin(theta) * cos(phi);
            p.z = rayon * sin(phi);

            points.push_back(p);
        }
    }

    // Faces.
    vector<Facette> facettes;

    for (unsigned int p = 0; p < NB_PARALLELES - 1; p++)
    {
        for (unsigned int m = 0; m < NB_MERIDIENS; m++)
        {
            unsigned int pn = (p + 1) % NB_PARALLELES;
            unsigned int mn = (m + 1) % NB_MERIDIENS;

            Point & p1 = points[p * NB_MERIDIENS + m];
            Point & p2 = points[p * NB_MERIDIENS + mn];
            Point & p3 = points[pn * NB_MERIDIENS + mn];
            Point & p4 = points[pn * NB_MERIDIENS + m];

            facettes.push_back(Facette(p1, p2, p3, p4));
        }
    }

    // Dessin de la sphère.
    for (Facette f : facettes)
    {
        glBegin(GL_POLYGON);
            sphereTexCoord(f.p1, rayon);
            glVertex3d(f.p1.x, f.p1.y, f.p1.z);

            sphereTexCoord(f.p2, rayon);
            glVertex3d(f.p2.x, f.p2.y, f.p2.z);

            sphereTexCoord(f.p3, rayon);
            glVertex3d(f.p3.x, f.p3.y, f.p3.z);

            sphereTexCoord(f.p4, rayon);
            glVertex3d(f.p4.x, f.p4.y, f.p4.z);
        glEnd();
    }
}
