#include <stdio.h>
#include "../DaftarADT/map.c"
#include "../DaftarADT/pesanan.c"
#include "../DaftarADT/mobita.c"
#include "../DaftarADT/inventory.c"
#include "../DaftarADT/gadget.c"
#include "../DaftarADT/pcolor.c"
#include "../DaftarADT/ADTPrimitif/Queue.c"

void move(Map peta, Queue *urutan, Mobita *player){
    printf("POSISI YANG DAPAT DICAPAI\n");
    int i, x ,y, baris, kolom=0 ,j,k;
    x = Absis(POSISI(*player)); // posisi sementara nobita
    y = Ordinat(POSISI(*player));
    ListDinamis dapatdicapai ;
    CONTENTS(dapatdicapai) = (Lokasi*) malloc (26 * sizeof(Lokasi));
    NEFF(dapatdicapai) = 0;
    KAPASITAS(dapatdicapai) = 26;
    for (i=0; i < NEFF(MAPLOC(peta)) ; i++) { // searching barisnya
        if (x == Absis(LOCPOINT(ELEMEN(MAPLOC(peta),i)))&& y == Ordinat(LOCPOINT(ELEMEN(MAPLOC(peta),i)))) {
            baris = i; // harusnya pake while deh algoritma searching tapi mager
        } 
    }
    for (j=0; j < NEFF(MAPLOC(peta)) ; j++) { // ngecek di matriks MAPADJ(peta) bisa dicapai ga
        if (ELEMENM(MAPADJ(peta),baris,j) == '1') {
            ELEMEN(dapatdicapai,kolom) = ELEMEN(MAPLOC(peta),j);
            kolom++ ;
            NEFF(dapatdicapai) += 1;
        } 
    }
    for (k=1; k <= NEFF(dapatdicapai) ; k++){
        printf("%d. %c (%d,%d)\n", k, LOCNAME(ELEMEN(dapatdicapai,k-1)), Absis(LOCPOINT(ELEMEN(dapatdicapai,k-1))), Ordinat(LOCPOINT(ELEMEN(dapatdicapai,k-1))) );
    }
    printf("Posisi yang dipilih? (ketik 0 jika ingin kembali)\n");
    int pilihan ;
    printf("ENTER COMMAND: ");
    scanf("%d", &pilihan);
    if (pilihan== 0) {
        printf("Kembali");
    }
    else {
        x = Absis(LOCPOINT(ELEMEN(dapatdicapai,pilihan-1)));
        y = Ordinat(LOCPOINT(ELEMEN(dapatdicapai,pilihan-1)));
        changePosisi(player, x, y);
        printf("Mobita sekarang berada di titik %c (%d,%d)!\n",LOCNAME(ELEMEN(dapatdicapai,pilihan -1)), x, y);
    }
}

void displayMapColor(Map peta, Queue *urutan, Mobita *player){ //INI BELUM JADIII
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
	for (i = 0; i < ROWS(m); i++){
		for (j = 0; j < COLS(m); j++){
            if (i == Absis(POSISI(*player)) && j == Ordinat(POSISI(*player))) { //INI BERARTI LOKASI MOBITA
                print_yellow(ELEMENM(m,i,j)); // harusnya pake while deh algoritma searching tapi mager
            } 
            else {
                printf("%c", ELMT(m,i,j));
            }
        }
        printf("\n");
	}
}

void help() {
    printf("1. MOVE\n"); //samuel
    printf("2. PICK UP\n"); // samuel
    printf("3. DROP OFF\n"); // samuel
    printf("4. DISPLAY MAP\n"); // saul
    printf("5. DISPLAY TO DO LIST\n"); // lewiss
    printf("6. DISPLAY IN PROGRESS\n"); // lewiss
    printf("7. BUY\n"); //jova
    printf("8. INVENTORY\n"); //ave mungkin
    printf("9. HELP\n");//udah
    printf("10. EXIT GAME\n");
    //harus ada yang ngeconvert Queue ke todolist dan inprogress berarti, mungkin diambil 5 6 juga soalnya mudah kan display doang
}

void pilihCommand(Map peta, Queue *urutan, Mobita *player){
    int pilihan ;
    printf("Silahkan pilih command: ");
    scanf("%d", &pilihan);
    if (pilihan == 1) {
        move(peta, urutan, player);
    }
    /*else if (pilihan ==3 ) {

    }*/
    else if (pilihan == 4) {
        displayMapColor(peta, urutan, player);
    }
    else if (pilihan == 9) {
        help();
    }
    else {
        printf("Pilihan yang dimasukkan salah. Silahkan masukkan opsi lain\n");
    }
    
    pilihCommand(peta, urutan,player);
}

int main() {
    int opsi,i;
    Map peta;
    DaftarPesanan daftar;
    Mobita player;
    Queue urutan;
    CreateMap(&peta);
    printf("Selamat datang di game TUBES K2 Kelompok 6\nketik 1 untuk new game\nketik 2 untuk exit\nmasukkan opsi: ");
    scanf("%d", &opsi);
    if (opsi ==1) {
        konfigurasi(&peta, &daftar); // ngebaca txt file ke program
        printf("Konfigurasi permainan berhasil\n");
        createMobita(&player);
        sortPesanan(&daftar);
        CreateQueue(&urutan);
        for (int i = 0; i < NEFF(daftar) ; i++) {
            enqueue(&urutan, ELEMEN(daftar,i));
        }
        int x = Absis(LOCPOINT(ELEMEN(MAPLOC(peta),0))); // 0 adalah headquarter
        int y = Ordinat(LOCPOINT(ELEMEN(MAPLOC(peta),0)));
        changePosisi(&player, x, y) ; // Mengubah koordinat awal nobita menjadi headquarter
        help();
        pilihCommand(peta, &urutan, &player);
    }
    return 0;
}

// Queue [9 elemen], dequeue --> [8elemen]
// in progress sama to do list linked list [kosong] [kosong]
// to do list [1 elemen todolist] [kosong]
