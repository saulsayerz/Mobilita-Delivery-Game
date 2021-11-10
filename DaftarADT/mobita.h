#ifndef MOBITA_H
#define MOBITA_H
#include "todo.h"
#include "inventory.h"
#include "tas.h"
#include "./ADTPrimitif/point.h"

typedef struct mobita
{    
    Inventory inventory;
    int waktu;
    int uang;
    POINT posisi;
    List toDoList;
    List inProgress;
    Tas tas;
    EffectList efek;
} Mobita;

#define INVENTORY(m) (m).inventory
#define WAKTU(m) (m).waktu
#define UANG(m) (m).uang
#define POSISI(m) (m).posisi
#define TODO(m) (m).toDoList
#define INPROGRESS(m) (m).inProgress
#define TAS(m) (m).tas
#define EFEK(m) (m).efek
/**
 * Inisialisasi Mobita
 **/
void createMobita(Mobita *m);

/**
 * Menambahkan satu unit ke waktu
 **/
void addOneToWaktu(Mobita *m);

// kurangi waktu sebanyak n
void decrementWaktu(Mobita *m, int n);

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
