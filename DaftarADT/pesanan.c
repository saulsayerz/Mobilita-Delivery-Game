#include "pesanan.h"
#include <stdio.h>

void CreatePesanan(int waktu, char asal,char tujuan, char jenis, int perishable, Pesanan *p){
    WAKTU(*p) = waktu;
    ASAL(*p) = asal;
    TUJUAN(*p) = tujuan;
    JENIS(*p) = jenis;
    PERISH(*p) = perishable;
}

void cetakPesanan(Pesanan p) {
    printf("%d %c %c %c %d\n", WAKTU(p),ASAL(p),TUJUAN(p),JENIS(p),PERISH(p));
}
