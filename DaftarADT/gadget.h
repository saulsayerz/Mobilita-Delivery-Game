#ifndef GADGET_H
#define GADGET_H
#include "boolean.h"

#define IDGADGETUNDEF -1
#define NAMAGADGETUNDEF "GADGETUNDEF"
#define HARGAGADGETUNDEF -999

typedef struct gadget
{
    int id;
    char *nama;
    int harga;
} Gadget;

#define IDGADGET(g) (g).id
#define NAMAGADGET(g) (g).nama
#define HARGAGADGET(g) (g).harga

/**
 * Menginisialisasi gadget
 **/
void createGadget(Gadget *g);

/**
 * Apakah gadget undef?
 **/
boolean isGadgetUNDEF(Gadget g);

Gadget newGadget(int id, char *nama, int harga);

void displayName(char *nama);

#endif