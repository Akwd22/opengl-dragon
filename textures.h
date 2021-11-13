/**
 * @file textures.h
 * @brief Fichier proposant des fonctions permettant de facilement gérer les textures OpenGL.
 */

#ifndef TEXTURES_H_INCLUDED
#define TEXTURES_H_INCLUDED

#include <string>

using namespace std;

/**
 * @brief Initialiser et charger en mémoire les textures nécessaires.
 */
void initTextures();

/**
 * @brief Définir la texture à utiliser.
 * @param textureId Identifiant de la texture.
 */
void setTexture(const unsigned int textureId);

/**
 * @brief Ne définir aucune texture à utiliser.
 */
void clearTexture();

#endif // TEXTURES_H_INCLUDED
