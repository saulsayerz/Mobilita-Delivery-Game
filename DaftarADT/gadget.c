#include "gadget.h"

/**
 * Menginisialisasi gadget
 **/
void createGadget(Gadget *g){
    NAMAGADGET(*g) = NAMAGADGETUNDEF;
    HARGAGADGET(*g) = HARGAGADGETUNDEF;
}

/**
 * Apakah gadget undef?
 **/
boolean isGadgetUNDEF(Gadget g){
    return NAMAGADGET(g) == NAMAGADGETUNDEF && HARGAGADGET(g) == HARGAGADGETUNDEF;
}

Gadget newGadget(char nama[], int harga)
{
    Gadget g;
    createGadget(&g);
    NAMAGADGET(g) = nama;
    HARGAGADGET(g) = harga;
    return g;
}

void displayName(char *nama)
{
    int i = 0;
    while ((*(nama + i) >= 65 && *(nama + i) <=122) || *(nama + i) == 32)
    {
        printf("%c", *(nama + i));
        i++;
    }
    printf(" ");
}