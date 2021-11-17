#include <stdio.h>
#include "./map/map.h"
#include "./mobita/mobita.h"
#include "./map/pcolor.h"
#include "./pesanan/queue.h"
#include "./pesanan/todo.h"

// define global variables
int pesananBerhasil = 0;
char* fileKonfig;

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
    startInputWord();
    pilihan = kataToInt(currentWord);
    while (pilihan < 0 || pilihan > NEFF(dapatdicapai))
    {
        printf("Input salah! Masukkan ulang command\nCOMMAND: ");
        startInputWord();
        pilihan = kataToInt(currentWord);
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
            printf("Kamu baru saja mempickup item heavy, ability SPEED BOOST mu hilang :(\n");
            removeEffect(
                &EFEK(*player),
                SPEED_BOOST);
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
    }
    else if (isTasFull(TAS_MOBITA(*player)))
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
            printf("Uang yang didapatkan : 200 Yen.\n");
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
                printf("Mendapat ability: SPEED BOOST!\n");
                speedBoostCounter = 0;
            }
        }
        else if (JENIS(INFO(p)) == 'P')
        {
            printf("Uang yang didapatkan : 400 Yen.\n");
            UANG(*player) += 400;
            setMaxItem(&TAS_MOBITA(*player), MAX_ITEM(TAS_MOBITA(*player)) + 1);
            printf("Mendapat ability: INCREASE CAPACITY!\n");
        }
        else if (JENIS(INFO(p)) == 'V')
        {
            printf("Uang yang didapatkan : 600 Yen.\n");
            UANG(*player) += 600;
        }
        removeItemFromTasAndInProgress(player);

        // menghapus efek senter pengecil setelah dropoff
        if (isEffectExist(EFEK(*player), SENTER_PENGECIL))
        {
            removeEffect(&EFEK(*player), SENTER_PENGECIL);
        }

        pesananBerhasil++;
    }
    else
    {
        printf("Tidak ada pesanan yang dapat diantarkan!");
    }

    printf("\n");
}

