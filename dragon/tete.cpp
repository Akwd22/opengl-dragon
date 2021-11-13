#ifdef __APPLE__
#include <GLUT/glut.h> // Pour Mac OS X.
#else
#include <GL/glut.h> // Pour les autres systèmes.
#endif

#include "tete.h"
#include "boulefeu.h"
#include "../formes.h"
#include "../point.h"
#include "../utils.h"
#include "../textures.h"

#define ANIM_ANGLE_PAS 0.05

namespace tete
{
    /// L'animation est-telle en cours ?
    bool isAnimating = false;

    /// Phase où la gueule du dragon s'ouvre.
    bool phaseOuvertureGueule = false;
    /// Phase où la boule de feu est générée.
    bool phaseBouleFeu = false;
    /// Phase où la gueule du dragon se ferme.
    bool phaseFermetureGueule = false;

    /// Angle actuelle d'ouverture de la gueule.
    double gueuleAngle = 0.00;

    void draw()
    {
        tickAnimation();

        // Crâne.
        glPushMatrix();
            glTranslatef(0.0, -0.3, 3.5);
            parallelepipede(0.9, 0.7, 0.5);
        glPopMatrix();

        // Museau.
        glPushMatrix();
            glTranslatef(0.0, -0.4, 3.9);
            parallelepipede(0.7, 0.5, 0.4);
        glPopMatrix();

        // Mâchoire basse.
        glPushMatrix();
            glColor3f(0, 1, 0);
            glTranslatef(0.0, -0.7, 3.5);
            glRotatef(gueuleAngle, 1, 0, 0);

            // Partie gauche.
            glPushMatrix();
                glTranslatef(0.0, 0.0, 0.0);
                parallelepipede(0.85, 0.2, 0.45);
            glPopMatrix();

            // Partie droite.
            glPushMatrix();
                glTranslatef(0.0, 0.0, 0.4);
                parallelepipede(0.65, 0.2, 0.35);
            glPopMatrix();
        glPopMatrix();

        setTexture(1); // Appliquer la texture d'oeil.

        // Oeil gauche.
        glPushMatrix();
            glTranslatef(-0.4, -0.2, 3.6);
            glRotatef(180, 0, 1, 0);
            sphere(0.1);
        glPopMatrix();

        // Oeil droit.
        glPushMatrix();
            glTranslatef(0.4, -0.2, 3.6);
            sphere(0.1);
        glPopMatrix();

        clearTexture();

        // Cornes.
        glPushMatrix();
            glTranslatef(-0.5, 0.05, 3.1);
            glRotatef(90, 1, 0, 0);
            glRotatef(-25, 0, 0, 1);
            glRotatef(30, 1, 0, 0);
            parallelepipede(0.1, 0.45, 0.1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.5, 0.05, 3.1);
            glRotatef(-90, 1, 0, 0);
            glRotatef(-25, 0, 0, 1);
            glRotatef(30, 1, 0, 0);
            parallelepipede(0.1, 0.45, 0.1);
        glPopMatrix();

        // Boule de feu (uniquement lors de l'animation).
        glPushMatrix();
            glTranslatef(0, -0.75, 4.0);
            boulefeu::draw();
        glPopMatrix();
    }

    void toggleAnimation()
    {
        if (!isAnimating)
            playAnimation();
    }

    void playAnimation()
    {
        isAnimating = true;

        phaseOuvertureGueule = true;
        phaseBouleFeu = false;
        phaseFermetureGueule = false;

        gueuleAngle = 0.00;
    }

    void stopAnimation()
    {
        isAnimating = false;

        phaseOuvertureGueule = false;
        phaseBouleFeu = false;
        phaseFermetureGueule = false;

        gueuleAngle = 0.00;
    }

    void tickAnimation()
    {
        if (!isAnimating)
            return;

        if (phaseOuvertureGueule)
        {
            gueuleAngle += ANIM_ANGLE_PAS;

            if (gueuleAngle >= 40)
            {
                phaseOuvertureGueule = false;
                phaseBouleFeu = true;
            }
        }

        if (phaseBouleFeu)
        {
            boulefeu::playAnimation();
            phaseBouleFeu = false;
            phaseFermetureGueule = true;
        }

        if (phaseFermetureGueule)
        {
            gueuleAngle -= ANIM_ANGLE_PAS;

            if (gueuleAngle <= 0)
            {
                stopAnimation();
            }
        }
    }
}
