#include "mobita.h"
#include <stdio.h>
/**
 * Inisialisasi Mobita
 **/
int speedBoostCounter;

void createMobita(Mobita *m)
{
    Inventory i;
    EffectList l;
    Tas t;
    // inisialisasi objek anak
    POINT p = MakePOINT(0, 0);
    createInventory(&i);
    createEffectList(&l);
    createTas(&t);
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
void addOneToWaktu(Mobita *m)
{
    WAKTU(*m) += 1;
}

/**
 * Menambahkan dua unit ke waktu
 **/
void addTwoToWaktu(Mobita *m)
{
    WAKTU(*m) += 2;
}

// decrement waktu
void decrementWaktu(Mobita *m, int n)
{
    int newWaktu = WAKTU(*m) - n;
    if (newWaktu < 0)
    {
        WAKTU(*m) = 0;
    }
    else
    {
        WAKTU(*m) = newWaktu;
    }
}

/**
 * Mengurangi uang
 * Jika uang kurang, print "Uang tidak cukup untuk membeli gadget!"
 **/
void useUang(Mobita *m, int jumlah)
{
    if (UANG(*m) - jumlah < 0)
    {
        printf("Uang tidak cukup untuk membeli gadget!\n");
    }
    else
    {
        UANG(*m) -= jumlah;
    }
}

/**
 * Menambahkan uang
 **/
void addUang(Mobita *m, int jumlah)
{
    UANG(*m) += jumlah;
}

/**
 * Mengecek apakah jumlah item heavy pada inprogress
 **/
int checkHeavy(Mobita *m)
{
    int jumlahHeavy = 0;
    Address p = INPROGRESS(*m);
    while (p != NULL)
    {
        if (JENIS(INFO(p)) == 'H')
        {
            jumlahHeavy++;
        }
        p = NEXT(p);
    }
    return jumlahHeavy;
}

void removeItemFromTasAndInProgress(Mobita *m)
{
    deleteFirst(&INPROGRESS(*m));
    Pesanan garbage;
    popTas(&TAS_MOBITA(*m), &garbage);
};

void addItemToTasAndInProgress(Mobita *m, Pesanan p)
{
    pushTas(&TAS_MOBITA(*m), p);
    insertFirst(&INPROGRESS(*m), p);
};

void decreasePerishableTime(Mobita *m)
{
    Address p = INPROGRESS(*m);
    int i = 0;
    while (p != NULL)
    {
        if (JENIS(INFO(p)) == 'P' && PERISH(INFO(p)) > 0)
        {
            PERISH(INFO(p)) -= 1;
        }

        if (JENIS(INFO(p)) == 'P' && PERISH(INFO(p)) == 0)
        {
            deleteAt(&INPROGRESS(*m), i);
            printf("Pesanan hangus\n");
        }
        p = NEXT(p);
        i++;
    }

    decreasePerishableTimeInTas(&TAS_MOBITA(*m));
}

void resetMostRecentlyPerishableTime(Mobita *m)
{
    int resetValue = UPPERMOST_PERISHABLE_INITIAL_TIME(TAS_MOBITA(*m));
    if (resetValue == -1)
    {
        // UDAH
    }
    else
    {
        Address p = INPROGRESS(*m);
        while (JENIS(INFO(p)) == 'P')
        {
            p = NEXT(p);
        }

        if (JENIS(INFO(p)) == 'P')
        {
            PERISH(INFO(p)) = resetValue;
        }

        resetMostRecentlyPerishableTimeInTas(&TAS_MOBITA(*m));
    }
}

void effectHandlerChangePosisi(Mobita *m, int heavy, boolean pintuKemanaSajaEffect, boolean speedBoostEffect, boolean senterPembesarEffect)
{

    if (heavy != 0 && !pintuKemanaSajaEffect)
    {
        int i;
        addOneToWaktu(m);
        for (i = 0; i < heavy; i++)
        {
            addOneToWaktu(m);
        }
        decreasePerishableTime(m);
    }
    else if (!pintuKemanaSajaEffect && speedBoostEffect)
    {
        speedBoostCounter += 1;
        if (speedBoostCounter % 2 == 0)
        {
            addOneToWaktu(m);
        }

        if (speedBoostCounter == 10)
        {
            speedBoostCounter = 0;
            removeEffect(&EFEK(*m), SPEED_BOOST);
        }
    }
    else if (!pintuKemanaSajaEffect)
    {
        addOneToWaktu(m);
        decreasePerishableTime(m);
    }

    if (heavy != 0 && senterPembesarEffect)
    {
        decrementWaktu(m, 1);
    }

    if (pintuKemanaSajaEffect)
    {
        printf("Kamu berpindah dengan instan!\n");
    }
}

/**
 * Mengubah posisi
 **/
void changePosisi(Mobita *m, int absis, int ordinat)
{
    Ordinat(POSISI(*m)) = ordinat;
    Absis(POSISI(*m)) = absis;

    EffectList efek = EFEK(*m);
    boolean senterPembesarEffect =
        isEffectExist(efek, SENTER_PENGECIL) && JENIS(TOP_TAS(TAS_MOBITA(*m))) == 'H';
    boolean pintuKemanaSajaEffect = isEffectExist(efek, PINTU_KEMANA_SAJA);
    boolean speedBoostEffect = isEffectExist(efek, SPEED_BOOST);

    int heavy = checkHeavy(m);
    effectHandlerChangePosisi(m, heavy, pintuKemanaSajaEffect, speedBoostEffect, senterPembesarEffect);
}

/**
 * Menggunakan gadget untuk memberikan efek
 */
void useGadget(Mobita *player, Gadget g)
{
    Tas *tas = &TAS_MOBITA(*player);
    Item itemTmp;

    // definisi
    char HEAVY = 'H';

    if (!strings_not_equal_v2(NAMAGADGET(g), KAIN_PEMBUNGKUS_WAKTU))
    {
    }
    else if (!strings_not_equal_v2(NAMAGADGET(g), PINTU_KEMANA_SAJA))
    {
        printf("Kamu memakai Pintu Kemana Saja, di MOVE selanjutnya, kamu bisa berpindah dengan instan!\n");
        addEffect(&EFEK(*player), PINTU_KEMANA_SAJA);
    }
    else if (!strings_not_equal_v2(NAMAGADGET(g), SENTER_PEMBESAR))
    {
        printf("Kamu memakai Senter Pembesar, TAS kamu membesar dua kali lipat!\n");
        setMaxItem(tas, MAX_ITEM(*tas) * 2);
    }
    else if (!strings_not_equal_v2(NAMAGADGET(g), SENTER_PENGECIL))
    {
        itemTmp = TOP_TAS(*tas);
        if (JENIS(itemTmp) != HEAVY)
        {
            printf("Item teratas tas bukan item heavy, kamu gaakan pakai ini karena tidak akan berefek!\n");
        }
        else
        {
            printf("Kamu memakai Senter Pengecil, di bagian atas tas itu item heavy, efek buruknya dia gaakaan ngaruh ke kamu!");
            addEffect(&EFEK(*player), SENTER_PENGECIL);
        }
    }
    else if (!strings_not_equal_v2(NAMAGADGET(g), MESIN_WAKTU))
    {
        decrementWaktu(player, 50);
    }
    else
    {
        printf("Gadget belum bisa dipakai");
    }
}