#include "map.h"
#include "point.h"
#include "wordmachine.h"
//#include "charmachine.c"
#include <stdio.h>

void CreateMap(Map *peta){
    MAPROW(*peta) = 0;
    MAPCOL(*peta) = 0;
    MAPNEFF(*peta) = 0;
}

void CreateLoc(char nama, int i, int j, Lokasi *tempat){
    LOCNAME(*tempat) = nama;
    Absis(LOCPOINT(*tempat)) = i;
    Ordinat(LOCPOINT(*tempat)) = j; 
}

void displayMap(Map peta){
    Matrix m;
    int i,j;
    ROWS(m) = MAPROW(peta) +2;
    COLS(m) = MAPCOL(peta) +2;
    for (i = 0; i < MAPROW(peta)+2 ; i++) {
        for (j = 0; j < MAPCOL(peta)+2 ; j++){
            if (i==0 || j==0 || i==MAPROW(peta)+1||j==MAPCOL(peta)+1 ){
                printf("*");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void konfigurasi() {
    int baris, kolom;
    startWord("test.txt");
    baris = kataToInt(currentWord);
    advWord();
    kolom = kataToInt(currentWord);
    adv(); //ini untuk ngeskip \n
    printf("%d %d", baris, kolom);
}

