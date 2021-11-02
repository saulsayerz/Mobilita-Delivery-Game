#include <stdio.h>
#include "inventory.h"
/**
 * Menginisialisasi inventory
 **/
void createInventory(Inventory *i)
{
    int count = 0;
    Gadget undefGadget;
    createGadget(&undefGadget);
    while (count < INVENTORYCAPACITY)
    {
        GADGETINIDX(*i, count) = undefGadget;
        count++;
    }
}

/**
 * Display Inventory
 **/
void displayInventory(Inventory i){
    int idx = 0;
    Gadget temp;
    while (idx < INVENTORYCAPACITY){
        temp = GADGETINIDX(i, idx);
        printf("%d. ", idx+1);
        if (isGadgetUNDEF(temp)){
            printf("-\n");
        } else {
            printf(NAMAGADGET(temp),"\n");
        }
        idx++;
    }
}

/**
 * Set Inventory in an index
 **/
void setGadgetFromInventoryOnIDX(Inventory *i, int idx, Gadget g){
    GADGETINIDX(*i, idx) = g;
}

/**
 * Delete gadget in Inventory in an index
 **/
void deleteGadgetFromInvetoryOnIDX(Inventory *i, int idx)
{
    Gadget gadgetUndef;
    createGadget(&gadgetUndef);
    GADGETINIDX(*i, idx) = gadgetUndef;
}

/**
 * Take gadget of idx
 * return the gadget
 **/
void takeGadgetFromInventory(Inventory *i, int idx, Gadget *g)
{
    *g = GADGETINIDX(*i, idx);
    deleteGadgetFromInvetoryOnIDX(i, idx);   
}
/**
 * Add gadget to inventory
 * Menambahkan ke kosong pertama
 **/
int addGadgetToInventory(Inventory *i, Gadget g)
{
    // dapatkan gadget undef pertama
    int idx = 0;
    while (idx < INVENTORYCAPACITY && !isGadgetUNDEF(GADGETINIDX(*i, idx))){
        idx++;
    }

    if (idx >= INVENTORYCAPACITY){
        printf("Inventory tidak cukup untuk menyimpan gadget");
        return 0;
    } else {
        setGadgetFromInventoryOnIDX(i, idx, g);
        return 1;
    }
}