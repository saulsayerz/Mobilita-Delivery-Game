#ifndef INVENTORY_H
#define INVENTORY_H

#include "../gadget/gadget.h"

#define INVENTORYCAPACITY 5

typedef struct inventory
{
    Gadget listGadget[INVENTORYCAPACITY];
} Inventory;

#define GADGETINIDX(i, idx) (i).listGadget[(idx)]

/**
 * Menginisialisasi inventory
 **/
void createInventory(Inventory *i);

/**
 * Display Inventory
 **/
void displayInventory(Inventory i);

/**
 * Set Inventory in an index
 **/
void setGadgetFromInventoryOnIDX(Inventory *i, int idx, Gadget g);

/**
 * Delete gadget in Inventory in an index
 **/
void deleteGadgetFromInvetoryOnIDX(Inventory *i, int idx);

/**
 * Take gadget of idx
 * return the gadget
 * it cover the case if the gadget is undef
 **/
void takeGadgetFromInventory(Inventory *i, int idx, Gadget *g);

/**
 * Add gadget to inventory
 * Menambahkan ke kosong pertama
 **/
int addGadgetToInventory(Inventory *i, Gadget g);

/**
 * Apakah inventory penuh?
 **/
void isInventoryFull(Inventory i);

#endif