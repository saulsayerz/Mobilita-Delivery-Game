#include "gadget.h"
/**
 * Menginisialisasi gadget
 **/
void createGadget(Gadget *g){
    IDGADGET(*g) = IDGADGETUNDEF;
    NAMAGADGET(*g) = NAMAGADGETUNDEF;
    HARGAGADGET(*g) = HARGAGADGETUNDEF;
}

/**
 * Apakah gadget undef?
 **/
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

/**
 * Menggunakan gadget untuk memberikan efek
 */
void useGadget(Mobita *player, Gadget g){
    Tas* tas = &TAS(*player);
    int newMaxItem;
    if (g.nama == "Kain Pembungkus Waktu"){
        
    } else if (g.nama == "Pintu Kemana Saja"){
        
    } else if (g.nama == "Senter Pembesar"){
        setMaxItem(tas, getMaxItem(tas)*2);
    } else if (g.nama == "Senter Pengecil"){

    } else if (g.nama == "Mesin Waktu"){
        
    } else {
        printf("Gadget belum bisa dipakai");
    }
}