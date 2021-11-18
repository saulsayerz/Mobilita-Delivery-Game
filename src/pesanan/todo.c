#include <stdio.h>
#include "todo.h"
#include "pesanan.h"

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

void deleteFirst(List *l)
{
    Address alamat = *l;
    // *val = INFO(alamat);
    *l = NEXT(alamat);
    free(alamat);
}

void deleteLast(List *l)
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
    // *val = INFO(alamat);
    free(alamat);
}

void deleteAt(List *l, int idx)
{
    /* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
    /* F.S. val diset dengan elemen l pada indeks ke-idx. */
    /*      Elemen l pada indeks ke-idx dihapus dari l */
    if (idx == 0)
    {
        // deleteFirst(l, val);
        deleteFirst(l);
    }
    else
    {
        Address p, q;
        q = *l;
        int count = 0;
        while (count < idx - 1)
        {
            count++;
            q = NEXT(q);
        }
        p = NEXT(q);
        // *val = INFO(p);
        NEXT(q) = NEXT(p);
        free(p);
    }
}

void displayJenis(Pesanan *p)
{
    switch (JENIS(*p))
    {
    case 'N':
        printf("Normal Item");
        break;

    case 'H':
        printf("Heavy Item");
        break;

    case 'V':
        printf("VIP Item");
        break;

    case 'P':
        printf("Perishable Item, sisa waktu %d", PERISH(*p));

    default:
        break;
    }
}

void displayTodo(List l)
{
    Address alamat = l;
    int i = 1;
    if (!isEmpty(l))
    {
        ElType info = INFO(alamat);
        printf("Pesanan pada To Do List:\n");
        while (alamat != NULL && NEXT(alamat) != NULL)
        {
            printf("%d. %c -> %c (", i, info.asal, info.tujuan);
            displayJenis(&info);
            printf(")\n");
            alamat = NEXT(alamat);
            info = INFO(alamat);
            i++;
        }
        printf("%d. %c -> %c (", i, info.asal, info.tujuan);
        displayJenis(&info);
        printf(")\n");
    }
    else
    {
        printf("Tidak ada To Do List\n");
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

void displayInProgress(List l)
{
    Address alamat = l;
    int i = 1;
    if (!isEmpty(l))
    {
        ElType info = INFO(alamat);
        printf("Pesanan yang sedang diantarkan: \n");
        while (alamat != NULL && NEXT(alamat) != NULL)
        {
            printf("%d. ", i);
            displayJenis(&info);
            printf(" (Tujuan : %c)\n", info.tujuan);
            alamat = NEXT(alamat);
            info = INFO(alamat);
            i++;
        }
        printf("%d. ", i);
        displayJenis(&info);
        printf(" (Tujuan : %c)\n", info.tujuan);
    }
    else
    {
        printf("Tidak ada pesanan yang sedang diantarkan\n");
    }
}

void inverseTodo(List *l)
{
    List invTodo;
    CreateTodoList(&invTodo);
    Address p = *l;
    while (p != NULL)
    {
        insertFirst(&invTodo, INFO(p));
        p = NEXT(p);
    }
    
    *l = invTodo;
}