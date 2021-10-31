#ifndef MOBITA_H
#define MOBITA_H
#include "todo.h"
#include "inventory.h"
#include "./ADTPrimitif/point.h"

typedef struct mobita
{    
    Inventory inventory;
    int waktu;
    int uang;
    POINT posisi;
    Address toDoList;
    Address inProgress;
} Mobita;

#define INVENTORY(m) (m).inventory
#define WAKTU(m) (m).waktu
#define UANG(m) (m).uang
#define POSISI(m) (m).posisi
#define TODO(m) (m).toDoList
#define INPROGRESS(m) (m).inProgress

/**
 * Inisialisasi Mobita
 **/
void createMobita(Mobita *m);

/**
 * Menambahkan satu unit ke waktu
 **/
void addOneToWaktu(Mobita *m);

/**
 * Mengurangi uang
 **/
void useUang(Mobita *m, int jumlah);

/**
 * Menambahkan uang
 **/
void addUang(Mobita *m, int jumlah);

/**
 * Mengecek jumlah barang heavy pada in progress
 **/
int checkHeavy(Mobita *m);

/**
 * Mengubah posisi
 **/
void changePosisi(Mobita *m, int absis, int ordinat);




#endif
