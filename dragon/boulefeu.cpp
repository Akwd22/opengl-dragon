#ifdef __APPLE__
#include <GLUT/glut.h> // Pour Mac OS X.
#else
#include <GL/glut.h> // Pour les autres systèmes.
#endif

#include "boulefeu.h"
#include "../point.h"
#include "../formes.h"

namespace boulefeu
{
    #define RAYON 0.25
    #define ANIM_X_PAS 0.001
    #define ANIM_Y_PAS 0.0003

    bool isAnimating = false;
    Point position;

    void draw()
    {
        glPushMatrix();
            tickAnimation();

            GLfloat position[] = {0.0, 0.0, -1.0, 1.0};
            GLfloat diffuse[] = {0.96, 0.88, 0.43, 1.0};
            GLfloat specular[] = {0.96, 0.88, 0.43, 1.0};

            glLightfv(GL_LIGHT0, GL_POSITION, position);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
            glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
            glEnable(GL_LIGHT0);

            glDisable(GL_LIGHTING);
                sphere(RAYON);
            glEnable(GL_LIGHTING);
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
    }

    void stopAnimation()
    {
        isAnimating = false;
        position = Point();
    }

    void tickAnimation()
    {
        if (!isAnimating) return;

        position.x += ANIM_X_PAS;
        position.y -= ANIM_Y_PAS;
        glTranslatef(position.x, position.y, position.z);
    }
}
