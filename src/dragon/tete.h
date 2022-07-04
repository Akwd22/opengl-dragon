/**
 * @file tete.h
 * @brief Fichier permettant de dessiner la tête du dragon et gérer son animation.
 */

#ifndef TETE_H_INCLUDED
#define TETE_H_INCLUDED

/// Tête du dragon.
namespace tete
{
    /// Dessiner la tête du dragon.
    void draw();
    /// Activer l'animation de la gueule du dragon.
    void toggleAnimation();
    /// Jouer l'animation de la gueule du dragon.
    void playAnimation();
    /// Arrêter l'animation de la gueule du dragon.
    void stopAnimation();
    /// Continuer à l'étape suivante de l'animation de la gueule du dragon.
    void tickAnimation();
}

#endif // TETE_H_INCLUDED
