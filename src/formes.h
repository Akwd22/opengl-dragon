/**
 * @file formes.h
 * @brief Fichier comportant des fonctions permettant de dessiner des formes basiques.
 */

#ifndef FORMES_H_INCLUDED
#define FORMES_H_INCLUDED

/**
 * @brief Dessiner une sphère sans texture et au centre du repère.
 * @param rayon Rayon de la sphère.
 */
void sphere(const double rayon);

/**
 * @brief Dessiner un parallélépipède sans texture et au centre du repère.
 * @param longueur Longueur du parallélépipède.
 * @param largeur Largeur du parallélépipède.
 * @param hauteur Hauteur du parallélépipède.
 */
void parallelepipede(const double longueur, const double largeur, const double hauteur);

#endif // FORMES_H_INCLUDED
