#ifdef __APPLE__
#include <GLUT/glut.h> // Pour Mac OS X.
#else
#include <GL/glut.h> // Pour les autres systèmes.
#endif

#include "ailes.h"
#include "../point.h"
#include "../formes.h"
#include "../utils.h"
#include "../textures.h"

#define ANIM_ANGLE_PAS 0.5

namespace ailes
{
    /// Phase Ailes Haute
    bool phaseAileHaute = false;
    /// Phase Ailes Basse
    bool phaseAileBasse = true;

    /// Angle actuelle des ailes
    double angleAile = 0.00;

    void aileDroite()
    {
        //Aile Droite
        // Base
        glPushMatrix();
            glRotatef(7, 0, 0, 1);
            glTranslatef(1, 0, 1.5);
            parallelepipede(1, 0.2, 0.4);
        glPopMatrix();

        // Milieu
        glPushMatrix();
            glTranslatef(1.9, 0.18, 1.5);
            parallelepipede(1, 0.14, 0.33);
        glPopMatrix();

        // Extension
        glPushMatrix();
            glRotatef(-7, 0, 0, 1);
            glTranslatef(2.8, 0.47, 1.5);
            parallelepipede(1, 0.08, 0.25);
        glPopMatrix();

        // Os ailes
        glPushMatrix();
            glTranslatef(1.3, 0.15, 0.9);
            parallelepipede(0.20, 0.10, 1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(2.3, 0.20, 1);
            parallelepipede(0.10, 0.05, 0.8);
        glPopMatrix();

        //Planeur Base
        glPushMatrix();
            glRotatef(7, 0, 0, 1);
            glTranslatef(0.8, 0, 1);
            parallelepipede(0.9, 0.04, 0.8);
        glPopMatrix();

        //Planeur Milieu
        glPushMatrix();
            glTranslatef(1.82, 0.18, 1.1);
            parallelepipede(0.9, 0.04, 0.7);
        glPopMatrix();

        //Planeur Extension
        glPushMatrix();
            glRotatef(-7, 0, 0, 1);
            glTranslatef(2.7, 0.47, 1.2);
            parallelepipede(0.9, 0.04, 0.6);
        glPopMatrix();
    }

    void aileGauche()
    {
        // Aile Gauche
        //Base
        glPushMatrix();
            glRotatef(-7, 0, 0, 1);
            glTranslatef(-1, 0, 1.5);
            parallelepipede(1, 0.2, 0.4);
        glPopMatrix();

        // Milieu
        glPushMatrix();
            glTranslatef(-1.9, 0.18, 1.5);
            parallelepipede(1, 0.14, 0.33);
        glPopMatrix();

        // Extension
        glPushMatrix();
            glRotatef(7, 0, 0, 1);
            glTranslatef(-2.8, 0.47, 1.5);
            parallelepipede(1, 0.08, 0.25);
        glPopMatrix();

        // Os ailes
        glPushMatrix();
            glTranslatef(-1.3, 0.15, 0.9);
            parallelepipede(0.20, 0.10, 1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2.3, 0.20, 1);
            parallelepipede(0.10, 0.05, 0.8);
        glPopMatrix();

        //Planeur Base
        glPushMatrix();
            glRotatef(-7, 0, 0, 1);
            glTranslatef(-0.8, 0, 1);
            parallelepipede(0.9, 0.04, 0.8);
        glPopMatrix();

        //Planeur Milieu
        glPushMatrix();
            glTranslatef(-1.82, 0.18, 1.1);
            parallelepipede(0.9, 0.04, 0.7);
        glPopMatrix();

        //Planeur Extension
        glPushMatrix();
            glRotatef(7, 0, 0, 1);
            glTranslatef(-2.7, 0.47, 1.2);
            parallelepipede(0.9, 0.04, 0.6);
        glPopMatrix();
    }

    void draw()
    {
        tickAnimation();

        glPushMatrix();
            glRotatef(angleAile, 0, 0, 1);
            aileDroite();
        glPopMatrix();

        glPushMatrix();
            glRotatef(-(angleAile), 0, 0, 1);
            aileGauche();
        glPopMatrix();
    }

    void tickAnimation()
    {
        if (phaseAileBasse)
        {
            angleAile += ANIM_ANGLE_PAS;

            if (angleAile >= 20)
            {
                phaseAileHaute = true;
                phaseAileBasse = false;
            }
        }

        if (phaseAileHaute)
        {
            angleAile -= ANIM_ANGLE_PAS;

            if (angleAile <= -20)
            {
                phaseAileHaute = false;
                phaseAileBasse = true;
            }
        }
    }
}
