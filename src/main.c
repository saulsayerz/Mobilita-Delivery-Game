#include <stdio.h>
#include "../DaftarADT/map.c"
#include "../DaftarADT/pesanan.c"
#include "../DaftarADT/mobita.c"
#include "../DaftarADT/inventory.c"
#include "../DaftarADT/gadget.c"
#include "../DaftarADT/pcolor.c"
#include "../DaftarADT/ADTPrimitif/Queue.c"
#include "../DaftarADT/todo.c"
#include "../DaftarADT/node.c"
#include "../DaftarADT/effect_list.c"
#include "../DaftarADT/tas.c"

// define global variables

void move(Map peta, Queue *urutan, Mobita *player)
{
    printf("POSISI YANG DAPAT DICAPAI\n");
    int i, x, y, baris, kolom = 0, j, k;
    x = Absis(POSISI(*player)); // posisi sementara nobita
    y = Ordinat(POSISI(*player));
    ListDinamis dapatdicapai;
    CONTENTS(dapatdicapai) = (Lokasi *)malloc(26 * sizeof(Lokasi));
    NEFF(dapatdicapai) = 0;
    KAPASITAS(dapatdicapai) = 26;
    boolean efekPintuKemanaSaja = isEffectExist(EFEK(*player), PINTU_KEMANA_SAJA);
    if (efekPintuKemanaSaja)
    {
        printf("Kamu menggunakan gadget Pintu Kemana Saja!, kamu bisa pergi kemana pun secara instan!\n");
    }
    for (i = 0; i < NEFF(MAPLOC(peta)); i++)
    { // searching barisnya
        if (x == Absis(LOCPOINT(ELEMEN(MAPLOC(peta), i))) && y == Ordinat(LOCPOINT(ELEMEN(MAPLOC(peta), i))))
        {
            baris = i; // harusnya pake while deh algoritma searching tapi mager
        }
    }

    for (j = 0; j < NEFF(MAPLOC(peta)); j++)
    { // ngecek di matriks MAPADJ(peta) bisa dicapai ga
        if (ELEMENM(MAPADJ(peta), baris, j) == '1' || efekPintuKemanaSaja)
        {
            ELEMEN(dapatdicapai, kolom) = ELEMEN(MAPLOC(peta), j);
            kolom++;
            NEFF(dapatdicapai) += 1;
        }
    }
    for (k = 1; k <= NEFF(dapatdicapai); k++)
    {
        printf("%d. %c (%d,%d)\n", k, LOCNAME(ELEMEN(dapatdicapai, k - 1)), Absis(LOCPOINT(ELEMEN(dapatdicapai, k - 1))), Ordinat(LOCPOINT(ELEMEN(dapatdicapai, k - 1))));
    }
    printf("Posisi yang dipilih? (ketik 0 jika ingin kembali)\n");
    int pilihan;
    printf("ENTER COMMAND: ");
    scanf("%d", &pilihan);
    while (pilihan < 0 || pilihan > NEFF(dapatdicapai))
    {
        printf("Input salah! Masukkan ulang command\nCOMMAND: ");
        scanf("%d", &pilihan);
    }
    if (pilihan == 0)
    {
        printf("Kembali\n");
    }
    else
    {
        x = Absis(LOCPOINT(ELEMEN(dapatdicapai, pilihan - 1)));
        y = Ordinat(LOCPOINT(ELEMEN(dapatdicapai, pilihan - 1)));
        changePosisi(player, x, y);
        removeEffect(&EFEK(*player), PINTU_KEMANA_SAJA);
        printf("Waktu : %d\n", WAKTU(*player));
        printf("Mobita sekarang berada di titik %c (%d,%d)!\n", LOCNAME(ELEMEN(dapatdicapai, pilihan - 1)), x, y);
    }
}

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
        }
        else
        {
            p = NEXT(p);
            idx++;
        }
    }

    if (exist && !isTasFull(TAS_MOBITA(*player)))
    {
        if (JENIS(INFO(p)) == 'H' && isEffectExist(EFEK(*player), SPEED_BOOST))
        {
            printf("Kamu baru saja mempickup item heavy, ability SPEED BOOST mu hilang :(");
            removeEffect(
                &EFEK(*player),
                SPEED_BOOST);
        } 
        
        if (JENIS(INFO(p)) == 'P'){
            setUppermostPerishableInitialTime(&TAS_MOBITA(*player), PERISH(INFO(p)));
        }
        printf("Pesanan berupa ");
        displayJenis(&INFO(p));
        printf(" berhasil diambil!!\n");
        printf("Tujuan Pesanan: %c\n", TUJUAN(INFO(p)));
        addItemToTasAndInProgress(player, INFO(p));
        deleteAt(&TODO(*player), idx);
    }
    else if (!exist)
    {
        printf("Pesanan tidak ditemukan!\n");
    } else if (isTasFull(TAS_MOBITA(*player)))
    {
        printf("Tas mu penuh!\n");
    }
}

