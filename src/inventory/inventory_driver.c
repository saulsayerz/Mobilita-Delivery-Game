#include "inventory.h"
#include <stdio.h>

// UNCOMMENT JIKA MENGGUNAKAN 'CODE RUNNER'
// #include "inventory.c"
// #include "../gadget/gadget.c"

int main()
{
    // inisialisasi inventory
    Inventory i;
    createInventory(&i);

    // inisialisasi gadget untuk dimasukkan ke dalam inventory
    Gadget g1, g2, g3, g4;
    createGadget(&g1);
    createGadget(&g2);
    createGadget(&g3);
    createGadget(&g4);

    //g1
    NAMAGADGET(g1) = "g1";
    HARGAGADGET(g1) = 100;
    IDGADGET(g1) = 1;

    //g2
    NAMAGADGET(g2) = "g2";
    HARGAGADGET(g2) = 200;
    IDGADGET(g2) = 2;

    //g3 sebagai gadget undef
    //g4
    NAMAGADGET(g4) = "g4";
    HARGAGADGET(g4) = 300;
    IDGADGET(g4) = 4;

    /**      TESTING       **/
    // menambahkan gadget ke inventory
    // expected behavior:
    //   inventory ter-append
    addGadgetToInventory(&i, g1);
    addGadgetToInventory(&i, g2);
    // test
    displayInventory(i);
    printf("------------------------\n");

    // mengambil gadget dari inventory
    // expected behavior:
    //  g3 berisi gadget di indeks 1 (g2), dan g2 hilang di inventory
    takeGadgetFromInventory(&i, 1, &g3);
    // test
    printf("g3 menjadi: %s\n", NAMAGADGET(g3));
    displayInventory(i);

    printf("------------------------\n");
    // set gadget di suatu indeks
    // expected behavior:
    //      g4 berisi gadget di indeks 0 (g1), dan g1 hilang di inventory
    setGadgetFromInventoryOnIDX(&i, 0, g4);
    // test
    displayInventory(i);

    return 0;
}