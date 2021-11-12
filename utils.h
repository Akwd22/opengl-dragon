#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <string>

using namespace std;

typedef struct
{
    /// Largeur de l'image.
    unsigned int largeur = 0;
    /// Hauteur de l'image.
    unsigned int hauteur = 0;
    /// Tableau 1D de taille @p largeur * @p hauteur * 3 stockant la valeur de chaque pixel de l'image.
    unsigned char *texels = nullptr;
} TTexture;

/**
 * @brief Charger en mémoire une image jpeg.
 * @param path Chemin d'accès de l'image.
 * @return Données de l'image chargée.
 */
TTexture loadJpeg(const string &path);

#endif // UTILS_H_INCLUDED
