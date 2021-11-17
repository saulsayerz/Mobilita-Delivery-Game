#include "pesanan.h"
#include <stdio.h>

void CreatePesanan(int waktu, char asal,char tujuan, char jenis, int perishable, Pesanan *p){
    WAKTUPESANAN(*p) = waktu;
    ASAL(*p) = asal;
    TUJUAN(*p) = tujuan;
    JENIS(*p) = jenis;
    PERISH(*p) = perishable;
    INITPERISH(*p) = perishable;
}

void cetakPesanan(Pesanan p) {
    printf("%d %c %c %c %d\n", WAKTUPESANAN(p),ASAL(p),TUJUAN(p),JENIS(p),PERISH(p));
}

void sortPesanan(DaftarPesanan *daftar) {
    int i, j;
    Pesanan temp;
    for (i = 0; i < NEFF(*daftar)-1; i++){
        for (j = 0; j < NEFF(*daftar)-i-1; j++){
            if (WAKTUPESANAN(ELEMEN(*daftar,j)) > WAKTUPESANAN(ELEMEN(*daftar,j+1))){
                temp = ELEMEN(*daftar,j);
                ELEMEN(*daftar,j) = ELEMEN(*daftar,j+1);
                ELEMEN(*daftar,j+1) = temp;
            }
        }
    }
}