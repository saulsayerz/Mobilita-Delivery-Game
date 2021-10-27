#include <stdio.h>
#include "map.c"

int main() {
    Map peta;
    DaftarPesanan daftar;

    CreateMap(&peta);
    MAPCOL(peta) = 8;
    MAPROW(peta) = 8;
    konfigurasi(&peta,&daftar);
    // printf("%d %d\n", MAPROW(peta), MAPCOL(peta)); // MENCETAK UKURAN PETA BARIS x KOLOM
    // printf("%d %d\n", Absis(LOCPOINT(ELEMEN(MAPLOC(peta),0))), Ordinat(LOCPOINT(ELEMEN(MAPLOC(peta),0)))); // MENCETAK ABSIS DAN ORDINAT DARI HEADQUARTER
    // cetakMatrix(MAPADJ(peta)); // CETAK MATRIKS ADJ
    // printf("%d\n", NEFF(daftar)); // CETAK BANYAKNYA PESANAN
    displayMap(peta);

    return 0;
}