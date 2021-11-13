/**
 * @file ailes.h
 * @brief Fichier permettant de dessiner les ailes du dragon et gérer leur animation.
 */

#ifndef AILES_H_INCLUDED
#define AILES_H_INCLUDED

/// Ailes du dragon animées.
namespace ailes
{
    /// Continuer à l'étape suivante de l'animation des ailes.
    void tickAnimation();
    /// Dessiner les ailes du dragon.
    void draw();
}

#endif // AILES_H_INCLUDED
