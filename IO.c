#include "IO.h"


//funkcja, która po wczytaniu do text stringLength znaków sprawdza, czy w tekst znajduje się znak '\n' (jesli tak to zamienia do na '\0', a jeśli nie, to czyści dalsze wejście
void dealWithInputAndNewLine(char * text, int stringLength) {
    int i;
    for (i = stringLength - 1; i > 0; i--) {
        if ( text[i] == '\n' ) {
            text[i] = '\0';
            break;
        }
    }
    if (i == 0 && text[0] != '\n')
        cleanInput();
}

void requestFileToRead (char * pToFileName) {
    
    char * fileName = pToFileName;
    fgets(fileName, 25, stdin);
    
    dealWithInputAndNewLine(fileName, 25);
    return;
}

void cleanInput (void) {
    char ch;
    while( (ch = getchar()) != '\n')
        continue;
}



//FUNKCJE DLA CAŁEGO ALGORYTMU W C
int checkPixel(unsigned char* one, unsigned char* two) {
    int i;
    for(i = 0; i < 4; i++) {
        if (one[i] != two[i])
            return 0;
    }
    return 1;
}

int checkRow(unsigned char* one, unsigned char* two) {
    int i;
    for(i = 0; i < 4; i++) {
        if(!checkPixel(&one[4*i], &two[4*i]))
            return 0;
    }
    return 1;
}

int check4x4 (unsigned char* data, unsigned char* pattern, int dataWidth) {
    int i;
    for(i = 0; i < 4; i++) {
        if(!checkRow(data + i*dataWidth*4, pattern + i*16))
            return 0;
    }
    return 1;
}

int calculateIndex(int x, int y, int width) {
    return y*width*4 + x*4;
}

int checkCorrectness (unsigned char * bitmapData, unsigned char * bitmapPattern, int width, int height) {
    int currX = 0;
    int currY = 0;
    int counter = 0;
    while(currY < height - 3) {
        if (check4x4(bitmapData + calculateIndex(currX, currY, width), bitmapPattern, width))
            counter++;
        if (currX < width - 4)
            currX++;
        else {
            currX = 0;
            currY++;
        }
    }
    return counter;
}


unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
    FILE *filePtr; //our file pointer
    BITMAPFILEHEADER bitmapFileHeader; //our bitmap file header
    unsigned char *bitmapImage;  //store image data

    //open filename in read binary mode
    filePtr = fopen(filename,"rb");
    if (filePtr == NULL)
        return NULL;

    //read the bitmap file header
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,filePtr);

    //verify that this is a bmp file by check bitmap id
    if (bitmapFileHeader.bfType !=0x4D42)
    {
        fclose(filePtr);
        return NULL;
    }
    //read the bitmap info header
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER),1,filePtr);
    //move file point to the begging of bitmap data
    fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
    //allocate enough memory for the bitmap image data
    bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);
    //verify memory allocation
    if (!bitmapImage)
    {
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }
    //read in the bitmap image data
    fread(bitmapImage,bitmapInfoHeader->biSizeImage,1,filePtr);
    //make sure bitmap image data was read
    if (bitmapImage == NULL)
    {
        fclose(filePtr);
        return NULL;
    }

    //close file and return bitmap iamge data
    fclose(filePtr);
    return bitmapImage;
}

void close() {};
