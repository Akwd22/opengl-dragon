#ifdef __APPLE__
#include <GLUT/glut.h> // Pour Mac OS X.
#else
#include <GL/glut.h> // Pour les autres systèmes.
#endif

#include "pattes.h"
#include "../point.h"
#include "../formes.h"

namespace pattes
{
    void jambeDroite()
    {
        //Base
        glPushMatrix();
            glRotatef(-15, 1, 0, 0);
            glTranslatef(0.6, 0, -0.2);
            parallelepipede(0.3, 0.6, 0.6);
        glPopMatrix();

        //Mollet
        glPushMatrix();
            glRotatef(-15, 1, 0, 0);
            glTranslatef(0.6, -0.55, -0.3);
            parallelepipede(0.3, 0.65, 0.4);
        glPopMatrix();

        // Tibia
        glPushMatrix();
            glTranslatef(0.6, -1.27, -0.06);
            parallelepipede(0.3, 0.8, 0.4);
        glPopMatrix();

        //Pied
        glPushMatrix();
            glTranslatef(0.6, -1.57, 0.29);
            parallelepipede(0.3, 0.2, 0.3);
        glPopMatrix();
    }

    void jambeGauche()
    {
        //Base
        glPushMatrix();
            glRotatef(-15, 1, 0, 0);
            glTranslatef(-0.6, 0, -0.2);
            parallelepipede(0.3, 0.6, 0.6);
        glPopMatrix();

        //Mollet
        glPushMatrix();
            glRotatef(-15, 1, 0, 0);
            glTranslatef(-0.6, -0.55, -0.3);
            parallelepipede(0.3, 0.65, 0.4);
        glPopMatrix();

        // Tibia
        glPushMatrix();
            glTranslatef(-0.6, -1.27, -0.06);
            parallelepipede(0.3, 0.8, 0.4);
        glPopMatrix();

        //Pied
        glPushMatrix();
            glTranslatef(-0.6, -1.57, 0.29);
            parallelepipede(0.3, 0.2, 0.3);
        glPopMatrix();
    }

    void draw()
    {
        jambeDroite();
        jambeGauche();
    }

}
