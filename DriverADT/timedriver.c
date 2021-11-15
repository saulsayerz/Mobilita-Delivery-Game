//Nama : Saul Sayers
//NIM  : 13520094 / 16520075
//Kelas: K02
//PRA-PRAKTIKUM 2

#include <stdio.h>
#include "time.h"
#include "time.c"

int main(){
    TIME time1,time2;
    printf("UJICOBA FUNGSI BACATIME, time1 dengan format hh mm ss: ");
    BacaTIME(&time1);
    TulisTIME(time1);
    printf("\nUJICOBA FUNGSI BACATIME, time2 dengan format hh mm ss: ");
    BacaTIME(&time2);
    TulisTIME(time2);
    printf("\nUJICOBA FUNGSI TEQ");
    printf("\n %d",TEQ(time1,time2));
    printf("\nUJICOBA FUNGSI TNEQ");
    printf("\n %d",TNEQ(time1,time2));
    printf("\nUJICOBA FUNGSI TLT");
    printf("\n %d",TLT(time1,time2));
    printf("\nUJICOBA FUNGSI TGT");
    printf("\n %d",TGT(time1,time2));
    printf("\nUJICOBA FUNGSI NextDetik");
    TulisTIME(NextDetik(time1));
    printf("\nUJICOBA FUNGSI NextNDetik");
    TulisTIME(NextNDetik(time1,5));
    printf("\nUJICOBA FUNGSI PrevDetik");
    TulisTIME(PrevDetik(time1));
    printf("\nUJICOBA FUNGSI PrevNDetik");
    TulisTIME(PrevNDetik(time1,5));
    printf("\nUJICOBA FUNGSI DURASI");
    printf("\n%d", Durasi(time1,time2));
    return 0 ;
}