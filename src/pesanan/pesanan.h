#ifndef PESANAN_H
#define PESANAN_H

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

#define NEFF(l) (l).nEff
#define CONTENTS(l) (l).contents
#define ELEMEN(l, i) (l).contents[i]
#define ELEMENM(M,i,j) (M).contents[(i)][(j)]
#define KAPASITAS(l) (l).capacity
#define WAKTUPESANAN(p) (p).waktu
#define ASAL(p) (p).asal
#define TUJUAN(p) (p).tujuan
#define JENIS(p) (p).jenis
#define PERISH(p) (p).perishable

void CreatePesanan(int waktu, char asal,char tujuan, char jenis, int perishable, Pesanan *p);
void cetakPesanan(Pesanan p);
void sortPesanan(DaftarPesanan *daftar);

#endif