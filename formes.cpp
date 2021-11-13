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

/**
 * @brief Créer une coordonnée de texture à partir d'un point d'une sphère.
 * @param p Point de la sphère.
 * @param rayon Rayon de la sphère.
 */
void sphereTexCoord(const Point &p, const double rayon)
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

            Point &p1 = points[p * NB_MERIDIENS + m];
            Point &p2 = points[p * NB_MERIDIENS + mn];
            Point &p3 = points[pn * NB_MERIDIENS + mn];
            Point &p4 = points[pn * NB_MERIDIENS + m];

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

void parallelepipede(const double x, const double y, const double z)
{
    glPushMatrix();
        // Tableau pour stocker les sommets du cube.
        Point pCube[8] = {
            {-0.5, -0.5, 0.5},
            {0.5, -0.5, 0.5},
            {0.5, -0.5, -0.5},
            {-0.5, -0.5, -0.5},
            {-0.5, 0.5, 0.5},
            {0.5, 0.5, 0.5},
            {0.5, 0.5, -0.5},
            {-0.5, 0.5, -0.5}};

        // Tableau pour stocker les indices des sommets par face pour le cube.
        int fCube[6][4] = {
            {0, 1, 2, 3},
            {0, 1, 5, 4},
            {1, 2, 6, 5},
            {2, 3, 7, 6},
            {0, 4, 7, 3},
            {4, 5, 6, 7}};

        glScalef(x, y, z);

        // Dessin du cube
        for (int i = 0; i < 6; i++)
        {
            if (i == 0) glNormal3f(0, -1, 0);   // Face du bas.
            if (i == 1) glNormal3f(0, 0, 1);    // Face avant.
            if (i == 2) glNormal3f(1, 0, 0);    // Face droite.
            if (i == 3) glNormal3f(0, 0, -1);   // Face arrière.
            if (i == 4) glNormal3f(-1, 0, 0);   // Face gauche.
            if (i == 5) glNormal3f(0, 1, 0);    // face du haut.

            glBegin(GL_POLYGON);
                for (int j = 0; j < 4; j++)
                {
                    if (j == 0) glTexCoord2f(0, 0);
                    if (j == 1) glTexCoord2f(0, 1);
                    if (j == 2) glTexCoord2f(1, 1);
                    if (j == 3) glTexCoord2f(1, 0);

                    double x = pCube[fCube[i][j]].x;
                    double y = pCube[fCube[i][j]].y;
                    double z = pCube[fCube[i][j]].z;

                    glVertex3f(x, y, z);
                }
            glEnd();
        }
    glPopMatrix();
}