void displayMapColor(Map peta, Queue *urutan, Mobita *player)
{
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
        startInputWord();
        choice = kataToInt(currentWord);
        if (choice)
        {
            Gadget wishlist = *(gadget + choice - 1);
            if (UANG(*player) < HARGAGADGET(wishlist))
            {
                printf("Uang tidak cukup untuk membeli gadget.\n");
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
    startInputWord();
    choice = kataToInt(currentWord);

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
        printf("Pilihan salah\n");
    }
}

void help()
{
    printf("1. MOVE\n");
    printf("2. PICKUP\n");
    printf("3. DROPOFF\n");
    printf("4. MAP\n");
    printf("5. TODO\n");
    printf("6. INPROGRESS\n");
    printf("7. BUY\n");
    printf("8. INVENTORY\n");
    printf("9. HELP\n");
    printf("10.EXIT\n");
}

void saveGame(Mobita *player, Queue *urutan)
{
    FILE *original, *copy;
    int c;
    original = fopen(fileKonfig, "r");
    printf("Masukkan name save file: ");
    startInputWord();
    char* name = akusisi(currentWord);
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
    fprintf(copy, "\n%d", WAKTU(*player));
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

    List todo = TODO(*player);
    List inProgress = INPROGRESS(*player);
    int lengthTodo = length(todo);
    int lengthInProgress = length(inProgress);
    int lengthQueuePesanan = lengthQueue(*urutan);

    fprintf(copy, "\n%d", lengthTodo + lengthInProgress + lengthQueuePesanan);

    for (int i = 0; i < lengthTodo; i++)
    {
        ElType todoPesanan = INFO(todo);
        if (todoPesanan.jenis != 'P')
        {
            fprintf(copy, "\n%d %c %c %c", todoPesanan.waktu, todoPesanan.asal, todoPesanan.tujuan, todoPesanan.jenis);
        }
        else
        {
            fprintf(copy, "\n%d %c %c %c %d", todoPesanan.waktu, todoPesanan.asal, todoPesanan.tujuan, todoPesanan.jenis, todoPesanan.perishable);
        }
        todo = NEXT(todo);
    }

    for (int i = 0; i < lengthInProgress; i++)
    {
        ElType inProgressPesanan = INFO(inProgress);
        if (inProgressPesanan.jenis != 'P')
        {
            fprintf(copy, "\n%d %c %c %c", inProgressPesanan.waktu, inProgressPesanan.asal, inProgressPesanan.tujuan, inProgressPesanan.jenis);
        }
        else
        {
            fprintf(copy, "\n%d %c %c %c %d", inProgressPesanan.waktu, inProgressPesanan.asal, inProgressPesanan.tujuan, inProgressPesanan.jenis, inProgressPesanan.perishable);
        }
        todo = NEXT(inProgress);
    }

    for (int i = 0; i < lengthQueuePesanan; i++)
    {
        ElType val;
        dequeue(urutan, &val);
        if (val.jenis != 'P')
        {
            fprintf(copy, "\n%d %c %c %c", val.waktu, val.asal, val.tujuan, val.jenis);
        }
        else
        {
            fprintf(copy, "\n%d %c %c %c %d", val.waktu, val.asal, val.tujuan, val.jenis, val.perishable);
        }
    }

    fprintf(copy, "\n");
    fclose(copy);
}

void pilihCommand(Map peta, Queue *urutan, Mobita *player, Gadget *gadget)
{
    int lenQ = lengthQueue(*urutan);
    for (int i = 0; i < lenQ; i++)
    {
        if (WAKTUPESANAN(HEAD(*urutan)) <= WAKTU(*player))
        {
            ElType val;
            dequeue(urutan, &val);
            insertFirst(&TODO(*player), val);
        }
    }
    
    printf("Silahkan pilih command: ");
    Word pilihan;
    startInputWord();
    pilihan = currentWord;
    if (!strings_not_equal(pilihan, "MOVE"))
    {
        move(peta, urutan, player);
    }
    else if (!strings_not_equal(pilihan, "PICKUP"))
    {
        pickUp(peta, urutan, player);
    }
    else if (!strings_not_equal(pilihan, "DROPOFF"))
    {
        dropOff(peta, urutan, player);
    }
    else if (!strings_not_equal(pilihan, "MAP"))
    {
        displayMapColor(peta, urutan, player);
    }
    else if (!strings_not_equal(pilihan, "TODO"))
    {
        displayTodo(TODO(*player));
    }
    else if (!strings_not_equal(pilihan, "INPROGRESS"))
    {
        displayInProgress(INPROGRESS(*player));
    }
    else if (!strings_not_equal(pilihan, "BUY"))
    {
        buyGadget(player, gadget, &peta);
    }
    else if (!strings_not_equal(pilihan, "INVENTORY"))
    {
        inventoryCommand(player);
    }
    else if (!strings_not_equal(pilihan, "HELP"))
    {
        help();
    }
    else if (!strings_not_equal(pilihan, "EXIT"))
    {
        Word choice;
        int exit;
        printf("Peringatan! Ability yang sedang aktif akan hilang.\n1 Lanjut, 0 batal\n");
        printf("Masukkan pilihan: ");
        startInputWord();
        exit = kataToInt(currentWord);

        if (exit)
        {
            printf("Apakah ingin menyimpan state saat ini? (Y/N) - default(N): ");
            startInputWord();
            choice = currentWord;
            if (!strings_not_equal(choice, "Y") || !strings_not_equal(choice, "y"))
            {
                saveGame(player, urutan);
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

    int sisaPesanan = length(TODO(*player)) + length(INPROGRESS(*player)) + lengthQueue(*urutan);

    if (sisaPesanan == 0)
    {
        POINT position = POSISI(*player);
        POINT headQuarter = NameToPoint(peta, '8');

        if (EQ(position, headQuarter))
        {
            printf("Congratulations!!!\n");
            printf("Semua pesanan telah diselesaikan\n");
            printf("Total pesanan berhasil: %d\n", pesananBerhasil);
            printf("Total uang terkumpul: %d\n", UANG(*player));
            printf("RESPECT+++\n");
            printf("Terimakasih telah bermain!!!\n");
            return;
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
    startInputWord();
    opsi = kataToInt(currentWord);
    if (opsi == 1 || opsi == 2)
    {
        createMobita(&player);
        gadgets[0] = newGadget(0, KAIN_PEMBUNGKUS_WAKTU, 800);
        gadgets[1] = newGadget(1, SENTER_PEMBESAR, 1200);
        gadgets[2] = newGadget(2, PINTU_KEMANA_SAJA, 1500);
        gadgets[3] = newGadget(3, MESIN_WAKTU, 3000);
        gadgets[4] = newGadget(4, SENTER_PENGECIL, 800);
        if (opsi == 1)
        {
            char *konfName;
            FILE *exist;
            printf("Masukkan nama file konfig: ");
            startInputWord();
            konfName = akusisi(currentWord);
            exist = fopen(konfName, "r");
            while (exist == NULL)
            {
                printf("File tidak ditemukan!\n");
                printf("Masukkan nama file konfig: ");
                startInputWord();
                konfName = akusisi(currentWord);
                exist = fopen(konfName, "r");
            }
            fileKonfig = konfName;
            konfigurasi(&peta, &daftar, konfName); // ngebaca txt file ke program
            printf("Konfigurasi permainan berhasil\n");
            int x = Absis(LOCPOINT(ELEMEN(MAPLOC(peta), 0))); // 0 adalah headquarter
            int y = Ordinat(LOCPOINT(ELEMEN(MAPLOC(peta), 0)));
            changePosisi(&player, x, y); // Mengubah koordinat awal nobita menjadi headquarter
        }
        else
        {
            char *loadName;
            FILE *exist;
            printf("Masukkan nama save file: ");
            startInputWord();
            loadName = akusisi(currentWord);
            exist = fopen(loadName, "r");
            while (exist == NULL)
            {
                printf("File tidak ditemukan!\n");
                printf("Masukkan nama file konfig: ");
                startInputWord();
                loadName = akusisi(currentWord);
                exist = fopen(loadName, "r");
            }
            loadGame(&peta, &daftar, &player, loadName, gadgets);
            printf("Load game berhasil\n");
        }

        sortPesanan(&daftar);
        CreateQueue(&urutan);
        for (i = 0; i < NEFF(daftar); i++)
        {
            enqueue(&urutan, ELEMEN(daftar, i));
        }
        help();
        pilihCommand(peta, &urutan, &player, gadgets);
    }
    return 0;
}