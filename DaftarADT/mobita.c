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
    WAKTU(*m) = -1; // karena di awal dia harus change posisi ke headquarter, maka waktu += 1
    POSISI(*m) = p;
}

/**
 * Menambahkan satu unit ke waktu
 **/
void addOneToWaktu(Mobita *m){
    WAKTU(*m) += 1;
}

/**
 * Menambahkan satu unit ke waktu
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
 * Mengecek apakah jumlah item heavy pada inprogress
 **/
int checkHeavy(Mobita *m){
    int jumlahHeavy = 0;
    Address p = INPROGRESS(*m);
    while (p != NULL) {
        if (JENIS(INFO(p)) == 'H'){
            jumlahHeavy++;
        }
        p = NEXT(p);
    }
    return jumlahHeavy;
}

/**
 * Mengubah posisi
 **/
void changePosisi(Mobita *m, int absis, int ordinat){
    Ordinat(POSISI(*m)) = ordinat;
    Absis(POSISI(*m)) = absis;

    int heavy = checkHeavy(m);
    if (heavy != 0){
        int i;
        for(i = 0;i<heavy;i++){
            addTwoToWaktu(m);
        }
    } else {
        addOneToWaktu(m);
    }
}