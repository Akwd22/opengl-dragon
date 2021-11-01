#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h> /* Pour Mac OS X */
#else
    #include <GL/glut.h>   /* Pour les autres systèmes */
#endif

#include "consts.h"

using namespace std;

/*
* TODO :
*   - Modéliser le dragon.
*   - Modéliser au moins 1 primitive à partir de sa représentation paramétrique.
*   - Utiliser au moins 2 textures : une plaquée sur une face, l'autre enroulée autour d'une primitive.
*   - Gérer au moins 2 types de lumières.
*   - Zoomer la caméra avec les touches 'z' et 'Z'.
*   - Touches directionnelles :
*       * tourner autour du dragon par la droite (flèche gauche);
*       * tourner autour du dragon par la gauche (flèche droite);
*       * tourner autour du dragon par le bas (flèche haute);
*       * tourner autour du dragon par le haut (flèche basse).
*   - Au moins 1 animation manuelle avec les touches du clavier.
*   - Au moins 1 animation automatique.
*/

/*
* NOTES :
*   - Hauteur : axe Y.
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

    glutSolidTeapot(0.5);

    glFlush();
    glutSwapBuffers();
};

void reshapeHandler(int l, int h)
{
    cout << "Window reshaped with new width: " << l << " and height: " << h << endl;
};

void keyboardHandler(unsigned char touche, int x, int y)
{
    cout << "Key pressed: " << touche << " at X: " << x << " Y: " << y << endl;
};

void mouseHandler(int bouton, int etat, int x, int y)
{
    cout << "Mouse button pressed: " << bouton << " with state: " << etat << " at X: " << x << " Y: " << y << endl;
};

void motionHandler(int x, int y)
{
    cout << "Mouse moved while button is pressed at X: " << x << " Y: " << y << endl;
};

void specialHandler(int touche, int x, int y)
{
    cout << "Non-ASCII key pressed: " << touche << " at X: " << x << " Y: " << y << endl;
};

void idleHandler()
{
};
