#include "gadget.h"
#include <stdio.h>
#include <string.h>

void createGadget(Gadget *g){
    IDGADGET(*g) = IDGADGETUNDEF;
    NAMAGADGET(*g) = NAMAGADGETUNDEF;
    HARGAGADGET(*g) = HARGAGADGETUNDEF;
}

boolean isGadgetUNDEF(Gadget g){
    return (strcmp(NAMAGADGET(g), NAMAGADGETUNDEF) == 0) && HARGAGADGET(g) == HARGAGADGETUNDEF;
}

Gadget newGadget(int id, char* nama, int harga)
{
    Gadget g;
    createGadget(&g);
    IDGADGET(g) = id;
    NAMAGADGET(g) = nama;
    HARGAGADGET(g) = harga;
    return g;
}

void displayName(char *nama)
{
    int i = 0;
    printf("%s", nama);
    printf(" ");
}