void dropOff(Map peta, Queue *urutan, Mobita *player)
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
    Address p = INPROGRESS(*player);
    printf("Nama lokasi mobita sekarang: %c\n", lokasiMobita);
    if (p != NULL && lokasiMobita == TUJUAN(INFO(p)))
    {
        printf("Pesanan ");
        displayJenis(&INFO(p));
        printf(" berhasil diantarkan!\n");
        if (JENIS(INFO(p)) == 'N')
        {
            printf("Uang yang didapatkan : 200 Yen.");
            UANG(*player) += 200;
        }
        else if (JENIS(INFO(p)) == 'H')
        {
            printf("Uang yang didapatkan : 400 Yen.\n");
            UANG(*player) += 400;
            if (checkHeavy(player) > 1)
            {
                printf("Kamu masih memiliki item Heavy lain dalam tas, tidak dapat ability SPEED BOOST!!\n");
            }
            else
            {
                addEffect(&EFEK(*player), SPEED_BOOST);
                printf("Mendapat ability: SPEED BOOST!");
                speedBoostCounter = 0;
            }
        }
        else if (JENIS(INFO(p)) == 'P')
        {
            printf("Uang yang didapatkan : 400 Yen.");
            UANG(*player) += 400;
            setMaxItem(&TAS_MOBITA(*player), MAX_ITEM(TAS_MOBITA(*player)) + 1);
            setUppermostPerishableInitialTime(&TAS_MOBITA(*player), PERISH(INFO(p)));
            printf("Mendapat ability: INCREASE CAPACITY!");
        }
        removeItemFromTasAndInProgress(player);
        
        // menghapus efek senter pengecil setelah dropoff
        if (isEffectExist(EFEK(*player), SENTER_PENGECIL))
        {
            removeEffect(&EFEK(*player), SENTER_PENGECIL);
        }
    }
    else
    {
        printf("Tidak ada pesanan yang dapat diantarkan!");
    }
    printf("\n");
}

