
#ifndef IO_H_
#define IO_H_
#include <stdio.h>
#include <stdlib.h>
#include "whereIsWally.h"
#include <GL/glut.h>
#include <GL/freeglut.h>

//DEKLARACJE FUNKCJI DLA CAŁEGO ALGORYTMU W C
int checkPixel(unsigned char* one, unsigned char* two);
int checkRow(unsigned char* one, unsigned char* two);
int check4x4 (unsigned char* data, unsigned char* pattern, int dataWidth);
int calculateIndex(int x, int y, int width);
int checkCorrectness (unsigned char * bitmapData, unsigned char * bitmapPattern, int width, int height);


//FUNKCJE DO POBIERANIA NAZWY PLIKU
void dealWithInputAndNewLine(char * text, int stringLength);
void cleanInput (void);
void requestFileToRead (char * pToFileName);


#pragma pack(push, 1)
typedef struct tagBITMAPFILEHEADER
{
    unsigned short bfType;  //specifies the file type
    unsigned int bfSize;  //specifies the size in bytes of the bitmap file
    unsigned short bfReserved1;  //reserved; must be 0
    unsigned short bfReserved2;  //reserved; must be 0
    unsigned int bfOffBits;  //species the offset in bytes from the bitmapfileheader to the bitmap bits
}BITMAPFILEHEADER;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct tagBITMAPINFOHEADER
{
    unsigned int biSize;  //specifies the number of bytes required by the struct
    int biWidth;  //specifies width in pixels
    int biHeight;  //species height in pixels
    unsigned short biPlanes; //specifies the number of color planes, must be 1
    unsigned short biBitCount; //specifies the number of bit per pixel
    unsigned int biCompression;//spcifies the type of compression
    unsigned int biSizeImage;  //size of image in bytes
    int biXPelsPerMeter;  //number of pixels per meter in x axis
    int biYPelsPerMeter;  //number of pixels per meter in y axis
    unsigned int biClrUsed;  //number of colors used by the bitmap
    unsigned int biClrImportant;
}BITMAPINFOHEADER;
#pragma pack(pop)


unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
void close();

#endif
