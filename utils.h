#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <string>

using namespace std;

typedef struct {
    unsigned int largeur = 0;
    unsigned int hauteur = 0;
    unsigned char * texels = nullptr;
} TTexture;

TTexture loadJpeg(const string & path);

#endif // UTILS_H_INCLUDED