void displayMapColor(Map peta, Queue *urutan, Mobita *player)
{ //INI BELUM JADIII
    Matrix m;
    ROWS(m) = MAPROW(peta) + 2;
    COLS(m) = MAPCOL(peta) + 2;
    Address p;
    int cetaknobita, cetaktodo, cetakprogress, cetakdicapai;
    int i, j, x, y, baris = 0, kolom = 0, k;
    x = Absis(POSISI(*player)); // posisi sementara nobita
    y = Ordinat(POSISI(*player));
    POINT titik = MakePOINT(0, 0);
    ListDinamis dapatdicapai;
    CONTENTS(dapatdicapai) = (Lokasi *)malloc(26 * sizeof(Lokasi));
    NEFF(dapatdicapai) = 0;
    KAPASITAS(dapatdicapai) = 26;
    for (i = 0; i < NEFF(MAPLOC(peta)); i++)
    { // searching barisnya
        if (x == Absis(LOCPOINT(ELEMEN(MAPLOC(peta), i))) && y == Ordinat(LOCPOINT(ELEMEN(MAPLOC(peta), i))))
        {
            baris = i; // harusnya pake while deh algoritma searching tapi mager
        }
    }
    for (j = 0; j < NEFF(MAPLOC(peta)); j++)
    { // ngecek di matriks MAPADJ(peta) bisa dicapai ga
        if (ELEMENM(MAPADJ(peta), baris, j) == '1')
        {
            ELEMEN(dapatdicapai, kolom) = ELEMEN(MAPLOC(peta), j);
            kolom++;
            NEFF(dapatdicapai) += 1;
        }
    }
    // printf("%d\n", NEFF(dapatdicapai));
    for (i = 0; i < MAPROW(peta) + 2; i++)
    {
        for (j = 0; j < MAPCOL(peta) + 2; j++)
        {
            if (i == 0 || j == 0 || i == MAPROW(peta) + 1 || j == MAPCOL(peta) + 1)
            {
                ELEMENM(m, i, j) = '*';
            }
            else
            {
                ELEMENM(m, i, j) = ' ';
            }
        }
    }
    for (i = 0; i < NEFF(MAPLOC(peta)); i++)
    {
        x = Absis(LOCPOINT(ELEMEN(MAPLOC(peta), i)));
        y = Ordinat(LOCPOINT(ELEMEN(MAPLOC(peta), i)));
        ELEMENM(m, x, y) = LOCNAME(ELEMEN(MAPLOC(peta), i));
    }
    for (i = 0; i < ROWS(m); i++)
    {
        for (j = 0; j < COLS(m); j++)
        {
            cetaknobita = 0;
            cetaktodo = 0;
            cetakprogress = 0;
            cetakdicapai = 0;
            if (i == Absis(POSISI(*player)) && j == Ordinat(POSISI(*player))) //INI BERARTI LOKASI MOBITA (WARNA KUNING)
            {
                print_yellow(ELEMENM(m, i, j)); // harusnya pake while deh algoritma searching tapi mager
                cetaknobita = 1;
            }
            if (!isEmpty(INPROGRESS(*player)) && !cetaknobita)
            {
                titik = NameToPoint(peta, TUJUAN(INFO(INPROGRESS(*player))));
                if (i == Absis(titik) && j == Ordinat(titik))
                {
                    print_blue(ELEMENM(m, i, j));
                    cetakprogress = 1;
                }
            }
            if (!cetakprogress && !cetaknobita)
            {
                p = TODO(*player);
                while (p != NULL)
                {
                    titik = NameToPoint(peta, ASAL(INFO(p)));
                    if (i == Absis(titik) && j == Ordinat(titik))
                    {
                        cetaktodo = 1;
                    }
                    p = NEXT(p);
                }
                if (cetaktodo)
                {
                    print_red(ELEMENM(m, i, j));
                }
            }
            for (k = 0; k < NEFF(dapatdicapai); k++)
            {
                if (Absis(LOCPOINT(ELEMEN(dapatdicapai, k))) == i && Ordinat(LOCPOINT(ELEMEN(dapatdicapai, k))) == j)
                {
                    cetakdicapai = 1;
                    //TulisPOINT(LOCPOINT(ELEMEN(dapatdicapai,k)));
                }
            }
            if (!cetakprogress && !cetaknobita && !cetaktodo && cetakdicapai)
            {
                print_green(ELEMENM(m, i, j));
            }
            if (!cetakprogress && !cetaknobita && !cetakdicapai && !cetaktodo)
            {
                printf("%c", ELEMENM(m, i, j));
            }
        }
        printf("\n");
    }
}

void buyGadget(Mobita *player, Gadget *gadget, Map *peta)
{
    POINT position = POSISI(*player);
    POINT headQuarter = NameToPoint(*peta, '8');

    if (EQ(position, headQuarter))
    {
        int i;
        printf("\n");
        printf("Uang anda sekarang: %d Yen\n", UANG(*player));
        printf("Gadget yang tersedia: \n");
        for (i = 0; i < 5; i++)
        {
            printf("%d. ", (i + 1));
            displayName(NAMAGADGET(*(gadget + i)));
            printf("(%d Yen)", HARGAGADGET(*(gadget + i)));
            printf("\n");
        }
        printf("Gadget mana yang ingin kau beli? (ketik 0 jika ingin kembali)\n");
        printf("ENTER COMMAND: ");
        int choice;
        scanf("%d", &choice);
        if (choice)
        {
            Gadget wishlist = *(gadget + choice - 1);
            if (UANG(*player) < HARGAGADGET(wishlist))
            {
                printf("Uang tidak cukup untuk membeli gadget, silahkan top up.\n");
            }
            else
            {
                int success = addGadgetToInventory(&INVENTORY(*player), wishlist);
                if (success)
                {
                    useUang(player, HARGAGADGET(wishlist));
                    displayName(NAMAGADGET(wishlist));
                    printf("berhasil dibeli!\n");
                    printf("Uang anda sekarang: %d Yen\n", UANG(*player));
                }
            }
        }
    }
    else
    {
        printf("Pembelian gadget hanya dapat dilakukan di headquarters.\n");
    }
}

