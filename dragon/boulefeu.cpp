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

namespace boulefeu
{
    #define RAYON 0.25
    #define ANIM_X_PAS 0.001
    #define ANIM_Y_PAS 0.0003

    bool isAnimating = false;
    Point position;

    void draw()
    {
        if (!isAnimating) return;

        glPushMatrix();
            tickAnimation();

            // Lumière source ponctuelle jaune représentant la luminescence de la boule.
            GLfloat position[] = {0.0, 0.0, -1.0, 1.0};
            GLfloat diffuse[] = {0.96, 0.88, 0.43, 1.0};

            glLightfv(GL_LIGHT0, GL_POSITION, position);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

            // Atténuation de l'intensité lumineuse plus la boule s'éloigne.
            glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0);
            glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.4);
            glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.4);

            // Afficher une sphère totalement éclairée et texturée.
            setTexture(0);
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
        glEnable(GL_LIGHT0);
    }

    void stopAnimation()
    {
        isAnimating = false;
        position = Point();
        glDisable(GL_LIGHT0);
    }

    void tickAnimation()
    {
        if (!isAnimating) return;

        position.x += ANIM_X_PAS;
        position.y -= ANIM_Y_PAS;
        glTranslatef(position.x, position.y, position.z);
    }
}
