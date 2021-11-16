#ifndef MOBITA_H
#define MOBITA_H

#include "../pesanan/todo.h"
#include "../inventory/inventory.h"
#include "../tas/tas.h"
#include "../map/point.h"
#include "../gadget/effect_list.h"
#include "../gadget/gadget.h"
#include "../mesin/wordmachine.h"

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
#define TAS_MOBITA(m) (m).tas
#define EFEK(m) (m).efek
/**
 * Inisialisasi Mobita
 **/
void createMobita(Mobita *m);

/**
 * Menambahkan satu unit ke waktu
 **/
void addOneToWaktu(Mobita *m);

/**
 * Menambahkan dua unit ke waktu
 **/
void addTwoToWaktu(Mobita *m);

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

void removeItemFromTasAndInProgress(Mobita *m);

void addItemToTasAndInProgress(Mobita *m, Pesanan p);

void decreasePerishableTime(Mobita *m);

void resetMostRecentlyPerishableTime(Mobita *m);

void effectHandlerChangePosisi(Mobita *m, int heavy, boolean pintuKemanaSajaEffect, boolean speedBoostEffect, boolean senterPembesarEffect);

/**
 * Mengubah posisi
 **/
void changePosisi(Mobita *m, int absis, int ordinat);

void useGadget(Mobita *player, Gadget g);
void decreasePerishableTime(Mobita *m);

#endif