void inventoryCommand(Mobita *player)
{
    // deklarasi
    int choice;
    int gadgetIdx;
    boolean isChoiceValid;
    Gadget gadgetUsed;
    createGadget(&gadgetUsed);

    // tampilkan inventory
    displayInventory(INVENTORY(*player));

    // tanya gadget yang ingin digunakan
    printf("Gadget mana yang ingin digunakan? (ketik 0 jika ingin kembali)\n");
    printf("ENTER COMMAND: ");
    scanf("%d", &choice);

    // pemrosesan pilihan
    isChoiceValid = (choice > 0 && choice <= INVENTORYCAPACITY);
    if (choice && isChoiceValid)
    {
        gadgetIdx = choice - 1;
        takeGadgetFromInventory(
            &INVENTORY(*player),
            gadgetIdx,
            &gadgetUsed);

        // cek apakah gadget yang diambil undef
        if (isGadgetUNDEF(gadgetUsed))
        {
            printf("Tidak ada Gadget yang dapat digunakan!\n");
        }
        else
        {
            useGadget(player, gadgetUsed);
        }
    }
    else if (choice && choice == 0)
    {
    }
}

void help()
{
    printf("1. MOVE\n");                // samuel udah
    printf("2. PICK UP\n");             // samuel udah
    printf("3. DROP OFF\n");            // samuel
    printf("4. DISPLAY MAP\n");         // saul
    printf("5. DISPLAY TO DO LIST\n");  // lewiss udah
    printf("6. DISPLAY IN PROGRESS\n"); // lewiss udah
    printf("7. BUY\n");                 //jova
    printf("8. INVENTORY\n");           //ave mungkin
    printf("9. HELP\n");                //udah
    printf("10. EXIT GAME\n");
    //harus ada yang ngeconvert Queue ke todolist dan inprogress berarti, mungkin diambil 5 6 juga soalnya mudah kan display doang
}

void saveGame(Mobita *player)
{
    // MALES PAKE MESINNNNNNN, NTAR AJA
    char name[20];
    printf("Masukkan nama save file: ");
    scanf("%s", &name);

    FILE *original, *copy;
    int c;
    original = fopen("test.txt", "r");
    copy = fopen(name, "w");
    if (!original || !copy)
    {
        puts("File error!");
    }
    while ((c = fgetc(original)) != EOF)
        fputc(c, copy);

    fclose(original);
    fclose(copy);

    copy = fopen(name, "a");

    fprintf(copy, "\n%d", UANG(*player));
    fprintf(copy, "\n%d", WAKTU(*player) - 1);
    fprintf(copy, "\n%d %d", Absis(POSISI(*player)), Ordinat(POSISI(*player)));

    Gadget *gadget = INVENTORY(*player).listGadget;
    int id[INVENTORYCAPACITY];
    int total[INVENTORYCAPACITY];

    for (int i = 0; i < INVENTORYCAPACITY; i++)
    {
        id[i] = -1;
        total[i] = 0;
    }

    for (int i = 0; i < INVENTORYCAPACITY; i++)
    {
        Gadget currentGadget = *(gadget + i);
        if (!isGadgetUNDEF(currentGadget))
        {
            id[IDGADGET(currentGadget)] = IDGADGET(currentGadget);
            total[IDGADGET(currentGadget)]++;
        }
    }

    int lenInventory = 0;
    for (int i = 0; i < INVENTORYCAPACITY; i++)
    {
        if (id[i] != -1)
        {
            lenInventory++;
        }
    }

    fprintf(copy, "\n%d", lenInventory);
    for (int i = 0; i < INVENTORYCAPACITY; i++)
    {
        if (id[i] != -1)
        {
            fprintf(copy, "\n%d %d", id[i], total[i]);
        }
    }

    fclose(copy);
}

