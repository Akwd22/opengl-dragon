#ifdef __APPLE__
#include <GLUT/glut.h> // Pour Mac OS X.
#else
#include <GL/glut.h> // Pour les autres systèmes.
#endif

#include "textures.h"
#include "utils.h"

/// Nombre de textures total chargées.
#define NOMBRE_TEXTURES 3

/// Identifiants des textures générées.
unsigned int texIds[NOMBRE_TEXTURES];

void initTextures()
{
    TTexture textureFeu = loadJpeg("textures/feu.jpg");
    TTexture textureOeil = loadJpeg("textures/oeil.jpg");
    TTexture textureQueue = loadJpeg("textures/queue.jpg");

    glGenTextures(2, texIds);

    // Charger la texture de feu.
    glBindTexture(GL_TEXTURE_2D, texIds[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureFeu.largeur, textureFeu.hauteur, 0, GL_RGB, GL_UNSIGNED_BYTE, textureFeu.texels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // Charger la texture d'oeil.
    glBindTexture(GL_TEXTURE_2D, texIds[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureOeil.largeur, textureOeil.hauteur, 0, GL_RGB, GL_UNSIGNED_BYTE, textureOeil.texels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Charger la texture de la queue.
    glBindTexture(GL_TEXTURE_2D, texIds[2]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureQueue.largeur, textureQueue.hauteur, 0, GL_RGB, GL_UNSIGNED_BYTE, textureQueue.texels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Définir les propriétés des matériaux.
    GLfloat diffuse[] = {1.0, 1.0, 0.0, 1.0};
    GLfloat ambient[] = {0.8, 0.8, 0.8, 0.1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
}

void setTexture(const unsigned int textureId)
{
    glBindTexture(GL_TEXTURE_2D, texIds[textureId]);
}

void clearTexture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
