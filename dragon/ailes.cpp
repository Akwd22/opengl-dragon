#ifdef __APPLE__
#include <GLUT/glut.h> // Pour Mac OS X.
#else
#include <GL/glut.h> // Pour les autres systèmes.
#endif

#include "../point.h"
#include "../formes.h"

namespace ailes
{
    void aileDroite(){
        //Aile Droite
        // Base
        glPushMatrix();
            glRotatef(7,0,0,1);
            glTranslatef(1,0,1.5);
            parallelepipede(1,0.2,0.4);
        glPopMatrix();

        // Milieu
        glPushMatrix();
            glTranslatef(1.9,0.18,1.5);
            parallelepipede(1,0.14,0.33);
        glPopMatrix();

        // Extension
        glPushMatrix();
            glRotatef(-7,0,0,1);
            glTranslatef(2.8,0.47,1.5);
            parallelepipede(1,0.08,0.25);
        glPopMatrix();

        // Os ailes
        glPushMatrix();
            glTranslatef(1.3,0.15,0.9);
            parallelepipede(0.20,0.10,1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(2.3,0.20,1);
            parallelepipede(0.10,0.05,0.8);
        glPopMatrix();
    }

    void aileGauche(){
        // Aile Gauche
        //Base
        glPushMatrix();
            glRotatef(-7,0,0,1);
            glTranslatef(-1,0,1.5);
            parallelepipede(1,0.2,0.4);
        glPopMatrix();

        // Milieu
        glPushMatrix();
            glTranslatef(-1.9,0.18,1.5);
            parallelepipede(1,0.14,0.33);
        glPopMatrix();

        // Extension
        glPushMatrix();
            glRotatef(7,0,0,1);
            glTranslatef(-2.8,0.47,1.5);
            parallelepipede(1,0.08,0.25);
        glPopMatrix();

        // Os ailes
        glPushMatrix();
            glTranslatef(-1.3,0.15,0.9);
            parallelepipede(0.20,0.10,1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2.3,0.20,1);
            parallelepipede(0.10,0.05,0.8);
        glPopMatrix();
    }

    void draw()
    {
        aileDroite();
        aileGauche();
    }


}
