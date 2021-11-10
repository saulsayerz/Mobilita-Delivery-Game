#include "gadget.h"
#include "effect_list.h"


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

/**
 * Menggunakan gadget untuk memberikan efek
 */
void useGadget(Mobita *player, Gadget g){
    Tas* tas = &TAS(*player);
    int newMaxItem;
    Item itemTmp;
    
    // definisi
    char HEAVY = 'H';

    if (g.nama == "Kain Pembungkus Waktu"){
        //perishable item return
        addEffect(&EFEK(*player), KAIN_PEMBUNGKUS_WAKTU);
    } else if (g.nama == "Pintu Kemana Saja"){
        // di move, kalau efek ini ada, maka cost waktu tidak perlu
        // efek dihilangkan tepat setelah digunakan, harus ada pengecekan di akhir
        // ISSUE: dia harusnya bisa ke segala titik.
        addEffect(player, PINTU_KEMANA_SAJA);
    } else if (g.nama == "Senter Pembesar"){
        setMaxItem(tas, getMaxItem(tas)*2);
    } else if (g.nama == "Senter Pengecil"){
        // DONE: saat dropoff/return cek apakah efek ini ada. kalau ada hapus
        // DONE:saat move cek apakah efek ini ada kalau ada penambahannya bisa kurang 1
        itemTmp = TOP_TAS(*tas);
        if (JENIS(itemTmp) != HEAVY){
            printf("Item teratas tas bukan item heavy, yakin?\n");
        } else {
            addEffect(&EFEK(*player),SENTER_PENGECIL);
        }
    } else if (g.nama == "Mesin Waktu"){
        // time berkurang 50
        // pesanan pada jangka waktu 50 tidak akan hilang
        // dengan kata lain, akan masuk ke to do list
        // tidak akan muncul lagi ke to do list saat waktunya dilampaui
        // jadi hanya dipindah saja ke to do list
        // sehingga di waktu masuknya tidak perlu ada pemunculan  lagi

        // harus ada traverse lagi di inprogress

        // questions: apakah messin waktu menghilangkan reward yang didapat?
        // apakah mesin waktu merewind pekerjaan menjadi undone?
        // jika iya, berarti harus ada trackernya dong

        decrementWaktu(player, 50);

    } else {
        printf("Gadget belum bisa dipakai");
    }
}