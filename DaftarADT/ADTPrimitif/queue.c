//NAMA  : Saul Sayers
//NIM   : 13520094 / 16520075
//KELAS : K02 Alstrukdat
//PRAPRAKTIKUM 7

#include <stdio.h>
#include "queue.h"

void CreateQueue(Queue *q){
    IDX_HEAD(*q) = IDX_UNDEF;
    IDX_TAIL(*q) = IDX_UNDEF;
}
/* I.S. sembarang */
/* F.S. Sebuah q kosong terbentuk dengan kondisi sbb: */
/* - Index head bernilai IDX_UNDEF */
/* - Index tail bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah q kosong */

boolean isEmptyQueue(Queue q){
    return (IDX_HEAD(q) == IDX_UNDEF && IDX_TAIL(q) == IDX_UNDEF);
}
/* Mengirim true jika q kosong: lihat definisi di atas */

boolean isFull(Queue q){
    return (IDX_HEAD(q) == 0 && IDX_TAIL(q) == (CAPACITY -1));
}
/* Mengirim true jika tabel penampung elemen q sudah penuh */
/* yaitu jika index head bernilai 0 dan index tail bernilai CAPACITY-1 */

int lengthQueue(Queue q){
    int panjang ;
    if (isEmptyQueue(q)) {
        panjang = 0;
    }
    else {
        panjang = IDX_TAIL(q) - IDX_HEAD(q) +1 ;
    }
    return panjang ;
}

void enqueue(Queue *q, Pesanan val){
    int i,awal;
    Pesanan nilai;
    if (isEmptyQueue(*q)) {
        IDX_HEAD(*q) = 0;
        IDX_TAIL(*q) = 0;
        HEAD(*q) = val;
    }
    else {
        if ((IDX_TAIL(*q) == 99)) {
            for (i = IDX_HEAD(*q); i < IDX_TAIL(*q) +1; i++){
                (*q).buffer[i - IDX_HEAD(*q)] = (*q).buffer[i];
            }
            IDX_TAIL(*q) = IDX_TAIL(*q) - IDX_HEAD(*q);
            IDX_HEAD(*q) = 0;
        }
        IDX_TAIL(*q) +=1  ;
        TAIL(*q) = val ;
    }
}
/* Proses: Menambahkan val pada q dengan aturan FIFO */
/* I.S. q mungkin kosong, tabel penampung elemen q TIDAK penuh */
/* F.S. val menjadi TAIL yang baru, IDX_TAIL "mundur".
        Jika q penuh semu, maka perlu dilakukan aksi penggeseran "maju" elemen-elemen q
        menjadi rata kiri untuk membuat ruang kosong bagi TAIL baru  */

void dequeue(Queue *q, Pesanan *val){
    /*int awal = IDX_HEAD(*q);
    int i;
    Pesanan nilai ;
    *val = HEAD(*q);
    if (length(*q) == 1) {
        CreateQueue(q) ;
    }
    else{
        for (i = awal+1;i < length(*q) + awal; i++){
            IDX_HEAD(*q) = i;
            nilai = HEAD(*q) ;
            IDX_HEAD(*q) -= 1;
            HEAD(*q) = nilai;
        }
    }
    IDX_TAIL(*q) -= 1;
    IDX_HEAD(*q) = awal;*/
    *val = HEAD(*q);
    if (lengthQueue(*q) == 1) {
        CreateQueue(q) ;
    }
    else {
        IDX_HEAD(*q) += 1;
    }
}
/* Proses: Menghapus val pada q dengan aturan FIFO */
/* I.S. q tidak mungkin kosong */
/* F.S. val = nilai elemen HEAD pd I.S., HEAD dan IDX_HEAD "mundur";
        q mungkin kosong */

void displayQueue(Queue q){
    int i;
    int awal = IDX_HEAD(q) ;
    printf("[");
    if (!isEmptyQueue(q)) {
        for(i=awal; i < IDX_TAIL(q)+1 ; i++){
            IDX_HEAD(q) = i;
            printf("%d", HEAD(q));
            if (i != IDX_TAIL(q)) {
                printf(",");
            }
        }
    }
    printf("]");
    /* Proses : Menuliskan isi Queue dengan traversal, Queue ditulis di antara kurung 
   siku; antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan 
   karakter di depan, di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. q boleh kosong */
/* F.S. Jika q tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika Queue kosong : menulis [] */
}

/*int main() {
    Queue q;
    CreateQueue(&q);
    IDX_HEAD(q) = 5;
    IDX_TAIL(q) = 7;
    q.buffer[5] = 1;
    q.buffer[6] = 2;
    q.buffer[7] = 3;
    displayQueue(q);
}*/