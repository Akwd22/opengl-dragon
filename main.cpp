/**
 * @file main.cpp
 * @brief Fichier responsable de l'initialisation d'OpenGL et de ses bibliothèques.
 * Définir les paramètres de rendu, de la caméra, de la gestion de la fenêtre ainsi que des interactions IHM (clavier, souris, etc.).
 */

#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h> // Pour Mac OS X.
#include <GLUT/freeglut.h>
#else
#include <GL/glut.h> // Pour les autres systèmes.
#include <GL/freeglut.h>
#endif

#include "textures.h"
#include "formes.h"
#include "dragon/corps.h"
#include "dragon/ailes.h"
#include "dragon/tete.h"
#include "dragon/pattes.h"
#include "dragon/boulefeu.h"

using namespace std;

/*
* TODO :
*   # Modéliser le dragon.
*   # Modéliser au moins 1 primitive à partir de sa représentation paramétrique.
*   # Utiliser au moins 2 textures : une plaquée sur une face, l'autre enroulée autour d'une primitive.
*   # Gérer au moins 2 types de lumières.
*   # Zoomer la caméra avec les touches 'z' et 'Z'.
*   # Touches directionnelles :
*       * tourner autour du dragon par la droite (flèche gauche);
*       * tourner autour du dragon par la gauche (flèche droite);
*       * tourner autour du dragon par le bas (flèche haute);
*       * tourner autour du dragon par le haut (flèche basse).
*   # Au moins 1 animation manuelle avec les touches du clavier.
*   # Au moins 1 animation automatique.
*/

/* -------------------------------------------------------------------------- */
/*                                 Définitions                                */
/* -------------------------------------------------------------------------- */

/* ----------------------------- Initialisations ---------------------------- */

void initGlut(int *argc, char **argv);
void initGl();

/* ------------------------ Fonctions de dispositions ----------------------- */

void displayCamera();
void displayRepere();
void displaySpot();
void displayPlateforme();

/* -------------------------- Fonctions de rappels -------------------------- */

void displayHandler();
void reshapeHandler(int l, int h);
void keyboardHandler(unsigned char touche, int x, int y);
void mouseHandler(int bouton, int etat, int x, int y);
void motionHandler(int x, int y);
void specialHandler(int touche, int x, int y);
void idleHandler();

/* -------------------------------------------------------------------------- */
/*                             Variables globales                             */
/* -------------------------------------------------------------------------- */

/* --------------------------------- Fenêtre -------------------------------- */

/// Largeur de la fenêtre.
unsigned int winWidth;
/// Hauteur de la fenêtre.
unsigned int winHeight;

/// Dernière position X du curseur.
int oldY;
/// Dernière position Y du curseur.
int oldX;

/// Bouton de la souris enfoncé (-1 si aucun).
int mousePressedButton = -1;

/* --------------------------------- Caméra --------------------------------- */

/// Angle FOV de la caméra (pour le zoom).
float fovCamera = 60.0;
/// Pas de modification du FOV de la caméra.
float fovCameraStep = 2.0;

/// Angle de rotation caméra autour de l'axe Y.
float angleCameraY = 0.0;
/// Angle de rotation caméra autour de l'axe X.
float angleCameraX = 0.0;
/// Pas de modification de la rotation caméra autour d'un axe.
float angleCameraStep = 1.0;

/* -------------------------------------------------------------------------- */
/*                                    Main                                    */
/* -------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
    initGlut(&argc, argv);
    return 0;
}

/* -------------------------------------------------------------------------- */
/*                               Implémentations                              */
/* -------------------------------------------------------------------------- */

/* ----------------------------- Initialisations ---------------------------- */

/**
 * @brief Initialiser la bibliothèque GLUT.
 * Créer la fenêtre et définir les fonctions de rappels.
 * @param argc Nombre d'arguments passé au programme.
 * @param argv Arguments passés au programme.
 */
void initGlut(int *argc, char **argv)
{
    // Initialisation fenêtre.
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(1000, 500);
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

/**
 * @brief Initialiser la bibliothèque OpenGL.
 * Définir les paramètres de rendu.
 */
void initGl()
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // Couleur du fond.
    glColor3f(1.0, 1.0, 1.0);         // Couleur des tracés.

    initTextures();

    // Paramètres OpenGL.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);

    glShadeModel(GL_SMOOTH);
}

/* ------------------------ Fonctions de dispositions ----------------------- */

/// Afficher et placer la caméra.
void displayCamera()
{
    // Zoom de la caméra.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovCamera, (float)winWidth / (float)winHeight, 0.5, 20.0);

    // Position de la caméra.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Rotation de la caméra.
    glRotatef(angleCameraY, 0.0, 1.0, 0.0);
    glRotatef(angleCameraX, 1.0, 0.0, 0.0);
}

/// Afficher et placer le repère.
void displayRepere()
{
    bool lightingEnabled = glIsEnabled(GL_LIGHTING);

    glDisable(GL_LIGHTING);

    // Axe X en rouge.
    glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3i(0, 0, 0);
        glVertex3i(3, 0, 0);
    glEnd();

    // Axe Y en vert.
    glBegin(GL_LINES);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3i(0, 0, 0);
        glVertex3i(0, 3, 0);
    glEnd();

    // Axe Z en bleu.
    glBegin(GL_LINES);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3i(0, 0, 0);
        glVertex3i(0, 0, 3);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);

    if (lightingEnabled)
        glEnable(GL_LIGHTING);
}

