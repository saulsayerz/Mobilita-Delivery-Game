// NAMA      : Saul Sayers
// NIM       : 13520094
// Tanggal   : 24 Oktober 2021
// Topik     : ADT Linked List
// Deskripsi : Implementasi ADT Linked List dalam bahasa C

#include "list_linked.h"
#include <stdio.h>

void CreateList(List *l){
    *l = NULL;
}

boolean isEmpty(List l){
    return l == NULL;
}

ElType getElmt(List l, int idx){
    ElType nomer = 0 ;
    Address alamat = l;
    while (nomer < idx) {
        nomer += 1;
        alamat = NEXT(alamat);
    }
    return INFO(alamat);
}

void setElmt(List *l, int idx, ElType val){
    ElType nomer = 0 ;
    Address alamat = *l;
    while (nomer < idx) {
        nomer += 1;
        alamat = NEXT(alamat);
    }
    INFO(alamat) = val;
}

int indexOf(List l, ElType val){
    int indeks = 0, hasil ;
    Address alamat = l ;
    boolean found = false;
    while (alamat != NULL && !found) {
        if (INFO(alamat) == val) {
            found = true;
        }
        else {
            indeks ++ ;
            alamat = NEXT(alamat);
        }
    }
    if (found) {
        hasil = indeks;
    }
    else {
        hasil = IDX_UNDEF;
    }
    return hasil ;
}

void insertFirst(List *l, ElType val){
    Address baru ;
    baru = newNode(val);
    if (baru != NULL) {
        NEXT(baru) = *l;
        *l = baru;
    }
}


void insertLast(List *l, ElType val){
    Address alamat, akhir ;
    /*if (isEmpty(&l)) {
        insertFirst(l, val);
    }*/
    if (*l == NULL) {
        insertFirst(l, val);
    }
    else {
        alamat = newNode(val) ;
        if (alamat != NULL) {
            akhir = *l ;
            while (NEXT(akhir) != NULL ) {
                akhir = NEXT(akhir);
            }
            NEXT(akhir) = alamat;
        }
    }
}

void insertAt(List *l, ElType val, int idx){
    int angka;
    Address alamat, lokasi ;
    if (idx == 0) {
        insertFirst(l,val);
    }
    else {
        alamat = newNode(val);
        if (alamat != NULL) {
            angka = 0;
            lokasi = *l;
            while (angka < idx - 1) {
                angka++ ;
                lokasi = NEXT(lokasi);
            }
            NEXT(alamat) = NEXT(lokasi);
            NEXT(lokasi) = alamat;
        }
    }
}

void deleteFirst(List *l, ElType *val){
    Address alamat = *l;
    *val = INFO(alamat) ;
    *l = NEXT(alamat);
    free(alamat) ;
}

void deleteLast(List *l, ElType *val){
    Address alamat, lokasi ;
    alamat = *l;
    lokasi = NULL ;
    while (NEXT(alamat) != NULL) {
        lokasi = alamat ;
        alamat = NEXT(alamat) ;
    }
    if (lokasi == NULL) {
        *l = NULL;
    }
    else {
        NEXT(lokasi) = NULL;
    }
    *val = INFO(alamat);
    free(alamat);
}

void deleteAt(List *l, int idx, ElType *val){
    int angka;
    Address alamat, lokasi ;
    if (idx == 0) {
        deleteFirst(l,val);
    }
    else {
        angka = 0;
        lokasi = *l;
        while (angka < idx - 1) {
            angka ++ ;
            lokasi = NEXT(lokasi) ;
        }
        alamat = NEXT(lokasi);
        *val= INFO(alamat);
        NEXT(lokasi) = NEXT(alamat);
        free(alamat);
    }
}

void displayList(List l){
    Address alamat = l ;
    printf("[");
    if (!isEmpty(l)) {
        while (NEXT(alamat) != NULL) {
            printf("%d,", INFO(alamat));
            alamat = NEXT(alamat);
        }
        printf("%d", INFO(alamat));
    }
    printf("]");
}

int length(List l){
    int panjang = 0;
    Address akhir = l;
    while (akhir != NULL) {
        panjang++ ;
        akhir = NEXT(akhir);
    }
    return panjang;
}

/****************** PROSES TERHADAP LIST ******************/
List concat(List l1, List l2) {
    Address alamat = l1;
    List l3;
    ElType val;
    CreateList(&l3);
    while (alamat != NULL) {
        insertLast(&l3, INFO(alamat));
        alamat = NEXT(alamat);
    }
    alamat = l2;
    while (alamat != NULL) {
        insertLast(&l3, INFO(alamat));
        alamat = NEXT(alamat);
    }
    return l3;
}



