#include "gadget.h"

// UNCOMMENT JIKA MENGGUNAKAN 'code-runner'
// #include "gadget.c"
void createGadget(Gadget *g);

/**
 * Apakah gadget undef?
 **/
boolean isGadgetUNDEF(Gadget g);

Gadget newGadget(int id, char *nama, int harga);

void displayName(char *nama);
int main()
{
    // inisialisasi gadget
    Gadget g1, g2, g3, g4;
    createGadget(&g1);
    createGadget(&g2);
    createGadget(&g3);

    //g1
    NAMAGADGET(g1) = "g1";
    HARGAGADGET(g1) = 100;
    IDGADGET(g1) = 1;

    /**      TESTING       **/

    // mengecek apakah gadget baru terbentuk
    // expected result:
    //   properti g4 sesuai dengan masukan
    g4 = newGadget(4, "g4", 200);
    displayName(NAMAGADGET(g4));
    printf("ID: %d\n", IDGADGET(g4));
    printf("Harga: %d\n", HARGAGADGET(g4));

    printf("------------------------\n");

    // mengecek apakah gadget undef
    // expected result:
    //      g1 tidak undef, dan g3 undef
    if (!isGadgetUNDEF(g1))
    {
        printf("Gadget g1 bukan gadget undef\n");
    }
    if (isGadgetUNDEF(g3))
    {
        printf("Gadget g3 adalah gadget undef\n");
    }
    printf("------------------------\n");

    // berhasil menampilkan nama gadget
    // expected result:
    //      nama g2 terprint "g2"
    displayName(NAMAGADGET(g2));
    printf("------------------------\n");

    return 0;
}