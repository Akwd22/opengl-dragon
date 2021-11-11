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

void sphere(const double rayon)
{
    #define NB_MERIDIENS 16
    #define NB_PARALLELES 14

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
            glVertex3d(f.p1.x, f.p1.y, f.p1.z);
            glVertex3d(f.p2.x, f.p2.y, f.p2.z);
            glVertex3d(f.p3.x, f.p3.y, f.p3.z);
            glVertex3d(f.p4.x, f.p4.y, f.p4.z);
        glEnd();
    }
}

void parallelepipede(const double longueur, const double largeur, const double hauteur) {
    glPushMatrix();
    //Tableau pour stocker les sommets du cube et leur couleur
    Point pCube[8]={
        {-0.5,-0.5, 0.5},
        { 0.5, -0.5, 0.5},
        { 0.5, -0.5, -0.5},
        { -0.5, -0.5, -0.5},
        { -0.5,0.5, 0.5},
        { 0.5, 0.5, 0.5},
        { 0.5, 0.5, -0.5},
        { -0.5, 0.5, -0.5}};

    //Tableau pour stocker les indices des sommets par face pour le cube
    int fCube[6][4]={
      {0,1,2,3},//face envers endroit={0,3,2,1}
      {0,1,5,4},
      {1,2,6,5},
      {2,3,7,6},
      {0,4,7,3},
      {4,5,6,7}};

    glScalef(largeur, hauteur, longueur);

    // Dessin du cube
    for (int i=0;i<6;i++)
    {
        glBegin(GL_POLYGON);
        for (int j=0;j<4;j++){
            glVertex3f(pCube[fCube[i][j]].x,pCube[fCube[i][j]].y,pCube[fCube[i][j]].z);
        }
        glEnd();
    }
    glPopMatrix();
}

