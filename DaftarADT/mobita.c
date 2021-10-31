#include "mobita.h"

/**
 * Inisialisasi Mobita
 **/
void createMobita(Mobita *m){
    Inventory i;

    // inisialisasi objek anak
    POINT p = MakePOINT(0, 0);
    createInventory(&i);

    // assign tiap properti objek
    INVENTORY(*m) = i;
    UANG(*m) = 0;
    WAKTU(*m) = 0;
    POSISI(*m) = p;
}

/**
 * Menambahkan satu unit ke waktu
 **/
void addOneToWaktu(Mobita *m){
    WAKTU(*m) += 1;
}

/**
 * Menambahkan dua unit ke waktu
 **/
void addTwoToWaktu(Mobita *m){
    WAKTU(*m) += 2;
}

/**
 * Mengurangi uang
 * Jika uang kurang, print "Uang tidak cukup untuk membeli gadget!"
 **/
void useUang(Mobita *m, int jumlah){
    if (UANG(*m) - jumlah < 0){
        printf("Uang tidak cukup untuk membeli gadget!\n");
    } else {
        UANG(*m) -= jumlah;
    }
}

/**
 * Menambahkan uang
 **/
void addUang(Mobita *m, int jumlah){
    UANG(*m) += jumlah;
}

/**
 * Mengubah posisi
 **/
void changePosisi(Mobita *m, int absis, int ordinat){
    Ordinat(POSISI(*m)) = ordinat;
    Absis(POSISI(*m)) = absis;
}