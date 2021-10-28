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