#ifndef MODELLOADER_H
#define MODELLOADER_H 
#include "glutcallbacks.h"
#include <SOIL/SOIL.h>
//1-es �rt�kkel bet�lti a text�r�kat, 2-essel kil�p a programb�l
int graphicsMode;
typedef GLubyte Pixel[3]; //r,g,b

/**
*Parse models and textures
*/
void parseModels();

/**
*Initialize textres
*/
void initialize_texture();
#endif /*MODELLOADER_H*/
