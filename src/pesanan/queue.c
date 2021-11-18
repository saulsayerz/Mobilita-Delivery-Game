#include <stdio.h>
#include "queue.h"

void CreateQueue(Queue *q)
{
    IDX_HEAD(*q) = IDX_UNDEF;
    IDX_TAIL(*q) = IDX_UNDEF;
}
/* I.S. sembarang */
/* F.S. Sebuah q kosong terbentuk dengan kondisi sbb: */
/* - Index head bernilai IDX_UNDEF */
/* - Index tail bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah q kosong */

boolean isEmptyQueue(Queue q)
{
    return (IDX_HEAD(q) == IDX_UNDEF && IDX_TAIL(q) == IDX_UNDEF);
}
/* Mengirim true jika q kosong: lihat definisi di atas */

boolean isFull(Queue q)
{
    return (IDX_HEAD(q) == 0 && IDX_TAIL(q) == (CAPACITYQ - 1));
}
/* Mengirim true jika tabel penampung elemen q sudah penuh */
/* yaitu jika index head bernilai 0 dan index tail bernilai CAPACITY-1 */

int lengthQueue(Queue q)
{
    int panjang;
    if (isEmptyQueue(q))
    {
        panjang = 0;
    }
    else
    {
        panjang = IDX_TAIL(q) - IDX_HEAD(q) + 1;
    }
    return panjang;
}

void enqueue(Queue *q, Pesanan val)
{
    int i;
    // Pesanan nilai;
    if (isEmptyQueue(*q))
    {
        IDX_HEAD(*q) = 0;
        IDX_TAIL(*q) = 0;
        HEAD(*q) = val;
    }
    else
    {
        if ((IDX_TAIL(*q) == 99))
        {
            for (i = IDX_HEAD(*q); i < IDX_TAIL(*q) + 1; i++)
            {
                (*q).buffer[i - IDX_HEAD(*q)] = (*q).buffer[i];
            }
            IDX_TAIL(*q) = IDX_TAIL(*q) - IDX_HEAD(*q);
            IDX_HEAD(*q) = 0;
        }
        IDX_TAIL(*q) += 1;
        TAIL(*q) = val;
    }
}
/* Proses: Menambahkan val pada q dengan aturan FIFO */
/* I.S. q mungkin kosong, tabel penampung elemen q TIDAK penuh */
/* F.S. val menjadi TAIL yang baru, IDX_TAIL "mundur".
        Jika q penuh semu, maka perlu dilakukan aksi penggeseran "maju" elemen-elemen q
        menjadi rata kiri untuk membuat ruang kosong bagi TAIL baru  */

void dequeue(Queue *q, Pesanan *val)
{
    *val = HEAD(*q);
    if (lengthQueue(*q) == 1)
    {
        CreateQueue(q);
    }
    else
    {
        IDX_HEAD(*q) += 1;
    }
}