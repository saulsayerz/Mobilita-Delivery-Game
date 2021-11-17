#include "map.h"
#include <stdio.h>
#include <stdlib.h>
static FILE * tape;

void CreateMap(Map *peta){
    MAPROW(*peta) = 0;
    MAPCOL(*peta) = 0;
    NEFF(MAPLOC(*peta)) = 0;
    CONTENTS(MAPLOC(*peta)) = (Lokasi*) malloc (26 * sizeof(Lokasi));
    KAPASITAS(MAPLOC(*peta)) = 26;
    ROWS(MAPADJ(*peta)) = 0 ;
    COLS(MAPADJ(*peta)) = 0 ;
}

void CreateLoc(char nama, int i, int j, Lokasi *tempat){
    LOCNAME(*tempat) = nama;
    Absis(LOCPOINT(*tempat)) = i;
    Ordinat(LOCPOINT(*tempat)) = j; 
}


void displayMap(Map peta){ //INI BELUM JADIII
    Matrix m;
    int i,j,x,y;
    ROWS(m) = MAPROW(peta) +2;
    COLS(m) = MAPCOL(peta) +2;
    for (i = 0; i < MAPROW(peta)+2 ; i++) {
        for (j = 0; j < MAPCOL(peta)+2 ; j++){
            if (i==0 || j==0 || i==MAPROW(peta)+1||j==MAPCOL(peta)+1 ){
                ELEMENM(m,i,j) = '*';
            }
            else {
                ELEMENM(m,i,j) = ' ';
            }
        }
    }
    for (i = 0; i < NEFF(MAPLOC(peta)) ; i++){
        x = Absis(LOCPOINT(ELEMEN(MAPLOC(peta),i)));
        y = Ordinat(LOCPOINT(ELEMEN(MAPLOC(peta),i)));
        ELEMENM(m,x,y) = LOCNAME(ELEMEN(MAPLOC(peta),i));
    }
    cetakMatrix(m);
}

void konfigurasi(Map *peta, DaftarPesanan *daftar, char *name) {
    int x,y,i,j ;
    char nama;
    int waktu,perishable;
    char asal,tujuan,jenis;
    Pesanan pesan;
    Lokasi lok ;
    startWord(name);
    MAPROW(*peta) = kataToInt(currentWord);
    advWord();
    MAPCOL(*peta) = kataToInt(currentWord);
    adv();
    copyWord();
    x = kataToInt(currentWord);
    advWord();
    y = kataToInt(currentWord);
    CreateLoc('8', x, y, &lok); // UNTUK HEADQUARTERS
    ELEMEN(MAPLOC(*peta),0) = lok; //MENGISI LOKASI HEADQUARTERS KE MAP
    NEFF(MAPLOC(*peta)) = 1; //ISINYA MASIH HEADQUARTERS DOANG
    adv();
    copyWord();
    NEFF(MAPLOC(*peta)) += kataToInt(currentWord); //Ini banyaknya lokasinya
    adv();
    for (i=1; i<NEFF(MAPLOC(*peta)); i++){
        copyWord();
        nama = currentWord.contents[0];
        advWord();
        x = kataToInt(currentWord);
        advWord();
        y = kataToInt(currentWord);
        //printf("%c %d %d\n", nama, x, y); MENCETAK TIAP LOKASI
        CreateLoc(nama, x, y, &lok); // UNTUK SEMUA LOKASI
        ELEMEN(MAPLOC(*peta),i) = lok;
        adv();
    }
    ROWS(MAPADJ(*peta)) = NEFF(MAPLOC(*peta));
    COLS(MAPADJ(*peta)) = NEFF(MAPLOC(*peta));
    for (i=0 ; i < NEFF(MAPLOC(*peta)); i++){
        for (j=0 ; j < NEFF(MAPLOC(*peta));j++) {
            ELEMENM(MAPADJ(*peta),i,j) = currentChar;
            adv();
            adv();
        }
    }
    copyWord();
    NEFF(*daftar) = kataToInt(currentWord);
    adv();
    for (i=0; i<NEFF(*daftar)-1;i++) {
        copyWord();
        waktu = kataToInt(currentWord);
        advWord();
        asal = currentWord.contents[0];
        advWord();
        tujuan = currentWord.contents[0];
        advWord();
        jenis = currentWord.contents[0];
        if (currentWord.contents[0]== 'P'){
            advWord();
            perishable = kataToInt(currentWord);
        }
        else {
            perishable = -1; // INI UNDEF
        }
        CreatePesanan(waktu, asal, tujuan, jenis, perishable, &pesan);
        //cetakPesanan(pesan);
        daftar->contents[i] = pesan;
        adv();
    }
    copyWord();
    waktu = kataToInt(currentWord);
    advWord();
    asal = currentWord.contents[0];
    advWord();
    tujuan = currentWord.contents[0];
    advWord();
    jenis = currentWord.contents[0];
    if (jenis== 'P'){
        advWord();
        perishable = kataToInt(currentWord);
    }
    else {
        perishable = -1; // INI UNDEF
    }
    CreatePesanan(waktu, asal, tujuan, jenis, perishable, &pesan);
    //cetakPesanan(pesan);
    daftar->contents[i] = pesan;
    fclose(tape);
}

