#include "gadget.h"
#include "mobita.h"

void createGadget(Gadget *g){
    IDGADGET(*g) = IDGADGETUNDEF;
    NAMAGADGET(*g) = NAMAGADGETUNDEF;
    HARGAGADGET(*g) = HARGAGADGETUNDEF;
}

boolean isGadgetUNDEF(Gadget g){
    return NAMAGADGET(g) == NAMAGADGETUNDEF && HARGAGADGET(g) == HARGAGADGETUNDEF;
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
    int i = 0;
    while ((*(nama + i) >= 65 && *(nama + i) <=122) || *(nama + i) == 32)
    {
        printf("%c", *(nama + i));
        i++;
    }
    printf(" ");
}