void pilihCommand(Map peta, Queue *urutan, Mobita *player, Gadget *gadget)
{
    int pilihan;
    printf("Silahkan pilih command: ");
    scanf("%d", &pilihan);
    if (pilihan == 1)
    {
        move(peta, urutan, player);
    }
    else if (pilihan == 2)
    {
        pickUp(peta, urutan, player);
    }
    else if (pilihan == 3)
    {
        dropOff(peta, urutan, player);
    }
    else if (pilihan == 4)
    {
        displayMapColor(peta, urutan, player);
    }
    else if (pilihan == 5)
    {
        displayTodo(TODO(*player));
    }
    else if (pilihan == 6)
    {
        displayInProgress(INPROGRESS(*player));
    }
    else if (pilihan == 7)
    {
        buyGadget(player, gadget, &peta);
    }
    else if (pilihan == 8)
    {
        inventoryCommand(player);
    }
    else if (pilihan == 9)
    {
        help();
    }
    else if (pilihan == 10)
    {
        char choice;
        int exit;
        printf("Peringatan! Ability yang sedang aktif akan hilang.\n0 untuk membatalkan: ");
        scanf("%d", &exit);

        if (exit)
        {
            printf("Apakah ingin menyimpan state saat ini? (Y/N) - default(N): ");
            scanf(" %c", &choice);
            if (choice == 'Y' || choice == 'y')
            {
                saveGame(player);
            }
            else
            {
                printf("Terimakasih telah bermain\n");
            }
            return;
        }
    }
    else
    {
        printf("Pilihan yang dimasukkan salah. Silahkan masukkan opsi lain\n");
    }

    for (int i = 0; i < lengthQueue(*urutan); i++)
    {
        if (WAKTUPESANAN(HEAD(*urutan)) == WAKTU(*player))
        {
            ElType val;
            dequeue(urutan, &val);
            insertFirst(&TODO(*player), val);
        }
    }

    pilihCommand(peta, urutan, player, gadget);
}

int main()
{
    int opsi, i;
    Map peta;
    DaftarPesanan daftar;
    Mobita player;
    Queue urutan;
    Gadget gadgets[INVENTORYCAPACITY];
    CreateMap(&peta);
    printf("Selamat datang di game TUBES K2 Kelompok 6\nketik 1 untuk new game\nketik 2 untuk load game\nketik 3 untuk exit\nmasukkan opsi: ");
    scanf("%d", &opsi);
    if (opsi == 1 || opsi == 2)
    {
        createMobita(&player);
        if (opsi == 1)
        {
            konfigurasi(&peta, &daftar); // ngebaca txt file ke program
            printf("Konfigurasi permainan berhasil\n");
            int x = Absis(LOCPOINT(ELEMEN(MAPLOC(peta), 0))); // 0 adalah headquarter
            int y = Ordinat(LOCPOINT(ELEMEN(MAPLOC(peta), 0)));
            changePosisi(&player, x, y); // Mengubah koordinat awal nobita menjadi headquarter
        }
        else
        {
            char name[20];
            printf("Masukkan nama save file: ");
            scanf("%s", &name);
            loadGame(&peta, &daftar, &player, name);
            printf("Load game berhasil\n");
        }

        sortPesanan(&daftar);
        CreateQueue(&urutan);
        for (i = 0; i < NEFF(daftar); i++)
        {
            enqueue(&urutan, ELEMEN(daftar, i));
        }
        help();
        int j = 0;
        gadgets[0] = newGadget(0, "Kain Pembungkus Waktu", 800);
        gadgets[1] = newGadget(1, "Senter Pembesar", 1200);
        gadgets[2] = newGadget(2, "Pintu Kemana Saja", 1500);
        gadgets[3] = newGadget(3, "Mesin Waktu", 3000);
        gadgets[4] = newGadget(4, "Senter Pengecil", 800);
        pilihCommand(peta, &urutan, &player, gadgets);
    }
    return 0;
}

// Queue [9 elemen], dequeue --> [8elemen]
// in progress sama to do list linked list [kosong] [kosong]
// to do list [1 elemen todolist] [kosong]
