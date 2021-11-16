#include "gadget.h"
#include <stdio.h>

void createGadget(Gadget *g){
    IDGADGET(*g) = IDGADGETUNDEF;
    NAMAGADGET(*g) = NAMAGADGETUNDEF;
    HARGAGADGET(*g) = HARGAGADGETUNDEF;
}

boolean isGadgetUNDEF(Gadget g){
    return !strings_not_equal_v2(NAMAGADGET(g), NAMAGADGETUNDEF) && HARGAGADGET(g) == HARGAGADGETUNDEF;
}

Gadget newGadget(int id, char nama[], int harga)
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
    printf("%s", nama);
}


