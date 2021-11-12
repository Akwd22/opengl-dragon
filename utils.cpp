#include <cstdio>
#include <cstdlib>
#include <GL/freeglut.h>
#include <jpeglib.h>
#include <jerror.h>

#include "utils.h"

#ifdef __WIN32
#pragma comment(lib, "jpeg.lib")
#endif

TTexture loadJpeg(const string &path)
{
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *file;
    unsigned char *ligne;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

#ifdef __WIN32
    if (fopen_s(&file, fichier, "rb") != 0)
    {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier %s\n", path);
        exit(1);
    }
#elif __GNUC__
    if ((file = fopen(path.c_str(), "rb")) == 0)
    {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier %s\n", path.c_str());
        exit(1);
    }
#endif

    jpeg_stdio_src(&cinfo, file);
    jpeg_read_header(&cinfo, TRUE);

    unsigned char *image = (unsigned char *)calloc(cinfo.image_width * cinfo.image_height * 3, sizeof(unsigned char));

    if (cinfo.jpeg_color_space == JCS_GRAYSCALE)
    {
        fprintf(stdout, "Erreur : l'image doit être de type RGB\n");
        exit(1);
    }

    jpeg_start_decompress(&cinfo);
    ligne = image;

    while (cinfo.output_scanline < cinfo.output_height)
    {
        ligne = image + 3 * cinfo.image_width * cinfo.output_scanline;
        jpeg_read_scanlines(&cinfo, &ligne, 1);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    TTexture resultat;
    resultat.largeur = cinfo.image_width;
    resultat.hauteur = cinfo.image_height;
    resultat.texels = image;

    return resultat;
}
