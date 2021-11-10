#include "mobita.h"
#include "effect_list.h"
/**
 * Inisialisasi Mobita
 **/
void createMobita(Mobita *m){
    Inventory i;
    EffectList l;
    Tas t;
    // inisialisasi objek anak
    POINT p = MakePOINT(0, 0);
    createInventory(&i);
    createEffectList(&l);

    // assign tiap properti objek
    INVENTORY(*m) = i;
    UANG(*m) = 10000;
    WAKTU(*m) = -1;
    POSISI(*m) = p;
    TODO(*m) = NULL;
    INPROGRESS(*m) = NULL;
    EFEK(*m) = l;
    TAS_MOBITA(*m) = t;
}

/**
 * Menambahkan satu unit ke waktu
 **/
void addOneToWaktu(Mobita *m){
    WAKTU(*m) += 1;
}

/**
 * Menambahkan dua unit ke waktu
 **/
void addTwoToWaktu(Mobita *m){
    WAKTU(*m) += 2;
}

// decrement waktu
void decrementWaktu(Mobita *m, int n){
    int newWaktu = WAKTU(*m) - n;
    if(newWaktu < 0){
        WAKTU(*m) = 0;
    } else {
        WAKTU(*m) = newWaktu;
    }
}

/**
 * Mengurangi uang
 * Jika uang kurang, print "Uang tidak cukup untuk membeli gadget!"
 **/
void useUang(Mobita *m, int jumlah){
    if (UANG(*m) - jumlah < 0){
        printf("Uang tidak cukup untuk membeli gadget!\n");
    } else {
        UANG(*m) -= jumlah;
    }
}

/**
 * Menambahkan uang
 **/
void addUang(Mobita *m, int jumlah){
    UANG(*m) += jumlah;
}

/**
 * Mengecek apakah jumlah item heavy pada inprogress
 **/
int checkHeavy(Mobita *m){
    int jumlahHeavy = 0;
    Address p = INPROGRESS(*m);
    while (p != NULL) {
        if (JENIS(INFO(p)) == 'H'){
            jumlahHeavy++;
        }
        p = NEXT(p);
    }
    return jumlahHeavy;
}


/**
 * Mengubah posisi
 **/
void changePosisi(Mobita *m, int absis, int ordinat){
    Ordinat(POSISI(*m)) = ordinat;
    Absis(POSISI(*m)) = absis;

    EffectList efek = EFEK(*m);    
    boolean senterPembesarEffect = 
        isEffectExist(efek, SENTER_PENGECIL)
        && JENIS(TOP_TAS(TAS_MOBITA(*m))) == 'H';
    boolean pintuKemanaSajaEffect = isEffectExist(efek, PINTU_KEMANA_SAJA);

    int heavy = checkHeavy(m);
    if (heavy != 0 && !pintuKemanaSajaEffect){
        int i;
        addOneToWaktu(m);
        for(i = 0;i<heavy;i++){
            addOneToWaktu(m);
        }
    } else if (!pintuKemanaSajaEffect) {
        addOneToWaktu(m);
    }

    if (heavy != 0 && senterPembesarEffect){
        decrementWaktu(m, 1);
    }

    if(pintuKemanaSajaEffect){
        printf("Kamu berpindah dengan instan!\n");
    }
}

/**
 * Menggunakan gadget untuk memberikan efek
 */
void useGadget(Mobita *player, Gadget g){
    Tas* tas = &TAS_MOBITA(*player);
    int newMaxItem;
    Item itemTmp;
    
    // definisi
    char HEAVY = 'H';

    if (g.nama == "Kain Pembungkus Waktu"){
        addEffect(&EFEK(*player), KAIN_PEMBUNGKUS_WAKTU);
    } else if (g.nama == "Pintu Kemana Saja"){
        addEffect(&EFEK(*player), PINTU_KEMANA_SAJA);
    } else if (g.nama == "Senter Pembesar"){
        setMaxItem(tas, MAX_ITEM(*tas)*2);
    } else if (g.nama == "Senter Pengecil"){
        itemTmp = TOP_TAS(*tas);
        if (JENIS(itemTmp) != HEAVY){
            printf("Item teratas tas bukan item heavy, yakin?\n");
        } else {
            addEffect(&EFEK(*player),SENTER_PENGECIL);
        }
    } else if (g.nama == "Mesin Waktu"){
        decrementWaktu(player, 50);
    } else {
        printf("Gadget belum bisa dipakai");
    }
}