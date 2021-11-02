void pickUp(Map peta, Queue *urutan, Mobita *player)
{
    int i, x, y;
    x = Absis(POSISI(*player));
    y = Ordinat(POSISI(*player));

    char lokasiMobita;
    for (i = 0; i < NEFF(MAPLOC(peta)); i++)
    {
        if (x == Absis(LOCPOINT(ELEMEN(MAPLOC(peta), i))) && y == Ordinat(LOCPOINT(ELEMEN(MAPLOC(peta), i))))
        {
            lokasiMobita = LOCNAME(ELEMEN(MAPLOC(peta), i));
        }
    }
    int idx = 0;
    boolean exist = false;
    Address p = TODO(*player);
    printf("Nama lokasi mobita sekarang: %c\n", lokasiMobita);
    while (p != NULL && !exist)
    {
        if (p != NULL && lokasiMobita == ASAL(INFO(p)))
        {
            exist = true;
        } else 
        {
            p = NEXT(p);
            idx++;
        }
    }

    if (exist)
    {
        printf("Pesanan berupa ");
        displayJenis(&INFO(p));
        printf(" berhasil diambil!!\n");
        printf("Tujuan Pesanan: %c\n", TUJUAN(INFO(p)));
        insertFirst(&INPROGRESS(*player), INFO(p));
        deleteAt(&TODO(*player), idx);
    }
    else
    {
        printf("Pesanan tidak ditemukan!");
    }
}