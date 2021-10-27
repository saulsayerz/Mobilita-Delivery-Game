#include <stdio.h>
#include "../DaftarADT/map.c"
#include "../DaftarADT/pesanan.c"

int main() {
    int opsi;
    Map peta;
    DaftarPesanan daftar;
    CreateMap(&peta);
    printf("Selamat datang di game TUBES K2 Kelompok 6\nketik 1 untuk new game\nketik 2 untuk exit\nmasukkan opsi: ");
    scanf("%d", &opsi);
    if (opsi ==1) {
        konfigurasi(&peta, &daftar);
        /*printf("%d %d\n", MAPROW(peta), MAPCOL(peta)); // MENCETAK UKURAN PETA BARIS x KOLOM
        printf("%d %d\n", Absis(LOCPOINT(ELEMEN(MAPLOC(peta),0))), Ordinat(LOCPOINT(ELEMEN(MAPLOC(peta),0)))); //MENCETAK ABSIS DAN ORDINAT DARI HEADQUARTER
        cetakMatrix(MAPADJ(peta)); // CETAK MATRIKS ADJ
        printf("%d\n", NEFF(daftar)); // CETAK BANYAKNYA PESANAN
        displayMap(peta);*/ // BUAT NGEBIKIN PETA LOKASI
    }
    return 0;
}