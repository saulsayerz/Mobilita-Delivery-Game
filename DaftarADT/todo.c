#include <stdio.h>
#include "todo.h"

void CreateTodoList(List *l)
{
    *l = NULL;
}

boolean isEmpty(List l)
{
    return l == NULL;
}

void insertFirst(List *l, ElType val)
{
    Address baru;
    baru = newNode(val);
    if (baru != NULL)
    {
        NEXT(baru) = *l;
        *l = baru;
    }
}

void insertLast(List *l, ElType val)
{
    Address alamat, akhir;
    if (*l == NULL)
    {
        insertFirst(l, val);
    }
    else
    {
        alamat = newNode(val);
        if (alamat != NULL)
        {
            akhir = *l;
            while (NEXT(akhir) != NULL)
            {
                akhir = NEXT(akhir);
            }
            NEXT(akhir) = alamat;
        }
    }
}

void deleteFirst(List *l, ElType *val)
{
    Address alamat = *l;
    *val = INFO(alamat);
    *l = NEXT(alamat);
    free(alamat);
}

void deleteLast(List *l, ElType *val)
{
    Address alamat, lokasi;
    alamat = *l;
    lokasi = NULL;
    while (NEXT(alamat) != NULL)
    {
        lokasi = alamat;
        alamat = NEXT(alamat);
    }
    if (lokasi == NULL)
    {
        *l = NULL;
    }
    else
    {
        NEXT(lokasi) = NULL;
    }
    *val = INFO(alamat);
    free(alamat);
}

void displayJenis(Pesanan *p)
{
    switch (JENIS(*p))
    {
    case 'N':
        printf("(Normal Item)\n");
        break;
    
    case 'H':
        printf("(Heavy Item)\n");
        break;

    case 'V':
        printf("(VIP Item)\n");
        break;
    
    case 'P':
        printf("(Perishable Item, sisa waktu %d)\n", WAKTU(*p));

    default:
        break;
    }
}

void displayTodo(List l)
{
    Address alamat = l;
    int i = 0;
    if (!isEmpty(l))
    {
        ElType info = INFO(alamat);
        while (alamat != NULL)
        {
            printf("%d. %c -> %c ", i, info.asal, info.tujuan);
            displayJenis(&info);
            alamat = NEXT(alamat);
            i++;
        }
    }
}

int length(List l)
{
    int panjang = 0;
    Address akhir = l;
    while (akhir != NULL)
    {
        panjang++;
        akhir = NEXT(akhir);
    }
    return panjang;
}

void displayInProgress(List l){
    Addres alamat = l;
    
    if (!isEmpty(l))
    {
        ElType info = INFO(alamat);
        printf("Pesanan yang sedang diantarkan: \n1. ");
        displayJenis(&info);
        printf("(Tujuan: %c)", info.tujuan);
    }else{
        printf("Tidak ada pesanan saat ini.");
    }
}