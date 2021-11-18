#ifndef MAP_H
#define MAP_H

#include "../boolean.h"
#include "matrix.h"
#include "point.h"
#include "../mesin/wordmachine.h"
#include "../mesin/charmachine.h"
#include "../pesanan/pesanan.h"
#include "../mobita/mobita.h"
#include "../gadget/gadget.h"

typedef struct
{
   char nama;   /* banyaknya/ukuran baris yg terdefinisi */
   POINT titik; /* banyaknya/ukuran kolom yg terdefinisi */
} Lokasi;

typedef struct
{
   Lokasi *contents; /* memori tempat penyimpan elemen (container) */
   int nEff;         /* >=0, banyaknya elemen efektif */
   int capacity;     /* ini nanti bakal jadi 26 karena di spek soal gitu */
} ListDinamis;

typedef struct
{
   ListDinamis lokasi; // maksimal 26 karena lokasi terbanyak di spek cuman 26;
   int row;            /* banyaknya/ukuran baris peta yg terdefinisi */
   int col;
   Matrix adjacency; /* banyaknya/ukuran kolom  peta yg terdefinisi */
} Map;

//SELEKTOR
#define MAPROW(M) (M).row
#define MAPCOL(M) (M).col
#define MAPLOC(M) (M).lokasi
#define MAPADJ(M) (M).adjacency
#define LOCNAME(P) (P).nama
#define LOCPOINT(P) (P).titik
#define NEFF(l) (l).nEff

void CreateMap(Map *peta);
void CreateLoc(char nama, int i, int j, Lokasi *tempat);
void displayMap(Map peta);
void konfigurasi();
int loadGame(Map *peta, DaftarPesanan *daftar, Mobita *player, char *name, Gadget *gadget);
void cetakMatrix(Matrix M);
POINT NameToPoint(Map peta, char nama);

#endif