//
//  main.c
//  x86_WALLY
//
//  Created by Marcin Badach on 30/04/2020.
//  Copyright © 2020 Marcin Badach. All rights reserved.
//

#define GL_SILENCE_DEPRECATION


#include <stdio.h>
#include <stdlib.h>
#include "whereIsWally.h"
#include "IO.h"
//DYREKTYWY DLA MACOS
//#include <OpenGL/gl.h>
//#include <OpenGl/glu.h>
//#include <GLUT/glut.h>

//DYREKTYWY DLA LINUXA
#include <GL/glut.h>
#include <GL/freeglut.h>


int main(int argc, const char * argv[]) {
    BITMAPINFOHEADER bitmapDataHeader;
    BITMAPINFOHEADER bitmapPatternHeader;
    
    char * patternName = (char *)malloc(25 * sizeof(char));
    char * dataName = (char *)malloc(25 * sizeof(char));
    
    unsigned char *bitmapData = NULL;
    unsigned char *bitmapPattern = NULL;
    
    int width;
    int height;
    
    int firstRun = 1;
    int validInput = 1;
    
while(1){
    puts("Nacisnij dowolny klawisz, aby wczytać bitmapy, lub 'q', aby wyjść.");
    char c = getchar();
    cleanInput();
    
    if (c == 'q')
        break;
    
    puts("Podaj nazwę bitmapy o nieznanym rozmiarze:");
    requestFileToRead(dataName);
    puts("Podaj nazwę bitmapy o rozmiarze 4x4:");
    requestFileToRead(patternName);
    
    bitmapPattern = LoadBitmapFile(patternName,&bitmapPatternHeader);
    bitmapData = LoadBitmapFile(dataName,&bitmapDataHeader);
    
    validInput = 1;
    if(bitmapData == NULL) {
        printf("Bledna nazwa bitmapy danych.\n");
        validInput = 0;
    }
    if(bitmapPattern == NULL) {
        printf("Bledna nazwa pliku wzorca.\n");
        validInput = 0;
    }
    else if(bitmapPatternHeader.biWidth != 4 || bitmapPatternHeader.biHeight != 4) {
        printf("Bledne wymiary bitmapy wzorca.\n");
        validInput = 0;
    }

    
    if(validInput) {
    width = bitmapDataHeader.biWidth;
    height = bitmapDataHeader.biHeight;
    
//ALGORYTM W C
    int testV = checkCorrectness(bitmapData, bitmapPattern, width, height);
//WYWOŁANIE ALGORYTMU W ASSEMBLERZE
    unsigned int result = whereIsWally(bitmapData, bitmapPattern, width, height);
    
//SPRAWDZENIE POPRAWNOŚCI
    if(testV != result) {
        printf("Blad. Rozbieznosc wynikow obliczen.\n");
    }
    printf("Bitmapa o rozmiarze 4x4 występuje w drugiej bitmapie %d razy.\n", result);
    
    
//GLUT
    if(firstRun)
        glutInit(&argc, (char **)argv);
    
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_CONTINUE_EXECUTION);
    glViewport( (GLsizei) 0, (GLsizei) 0, (GLsizei) 100, (GLsizei) 100 );
    glClear(GL_COLOR_BUFFER_BIT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glutInitWindowSize(width+16, height+16);           // set a window size
    glutInitWindowPosition(50,50);          // set a window position
    glutCreateWindow("Bitmapy");
    
    glDrawPixels(4,4, GL_BGRA, GL_UNSIGNED_BYTE, bitmapPattern);
    glBitmap(0, 0, 0, 0, 10, 10, NULL);
    glDrawPixels(width,height, GL_BGRA, GL_UNSIGNED_BYTE, bitmapData);
    glutSwapBuffers();
    
    glutCloseFunc(close);
    glutMainLoop();
    glutInit(&argc, (char **)argv);
    glutLeaveMainLoop();
    firstRun = 0;
    }
    else printf("Wprowadz poprawne dane.\n");
}
    printf("Program zakończył działanie.\n");
    free(bitmapData);
    free(bitmapPattern);
    free(patternName);
    free(dataName);
    
    return 0;
}