/// Afficher un spot lumineux au-dessus du dragon.
void displaySpot()
{
    glPushMatrix();
        GLfloat position[] = {0.0, 5.0, 0.0, 1.0};
        GLfloat direction[] = {0.0, -1.0, 0.0};
        GLfloat color[] = {1.0, 0.6, 0.0, 1.0};

        glLightfv(GL_LIGHT7, GL_POSITION, position);
        glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, direction);
        glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, 90.0);
        glLightf(GL_LIGHT7, GL_SPOT_EXPONENT, 5.0);

        glLightfv(GL_LIGHT7, GL_AMBIENT, color);
        glLightfv(GL_LIGHT7, GL_DIFFUSE, color);

        glEnable(GL_LIGHT7);
    glPopMatrix();
}

/// Afficher une plateforme circulaire sous le dragon.
void displayPlateforme()
{
    glPushMatrix();
        glTranslatef(0.0, -2.0, 0.0);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        glutSolidCylinder(6.0, 0.1, 30.0, 30.0);
    glPopMatrix();
}

/* --------------------------- Fonctions de rappel -------------------------- */

/**
 * @brief Fonction de rappel pour l'affichage de la scène.
 * Afficher les objets 3D sur la scène, effectuer les transformations, etc.
 */
void displayHandler()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    displayCamera();
    displayRepere();

    displaySpot();
    displayPlateforme();

    glPushMatrix();
        corps::draw();
        ailes::draw();
        tete::draw();
        pattes::draw();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
};

/**
 * @brief Fonction de rappel lors du redimensionnement de la fenêtre.
 * @param l Nouvelle largeur de fenêtre.
 * @param h Nouvelle hauteur de fenêtre.
 */
void reshapeHandler(int l, int h)
{
    cout << "Window reshaped with new width: " << l << " and height: " << h << endl;

    glViewport(0, 0, l, h);

    winWidth = l;
    winHeight = h;
};

/**
 * @brief Fonction de rappel lors de l'appuie d'une touche ASCII.
 * @param touche Caractère ASCII de la touche appuyée.
 * @param x Position X du curseur au moment de l'appuie.
 * @param y Position Y du curseur au moment de l'appuie.
 */
void keyboardHandler(unsigned char touche, int x, int y)
{
    cout << "Key pressed: " << touche << " at X: " << x << " Y: " << y << endl;

    switch (touche)
    {
        case 'Z': // Zoomer la caméra.
            fovCamera -= fovCameraStep;
            break;
        case 'z': // Dézoomer la caméra.
            fovCamera += fovCameraStep;
            break;
        case 'p': // Affichage mode plein.
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
        case 'f': // Affichage mode fil de fer.
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        case 's': // Affichage en mode sommets seuls.
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
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
        case ' ': // Animation boule de feu.
            tete::toggleAnimation();
            break;
    }

    glutPostRedisplay();
};

/**
 * @brief Fonction de rappel lors de l'appuie d'un bouton souris.
 * @param bouton Bouton de la souris appuyé.
 * @param etat État du bouton appuyé (enfoncé ou relaché).
 * @param x Position X du curseur au moment de l'appuie.
 * @param y Position Y du curseur au moment de l'appuie.
 */
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
        case GLUT_SCROLL_UP: // Zoomer la caméra.
            if (etat == GLUT_UP) fovCamera -= fovCameraStep;
            break;
        case GLUT_SCROLL_DOWN: // Dézoomer la caméra.
            if (etat == GLUT_UP) fovCamera += fovCameraStep;
            break;
    }

    glutPostRedisplay();
};

/**
 * @brief Fonction de rappel lors du déplacement du curseur avec une touche enfoncée.
 * @param x Position X du curseur.
 * @param y Position Y du curseur.
 */
void motionHandler(int x, int y)
{
    cout << "Mouse moved while the button: " << mousePressedButton << " is pressed at X: " << x << " Y: " << y << endl;

    switch (mousePressedButton)
    {
        case GLUT_LEFT_BUTTON: // Rotationner la caméra.
            angleCameraY += x - oldX;
            angleCameraX += y - oldY;
            break;
    }

    oldY = y;
    oldX = x;

    glutPostRedisplay();
};

/**
 * @brief Fonction de rappel lors de l'appuie d'une touche non-ASCII.
 * @param touche Code non-ASCII de la touche appuyée.
 * @param x Position X du curseur au moment de l'appuie.
 * @param y Position Y du curseur au moment de l'appuie.
 */
void specialHandler(int touche, int x, int y)
{
    cout << "Non-ASCII key pressed: " << touche << " at X: " << x << " Y: " << y << endl;

    switch (touche)
    {
        case GLUT_KEY_LEFT: // Rotationner la caméra à droite.
            angleCameraY -= angleCameraStep;
            break;
        case GLUT_KEY_RIGHT: // Rotationner la caméra à gauche.
            angleCameraY += angleCameraStep;
            break;
        case GLUT_KEY_UP: // Rotationner la caméra en bas.
            angleCameraX -= angleCameraStep;
            break;
        case GLUT_KEY_DOWN: // Rotationner la caméra en haut.
            angleCameraX += angleCameraStep;
            break;
    }

    glutPostRedisplay();
};

/**
 * @brief Fonction de rappel lorsque inactif.
 * Effectuer les animations automatiques des objets.
 */
void idleHandler()
{
    tete::tickAnimation();
    boulefeu::tickAnimation();

    glutPostRedisplay();
};
