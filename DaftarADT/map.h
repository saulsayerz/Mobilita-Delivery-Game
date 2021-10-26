#ifndef MAP_H
#define MAP_H

#include "boolean.h"
#include "matrix.h"
#include "point.h"

typedef struct
{
   char nama; /* banyaknya/ukuran baris yg terdefinisi */
   POINT titik; /* banyaknya/ukuran kolom yg terdefinisi */
} Lokasi;


typedef struct
{
   Lokasi contents[26]; // maksimal 26 karena lokasi terbanyak di spek cuman 26
   int neff; // ini neff buat tau ada berapa lokasi efektif
   int row; /* banyaknya/ukuran baris yg terdefinisi */
   int col; /* banyaknya/ukuran kolom yg terdefinisi */
} Map;

//SELEKTOR
#define MAPROW(M) (M).row
#define MAPCOL(M) (M).col
#define MAPNEFF(M) (M).neff
#define MAPELMT(M, i) (M).contents[(i)]
#define LOCNAME(P) (P).nama
#define LOCPOINT(P) (P).titik

void CreateMap(Map *peta);
void CreateLoc(char nama, int i, int j, Lokasi *tempat);
void displayMap(Map peta);
void konfigurasi() ;

#endif