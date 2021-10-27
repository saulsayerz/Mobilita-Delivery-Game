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
    Lokasi *contents; /* memori tempat penyimpan elemen (container) */
    int nEff;       /* >=0, banyaknya elemen efektif */
    int capacity;   /* ini nanti bakal jadi 26 karena di spek soal gitu */
} ListDinamis;

typedef struct
{
   ListDinamis lokasi; // maksimal 26 karena lokasi terbanyak di spek cuman 26;
   int row; /* banyaknya/ukuran baris peta yg terdefinisi */
   int col;
   Matrix adjacency; /* banyaknya/ukuran kolom  peta yg terdefinisi */
} Map;

typedef struct {
   int waktu; /* waktu pesanan datang*/
   char asal;
   char tujuan;
   char jenis;
   int perishable; // -1 
} Pesanan;

typedef struct{
   Pesanan contents[30];
   int nEff; // berapa pesanan
} DaftarPesanan;

//SELEKTOR
#define MAPROW(M) (M).row
#define MAPCOL(M) (M).col
#define MAPLOC(M) (M).lokasi
#define MAPADJ(M) (M).adjacency
#define LOCNAME(P) (P).nama
#define LOCPOINT(P) (P).titik
#define NEFF(l) (l).nEff
#define CONTENTS(l) (l).contents
#define ELEMEN(l, i) (l).contents[i]
#define ELEMENM(M,i,j) (M).contents[(i)][(j)]
#define KAPASITAS(l) (l).capacity
#define WAKTU(p) (p).waktu
#define ASAL(p) (p).asal
#define TUJUAN(p) (p).tujuan
#define JENIS(p) (p).jenis
#define PERISH(p) (p).perishable

void CreateMap(Map *peta);
void CreateLoc(char nama, int i, int j, Lokasi *tempat);
void CreatePesanan(int waktu, char asal,char tujuan, char jenis, int perishable, Pesanan *p);
void displayMap(Map peta);
void konfigurasi();
void cetakMatrix(Matrix M);
void cetakPesanan(Pesanan p);

#endif