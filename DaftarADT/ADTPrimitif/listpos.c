/* Nama    : Saul Sayers */
/* NIM     : 13520094 / 16520075 */
/* Kelas   : K02 */
/* Tanggal : 8 September 2021 */
/* PRA-PRAKTIKUM 3 */

#include <stdio.h>
#include "listpos.h"

void CreateListPos(ListPos *l){
    int i;
    for (i = 0; i < CAPACITY ; i++) {
        ELMT(*l, i) = VAL_UNDEF;
    }
}

int length(ListPos l) {
    int panjang;
    panjang = 0;
    while (panjang < CAPACITY && ELMT(l, panjang)!= VAL_UNDEF) {
            panjang += 1;
    }
    return panjang;
}

boolean isIdxValid(ListPos l, int i) {
    return ((i>=0) && (i<CAPACITY));
}

boolean isIdxEff(ListPos l, int i) {
    return ((i>=0) && (i<length(l)));
}

boolean isEmpty(ListPos l) {
    return (length(l) == 0);
}

boolean isFull(ListPos l) {
    return (length(l) == CAPACITY);
}

void readList(ListPos *l) {
    int N,i ;
    CreateListPos(l);
    do {
        scanf("%d", &N) ;
    } while ((N < 0 ) || (N > CAPACITY));

    for (i=0; i<N ; i++) {
        scanf("%d", &ELMT(*l, i)) ;
    }
}

void displayList(ListPos l) {
    int i;
    printf("[");
	for (i = 0; isIdxEff(l,i) ; i++) {
		if (i != 0) {
			printf(",");
		}
		printf("%d", ELMT(l,i));
	}
	printf("]");
}

ListPos plusMinusTab(ListPos l1, ListPos l2, boolean plus) {
    ListPos total;
    int i;
    CreateListPos(&total);
    for (i=0;(i<length(l1));i++){
		if (plus){
			ELMT(total,i) = ELMT(l1,i) + ELMT(l2,i);
		}
		else{
			ELMT(total,i) = ELMT(l1,i) - ELMT(l2,i);
		}
	}
    return total;
}

boolean isListEqual(ListPos l1, ListPos l2) {
    int i = 0; 
    boolean sama = true;
    if (length(l1) != length(l2)){
        sama = false;
    }
    else{
        while ((i<length(l1)) && (sama)) {
            if (ELMT(l1,i) != ELMT(l2,i)) {
                sama = false;
            }
            i++ ;
        }
    }
    return sama;
}

int indexOf(ListPos l, ElType val){
    int indeks = IDX_UNDEF;
    int i = 0 ;
    boolean ketemu=false ;
    while ((i<length(l)) && !(ketemu)) {
        if (ELMT(l,i) == val) {
            ketemu = true ;
            indeks = i ;
        }
        i++ ;
    }
    return indeks;
}
    
void extremes(ListPos l, ElType *max, ElType *min) {
    *min = ELMT(l, 0);
    *max = ELMT(l, 0);
    int i;
    for (i=1;isIdxEff(l,i);i++){
        if (ELMT(l,i) > *max) {
            *max = ELMT(l,i);
        }
        if (ELMT(l,i) < *min) {
            *min = ELMT(l,i);
        }
    }
}    

boolean isAllEven(ListPos l) {
    boolean genap = true ;
    int i = 0 ;
    while ((i<length(l)) && (genap)) {
        if ((ELMT(l,i) % 2) != 0) {
            genap = false;
        }
        i++ ;
    }
    return genap ;
}

void sort(ListPos *l, boolean asc) {
    int i, j, temp;
    for (i = 0; i < length(*l)-1; i++){
        for (j = 0; j < length(*l)-i-1; j++){
            if (asc) {
                if (ELMT(*l,j) > ELMT(*l,j+1)){
                    temp = ELMT(*l,j);
                    ELMT(*l,j) = ELMT(*l,j+1);
                    ELMT(*l,j+1) = temp;
                }
            }
            else {
                if (ELMT(*l,j) < ELMT(*l,j+1)){
                    temp = ELMT(*l,j) ;
                    ELMT(*l,j) = ELMT(*l,j+1);
                    ELMT(*l,j+1) = temp;
                }
            }
        }
    }
}

void insertLast(ListPos *l, ElType val) {
    ELMT(*l,length(*l)) = val;
}

void deleteLast(ListPos *l, ElType *val){
    *val = ELMT(*l,length(*l)-1);
    ELMT(*l,length(*l)-1) = VAL_UNDEF;
}

typedef struct  { 
    ElType tab[100] ;
    int Neff ;
} listdavid;

void cekdavidkontol(listdavid *t) {
    (*t).tab[0] = 100 ;
}

