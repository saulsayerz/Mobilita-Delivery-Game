//Nama : Saul Sayers
//NIM  : 13520094
//Kelas: K02 Alstrukdat
//PRA-PRAKTIKUM 5

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

typedef struct {
    float contents[ROW_CAP][COL_CAP];
    int rowEff; 
    int colEff; 
} MatrixFloat;

/* *** Konstruktor membentuk Matrix *** */
void CreateMatrix(int nRow, int nCol, Matrix *m){
    ROWS(*m) = nRow ;
    COLS(*m) = nCol ;
}
/* Membentuk sebuah Matrix "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
/* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks m sesuai dengan definisi di atas terbentuk */

boolean isIdxValid(int i, int j){
    return (i >=0) && (i<ROW_CAP) && (j >=0) && (j<COL_CAP) ;
}

Index getLastIdxRow(Matrix m){
    return ROWS(m) -1;
}

Index getLastIdxCol(Matrix m){
    return COLS(m) -1 ;
}

boolean isIdxEff(Matrix m, Index i, Index j){
    return (i >=0) && (i<ROWS(m)) && (j >=0) && (j<COLS(m)) ;
}

ElType getElmtDiagonal(Matrix m, Index i){
    return ELMT(m,i,i) ;
}

void copyMatrix(Matrix mIn, Matrix *mRes){
	int i, j;
    COLS(*mRes) = COLS(mIn);
    ROWS(*mRes) = ROWS(mIn);
	for (i = 0; i < ROWS(mIn); i++){
		for (j = 0; j < COLS(mIn); j++){
			ELMT(*mRes,i,j) = ELMT(mIn,i,j);
		}
	}
}

void readMatrix(Matrix *m, int nRow, int nCol){
    int i, j;
    ROWS(*m) = nRow;
    COLS(*m) = nCol;
	for (i = 0; i < nRow; i++){
		for (j = 0; j < nCol; j++){
			if (j==0) {
                scanf("%d", &ELMT(*m,i,j));
            }
            else {
                scanf(" %d", &ELMT(*m,i,j));
            }
		}
	}
}

void displayMatrix(Matrix m){
    int i, j;
	for (i = 0; i < ROWS(m); i++){
		for (j = 0; j < COLS(m); j++){
			if (j==0) {
                printf("%d", ELMT(m,i,j));
            }
            else {
                printf(" %d", ELMT(m,i,j));
            }
		}
        if (i != getLastIdxRow(m)) {
            printf("\n");
        }
	}
}

Matrix addMatrix(Matrix m1, Matrix m2){
    Matrix m;
    int i,j ;
    ROWS(m) = ROWS(m1) ;
    COLS(m) = COLS(m1) ;
    for (i = 0; i < ROWS(m); i++){
	    for (j = 0; j < COLS(m); j++){
            ELMT(m,i,j) = ELMT(m1,i,j) + ELMT(m2,i,j);
        }
    }
    return m;
}

Matrix subtractMatrix(Matrix m1, Matrix m2){
    Matrix m;
    int i,j ;
    ROWS(m) = ROWS(m1) ;
    COLS(m) = COLS(m1) ;
    for (i = 0; i < ROWS(m); i++){
	    for (j = 0; j < COLS(m); j++){
            ELMT(m,i,j) = ELMT(m1,i,j) - ELMT(m2,i,j);
        }
    }
    return m;
}

Matrix multiplyMatrix(Matrix m1, Matrix m2){
    Matrix m;
    int i,j,k ;
    ElType total ;
    ROWS(m) = ROWS(m1) ;
    COLS(m) = COLS(m2) ;
    for (i = 0; i < ROWS(m1); i++){
	    for (j = 0; j < COLS(m2); j++){
            total = 0 ;
            for (k = 0; k < ROWS(m2); k++){
                total += ELMT(m1,i,k)*ELMT(m2,k,j);
            }
            ELMT(m,i,j) = total;
        }
    }
    return m;
}

Matrix multiplyConst(Matrix m, ElType x){
    Matrix mhasil;
    ROWS(mhasil) = ROWS(m) ;
    COLS(mhasil) = COLS(m) ;
    int i,j ;
    for (i = 0; i < ROWS(m); i++){
	    for (j = 0; j < COLS(m); j++){
            ELMT(mhasil,i,j) = x*ELMT(m,i,j);
        }
    }
    return mhasil;
}