void loadGame(Map *peta, DaftarPesanan *daftar, Mobita *player, char *name, Gadget *gadget)
{
    int x,y,i,j ;
    char nama;
    int waktu,perishable;
    char asal,tujuan,jenis;
    Pesanan pesan;
    Lokasi lok ;
    startWord(name);
    MAPROW(*peta) = kataToInt(currentWord);
    advWord();
    MAPCOL(*peta) = kataToInt(currentWord);
    adv();
    copyWord();
    x = kataToInt(currentWord);
    advWord();
    y = kataToInt(currentWord);
    CreateLoc('8', x, y, &lok); // UNTUK HEADQUARTERS
    ELEMEN(MAPLOC(*peta),0) = lok; //MENGISI LOKASI HEADQUARTERS KE MAP
    NEFF(MAPLOC(*peta)) = 1; //ISINYA MASIH HEADQUARTERS DOANG
    adv();
    copyWord();
    NEFF(MAPLOC(*peta)) += kataToInt(currentWord); //Ini banyaknya lokasinya
    adv();
    for (i=1; i<NEFF(MAPLOC(*peta)); i++){
        copyWord();
        nama = currentWord.contents[0];
        advWord();
        x = kataToInt(currentWord);
        advWord();
        y = kataToInt(currentWord);
        //printf("%c %d %d\n", nama, x, y); MENCETAK TIAP LOKASI
        CreateLoc(nama, x, y, &lok); // UNTUK SEMUA LOKASI
        ELEMEN(MAPLOC(*peta),i) = lok;
        adv();
    }
    ROWS(MAPADJ(*peta)) = NEFF(MAPLOC(*peta));
    COLS(MAPADJ(*peta)) = NEFF(MAPLOC(*peta));
    for (i=0 ; i < NEFF(MAPLOC(*peta)); i++){
        for (j=0 ; j < NEFF(MAPLOC(*peta));j++) {
            ELEMENM(MAPADJ(*peta),i,j) = currentChar;
            adv();
            adv();
        }
    }
    copyWord();
    NEFF(*daftar) = kataToInt(currentWord);
    adv();
    for (i=0; i<NEFF(*daftar)-1;i++) {
        copyWord();
        advWord();
        advWord();
        advWord();
        if (currentWord.contents[0]== 'P'){
            advWord();
        }
        adv();
    }
    copyWord();
    advWord();
    advWord();
    advWord();
    if (currentWord.contents[0]== 'P'){
        advWord();
    }

    // Load Mobita dari save game
    adv();
    adv();
    advWord();
    UANG(*player) = kataToInt(currentWord);
    adv();
    copyWord();
    WAKTU(*player) = kataToInt(currentWord) - 1;
    adv();
    copyWord();
    x = kataToInt(currentWord);
    advWord();
    y = kataToInt(currentWord);
    changePosisi(player, x,y);
    adv();
    copyWord();
    int inventoryLength = kataToInt(currentWord);

    for (int i = 0; i < inventoryLength; i++)
    {
        adv();
        copyWord();
        int id = kataToInt(currentWord);
        advWord();
        int total = kataToInt(currentWord);
        
        Gadget savedGadget = *(gadget + id);
        for (int j = 0; j < total; j++)
        {
            addGadgetToInventory(&INVENTORY(*player), savedGadget);
        }
    }
    adv();
    copyWord();
    NEFF(*daftar) = kataToInt(currentWord);
    adv();
    for (i=0; i<NEFF(*daftar)-1;i++) {
        copyWord();
        waktu = kataToInt(currentWord);
        advWord();
        asal = currentWord.contents[0];
        advWord();
        tujuan = currentWord.contents[0];
        advWord();
        jenis = currentWord.contents[0];
        if (currentWord.contents[0]== 'P'){
            advWord();
            perishable = kataToInt(currentWord);
        }
        else {
            perishable = -1; // INI UNDEF
        }
        CreatePesanan(waktu, asal, tujuan, jenis, perishable, &pesan);
        //cetakPesanan(pesan);
        daftar->contents[i] = pesan;
        adv();
    }
    copyWord();
    waktu = kataToInt(currentWord);
    advWord();
    asal = currentWord.contents[0];
    advWord();
    tujuan = currentWord.contents[0];
    advWord();
    jenis = currentWord.contents[0];
    if (jenis== 'P'){
        advWord();
        perishable = kataToInt(currentWord);
    }
    else {
        perishable = -1; // INI UNDEF
    }
    CreatePesanan(waktu, asal, tujuan, jenis, perishable, &pesan);
    //cetakPesanan(pesan);
    daftar->contents[i] = pesan;
    
    fclose(tape);
}

void cetakMatrix(Matrix m){
    int i, j;
	for (i = 0; i < ROWS(m); i++){
		for (j = 0; j < COLS(m); j++){
			if (j==0) {
                printf("%c", ELMT(m,i,j));
            }
            else {
                printf(" %c", ELMT(m,i,j));
            }
		}
        printf("\n");
	}
}

POINT NameToPoint(Map peta, char nama)
{   
    int i;
    POINT hasil;
    for (i = 0; i < NEFF(MAPLOC(peta)); i++) //harusnya searching pake while tapi mager
    {
        if (LOCNAME(ELEMEN(MAPLOC(peta), i)) == nama)
        {
            hasil = LOCPOINT(ELEMEN(MAPLOC(peta), i));
        }
    }
    return hasil;
}
