#ifdef __APPLE__
#include <GLUT/glut.h> // Pour Mac OS X.
#else
#include <GL/glut.h> // Pour les autres systèmes.
#endif

#include "corps.h"
#include "../point.h"
#include "../formes.h"
#include "../textures.h"

namespace corps
{
    void draw()
    {
        // Corps du dragon
        glPushMatrix();
            parallelepipede(1, 1, 1.5);
        glPopMatrix();

        glPushMatrix();
            glRotatef(10, 1, 0, 0);
            glTranslatef(0, 0.1, 1.2);
            parallelepipede(1.2, 1.2, 1.2);
        glPopMatrix();

        // Coup du dragon
        glPushMatrix();
            glRotatef(25, 1, 0, 0);
            glTranslatef(0, 0.6, 1.8);
            parallelepipede(0.9, 0.9, 1.3);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, -0.5, 2.8);
            parallelepipede(0.7, 0.7, 1);
        glPopMatrix();

        // Queue du dragon
        glPushMatrix();
            glRotatef(-15, 1, 0, 0);
            glTranslatef(0, 0.2, -1);
            parallelepipede(0.7, 0.7, 1);
        glPopMatrix();

        glPushMatrix();
            glRotatef(-10, 1, 0, 0);
            glTranslatef(0, 0.05, -1.8);
            parallelepipede(0.6, 0.6, 0.8);
        glPopMatrix();

        glPushMatrix();
            glRotatef(-5, 1, 0, 0);
            glTranslatef(0, -0.15, -2.4);
            parallelepipede(0.4, 0.4, 0.6);
        glPopMatrix();

        glPushMatrix();
            glRotatef(10, 1, 0, 0);
            glTranslatef(0, -0.85, -2.8);
            parallelepipede(0.2, 0.2, 0.8);
        glPopMatrix();

        // Bout de la queue
        glPushMatrix();
            glTranslatef(0, -0.25, -3.45);
            glRotatef(10, 1, 0, 0);
            glRotatef(45, 0, 1, 0);
            parallelepipede(0.5, 0.1, 0.5);
        glPopMatrix();
    }
}
