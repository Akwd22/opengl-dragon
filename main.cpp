#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>  // Pour Mac OS X.
#else
    #include <GL/glut.h>    // Pour les autres systèmes.
#endif

#include "consts.h"

using namespace std;

/*
* TODO :
*   - Modéliser le dragon.
*   - Modéliser au moins 1 primitive à partir de sa représentation paramétrique.
*   - Utiliser au moins 2 textures : une plaquée sur une face, l'autre enroulée autour d'une primitive.
*   - Gérer au moins 2 types de lumières.
*   # Zoomer la caméra avec les touches 'z' et 'Z'.
*   # Touches directionnelles :
*       * tourner autour du dragon par la droite (flèche gauche);
*       * tourner autour du dragon par la gauche (flèche droite);
*       * tourner autour du dragon par le bas (flèche haute);
*       * tourner autour du dragon par le haut (flèche basse).
*   - Au moins 1 animation manuelle avec les touches du clavier.
*   - Au moins 1 animation automatique.
*/

/*
* NOTES :
*   - 1 type de lumière au niveau des 2 yeux du dragon.
*   - 1 type de lumière ambiante.
*/

void initGlut(int* argc, char** argv);
void initGl();

void displayHandler();
void reshapeHandler(int l, int h);
void keyboardHandler(unsigned char touche, int x, int y);
void mouseHandler(int bouton, int etat, int x, int y);
void motionHandler(int x, int y);
void specialHandler(int touche, int x, int y);
void idleHandler();

float fovCamera = 50.0; // Zoom caméra.
float fovCameraStep = 1.0;

float angleCameraY = 0.0; // Rotation caméra autour axe Y.
float angleCameraYStep = 1.0;

float angleCameraX = 0.0; // Rotation caméra autour axe X.
float angleCameraXStep = 1.0;

int oldY;
int oldX;

int mousePressedButton = -1; // -1 <=> aucun bouton pressé

#if MAIN_CUBE == 0
int main(int argc, char** argv)
{
    initGlut(&argc, argv);
    return 0;
}
#endif // MAIN_CUBE

void initGlut(int* argc, char** argv)
{
    // Initialisation fenêtre.
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(2200, 200);
    glutCreateWindow("Projet SI");

    // Initialiser OpenGL.
    initGl();

    // Définition des fonctions de rappel.
    glutDisplayFunc(displayHandler);
    glutReshapeFunc(reshapeHandler);
    glutIdleFunc(idleHandler);

    glutKeyboardFunc(keyboardHandler);
    glutMouseFunc(mouseHandler);
    glutMotionFunc(motionHandler);
    glutSpecialFunc(specialHandler);

    glutMainLoop();
}

void initGl()
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // Couleur du fond.
    glColor3f(1.0, 1.0, 1.0); // Couleur des tracés.

    glPointSize(2.0);

    glEnable(GL_DEPTH_TEST);
}

void displayHandler()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovCamera, 1.0, 1.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, -5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glRotatef(angleCameraY, 0.0, 1.0, 0.0);
    glRotatef(angleCameraX, 1.0, 0.0, 0.0);

    glutSolidTeapot(1.0);

    glFlush();
    glutSwapBuffers();
};

void reshapeHandler(int l, int h)
{
    cout << "Window reshaped with new width: " << l << " and height: " << h << endl;

    glutPostRedisplay();
};

void keyboardHandler(unsigned char touche, int x, int y)
{
    cout << "Key pressed: " << touche << " at X: " << x << " Y: " << y << endl;

    switch (touche)
    {
        case 'Z':
            fovCamera -= fovCameraStep;
            break;
        case 'z':
            fovCamera += fovCameraStep;
            break;
        case 'p': // Affichage mode plein.
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            break;
        case 'f': // Affichage mode fil de fer.
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            break;
        case 's' : // Affichage en mode sommets seuls.
            glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
            break;
        case 'd':
            glEnable(GL_DEPTH_TEST);
            break;
        case 'D':
            glDisable(GL_DEPTH_TEST);
            break;
        case 'a':
            glPolygonMode(GL_FRONT, GL_FILL);
            glPolygonMode(GL_FRONT, GL_LINE);
        break;
    }

    glutPostRedisplay();
};

void mouseHandler(int bouton, int etat, int x, int y)
{
    #define GLUT_SCROLL_UP 3
    #define GLUT_SCROLL_DOWN 4

    cout << "Mouse button pressed: " << bouton << " with state: " << etat << " at X: " << x << " Y: " << y << endl;

    mousePressedButton = etat == GLUT_DOWN ? bouton : -1;

    switch (bouton)
    {
        case GLUT_LEFT_BUTTON:
            oldY = y;
            oldX = x;
            break;
        case GLUT_SCROLL_UP:
            if (etat == GLUT_UP) fovCamera -= fovCameraStep;
            break;
        case GLUT_SCROLL_DOWN:
            if (etat == GLUT_UP) fovCamera += fovCameraStep;
            break;
    }

    glutPostRedisplay();
};

void motionHandler(int x, int y)
{
    cout << "Mouse moved while the button: " << mousePressedButton << " is pressed at X: " << x << " Y: " << y << endl;

    switch (mousePressedButton)
    {
        case GLUT_LEFT_BUTTON:
            angleCameraY += x - oldX;
            angleCameraX += y - oldY;
            break;
    }

    oldY = y;
    oldX = x;

    glutPostRedisplay();
};

void specialHandler(int touche, int x, int y)
{
    cout << "Non-ASCII key pressed: " << touche << " at X: " << x << " Y: " << y << endl;

    switch (touche)
    {
        case GLUT_KEY_LEFT:
            angleCameraY -= angleCameraYStep;
            break;
        case GLUT_KEY_RIGHT:
            angleCameraY += angleCameraYStep;
            break;
        case GLUT_KEY_UP:
            angleCameraX -= angleCameraXStep;
            break;
        case GLUT_KEY_DOWN:
            angleCameraX += angleCameraXStep;
            break;
    }

    glutPostRedisplay();
};

void idleHandler()
{
};