void pMultiplyConst(Matrix *m, ElType k){
    int i,j ;
    for (i = 0; i < ROWS(*m); i++){
	    for (j = 0; j < COLS(*m); j++){
            ELMT(*m,i,j) = k*ELMT(*m,i,j);
        }
    }
}

boolean isEqual(Matrix m1, Matrix m2){
    int i,j ;
    boolean sama = true ;
    if (ROWS(m1) != ROWS(m2) || COLS(m1) != COLS(m2)) {
        sama = false ;
    }
    else {
        for (i = 0; i < ROWS(m1); i++){
	        for (j = 0; j < COLS(m1); j++){
                if (ELMT(m1,i,j) != ELMT(m2,i,j)) {
                    sama = false ;
                }
            }
        }
    }
    return sama;
}

boolean isNotEqual(Matrix m1, Matrix m2){
    return !isEqual(m1,m2);
}

boolean isSizeEqual(Matrix m1, Matrix m2){
    return ROWS(m1) == ROWS(m2) && COLS(m1) == COLS(m2);
}

int count(Matrix m){
    return ROWS(m)*COLS(m);
}

boolean isSquare(Matrix m){
    return ROWS(m) == COLS(m);
}

boolean isSymmetric(Matrix m){
    int i,j ;
    boolean simetris = true ;
    for (i = 0; i < ROWS(m); i++){
	    for (j = 0; j < COLS(m); j++){
            if (ELMT(m,i,j) != ELMT(m,j,i)) {
                simetris = false ;
            }
        }
    }
    return simetris;
}

boolean isIdentity(Matrix m){
    int i,j ;
    boolean identitas = true ;
    for (i = 0; i < ROWS(m); i++){
	    for (j = 0; j < COLS(m); j++){
            if (i==j) {
                if (ELMT(m,i,j) != 1){
                    identitas = false;
                }
            }
            else {
                if (ELMT(m,i,j) != 0){
                    identitas = false;
                }
            }
        }
    }
    return identitas;
}

boolean isSparse(Matrix m){
    int i,j ;
    boolean spars ;
    float maks = count(m)*0.05;
    int bernilai = 0 ;
    for (i = 0; i < ROWS(m); i++){
	    for (j = 0; j < COLS(m); j++){ 
            if (ELMT(m,i,j) != 0) {
                bernilai ++;
            }
        }
    }
    if (bernilai > maks) {
        spars = false;
    }
    else {
        spars = true ;
    }
    return spars;
}

Matrix inverse1(Matrix m){
    return multiplyConst(m,-1);
}

void pInverse1(Matrix *m){
    pMultiplyConst(m,-1) ;
}

float determinant(Matrix m){
    Matrix sementara; //menyimpan kofaktor
    int tanda = 1, i,j,k;
    float determinan=0;
    ROWS(sementara) = ROWS(m) -1;
    COLS(sementara) = COLS(m) -1;       
    if (ROWS(m) == 1){
        determinan = ELMT(m,0,0) ; //KALAU MATRIKSNYA 1x1 MAKA DETERMINANNYA YA ELEMEN ITU DOANG
    }
    else { //Ini buat 2x2 keatas, aslinya 2x2 sama 3x3 bisa cara biasa tapi gapapadeh ikut direkursifin
        for (i=0; i<ROWS(m); i++) { // ini untuk baris paling atas (pertama) kolom ke i nanti dikaliin minornya
            for (j=1; j<ROWS(m) ; j++ ){  // ini startnya dari baris kedua karena kofaktornya dari situ
                for (k=0 ; k<COLS(m) ; k++){
                    if (k<i){ 
                        ELMT(sementara,j-1,k) = ELMT(m,j,k); //ini buat ngisi kofaktor pokoknya
                    }
                    else if (k>i) {
                        ELMT(sementara,j-1,k-1) = ELMT(m,j,k); // ini jg yang sekolom sama i biar keskip
                    }
                }
            }
            determinan += tanda*ELMT(m,0,i)*determinant(sementara);
            tanda = -tanda;
        }
    }
    return determinan;
}

void transpose(Matrix *m){
    int i,j ;
    ElType sementara ;
    for (i = 0; i < ROWS(*m); i++){
	    for (j = 0; j <= i ; j++){ 
            sementara = ELMT(*m,i,j);
            ELMT(*m,i,j) = ELMT(*m,j,i) ;
            ELMT(*m,j,i) = sementara ;
        }
    }
}