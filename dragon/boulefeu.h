/**
 * @file boulefeu.h
 * @brief Fichier permettant de dessiner la boule de feu et gérer son animation.
 */

#ifndef BOULEFEU_H_INCLUDED
#define BOULEFEU_H_INCLUDED

/// Boule de feu animée qui sort de la gueule du dragon après appui sur la touche Espace.
namespace boulefeu
{
    /// Dessiner la boule de feu.
    void draw();
    /// Activer/désactiver l'animation de la boule de feu.
    void toggleAnimation();
    /// Jouer l'animation de la boule de feu.
    void playAnimation();
    /// Arrêter l'animation de la boule de feu.
    void stopAnimation();
    /// Continuer à l'étape suivante de l'animation de la boule de feu.
    void tickAnimation();
}

#endif // BOULEFEU_H_INCLUDED
