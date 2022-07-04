#ifdef __APPLE__
#include <GLUT/glut.h> // Pour Mac OS X.
#else
#include <GL/glut.h> // Pour les autres systèmes.
#endif

#include "boulefeu.h"
#include "../point.h"
#include "../formes.h"
#include "../utils.h"
#include "../textures.h"

#define RAYON 0.25
#define ANIM_Z_PAS 0.008
#define ANIM_Y_PAS 0.0003
#define ANIM_SCALE_PAS 0.01

namespace boulefeu
{
    /// L'animation est-telle en cours ?
    bool isAnimating = false;

    /// Position actuelle de la boule de feu.
    Point position;
    /// Scale actuel de la boule de feu.
    double scale = 0.00;

    void draw()
    {
        if (!isAnimating)
            return;

        glPushMatrix();
            tickAnimation();

            glScaled(scale, scale, scale);

            // Lumière source ponctuelle jaune représentant la luminescence de la boule.
            GLfloat position[] = {1.0, 1.0, 1.0, 1.0};
            GLfloat diffuse[] = {0.8, 0.0, 0.0, 1.0};

            glLightfv(GL_LIGHT0, GL_POSITION, position);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

            // Atténuation de l'intensité lumineuse plus la boule s'éloigne.
            glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0);
            glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.4);
            glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.4);

            // Afficher une sphère totalement éclairée et texturée.
            setTexture(0);
            glColor3f(1.0, 1.0, 1.0);

            glDisable(GL_LIGHTING);
                sphere(RAYON);
            glEnable(GL_LIGHTING);

            clearTexture();
        glPopMatrix();
    }

    void toggleAnimation()
    {
        isAnimating ? stopAnimation() : playAnimation();
    }

    void playAnimation()
    {
        isAnimating = true;

        position = Point();
        scale = 0.00;

        glEnable(GL_LIGHT0);
    }

    void stopAnimation()
    {
        isAnimating = false;

        position = Point();
        scale = 0.00;

        glDisable(GL_LIGHT0);
    }

    void tickAnimation()
    {
        if (!isAnimating)
            return;

        position.z += ANIM_Z_PAS;
        position.y -= ANIM_Y_PAS;

        if (position.z >= 5)
            stopAnimation();

        if (scale < 1)
            scale += ANIM_SCALE_PAS;

        glTranslatef(position.x, position.y, position.z);
    }
}
