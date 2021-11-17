#include "tas.h"

// UNCOMMENT JIKA MENGGUNAKAN 'code-runner'
#include "tas.c"
#include "../pesanan/pesanan.c"

int main()
{

    // inisialisasi tas
    Tas t1, t2;
    createTas(&t1);
    createTas(&t2);

    // inisialisasi pesanan untuk tes
    Pesanan p1, p2, p3, p4;
    CreatePesanan(25, 'A', 'D', 'H', -1, &p1);
    CreatePesanan(25, 'K', 'A', 'P', 1, &p2);
    CreatePesanan(25, 'F', 'L', 'N', -1, &p3);
    CreatePesanan(25, 'J', 'C', 'P', 20, &p4);
    // tes pushTas sekaligus popTas dan isTasEmpty dan juga tes perishable timenya
    // expected value:
    //   print dari top sampai indeks 0, mendapatkan p3, p2, p1
    pushTas(&t1, p1);
    pushTas(&t1, p2);
    pushTas(&t1, p3);
    // test
    ElTypeTas e;
    t2 = t1;
    while (isTasEmpty(t2) == false)
    {
        popTas(&t2, &e);
        cetakPesanan(e);
    }
    printf("------------------------\n");

    // tes isTasFull
    // expected value:
    //   karena kapasitas awal 3, maka jika dimasukkan 3 harusnya full, dan 2 harusnya tidak full
    //   untuk mengklarifikasi, sekalipun penuh kita tetap bisa push ke tas
    //   jadi skema validasi ada di fungsi yang memakai tas
    pushTas(&t2, p1);
    pushTas(&t2, p2);
    printf("Apakah tas 1 penuh: %c\n", isTasFull(t1) ? 'Y' : 'N');
    printf("Apakah tas 2 penuh: %c\n", isTasFull(t2) ? 'Y' : 'N');

    printf("------------------------\n");

    // tes setMaxItem
    // pengetesan dilakukan dengan mengubah maks item lalu tes apakah tas1
    // akan penuh lagi
    // expected value:
    //   max item berubah diindikasikan oleh tas tidak menjadi penuh
    setMaxItem(&t1, 4);
    printf("Apakah tas 1 penuh setelah diextend besarnya 1: %c\n", isTasFull(t1) ? 'Y' : 'N');
    pushTas(&t1, p4);
    printf("Apakah tas 1 penuh setelah ditambah 1 item: %c\n", isTasFull(t1) ? 'Y' : 'N');
    printf("------------------------\n");

    // tes mengurangi waktu semua perishable
    // expected value:
    //   waktu semua perishable di tas akan berkurang 1, dan yang menjadi 0 hilang
    decreasePerishableTimeInTas(&t1);
    t2 = t1;
    while (isTasEmpty(t2) == false)
    {
        popTas(&t2, &e);
        cetakPesanan(e);
    }
    printf("------------------------\n");

    return 0;
}