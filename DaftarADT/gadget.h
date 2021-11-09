#ifndef GADGET_H
#define GADGET_H
#include "boolean.h"
#include "mobita.h"
#define NAMAGADGETUNDEF "GADGETUNDEF"
#define HARGAGADGETUNDEF -999

typedef struct gadget
{
    char *nama;
    int harga;
} Gadget;

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

Gadget newGadget(char *nama, int harga);

void displayName(char *nama);

/**
 * Menggunakan gadget untuk memberikan efek
 */
void useGadget(Mobita *player, Gadget g);

#endif