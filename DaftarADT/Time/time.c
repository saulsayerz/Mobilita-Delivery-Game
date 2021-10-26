//Nama : Saul Sayers
//NIM  : 13520094 / 16520075
//Kelas: K02
//PRA-PRAKTIKUM 2

#include <stdio.h>
#include "time.h"
#include <math.h>

boolean IsTIMEValid (int H, int M, int S){
    return (0<=H) && (H<24) && (0<=M) && (M<60) && (0<=S) && (S<60);
}

TIME MakeTIME (int HH, int MM, int SS){
    TIME time;
    Hour(time)=HH;
    Minute(time)=MM;
    Second(time)=SS;
    return time;
}

void BacaTIME (TIME * T){
    boolean benar=false;
    int j,m,d;
    while(benar == false){
        scanf("%d %d %d", &j,&m,&d);
        benar=IsTIMEValid(j,m,d);
        if (benar == false) {
            printf("Jam tidak valid\n");
        }
    }
    *T=MakeTIME(j,m,d);
}

void TulisTIME (TIME T){
   printf("%02d:%02d:%02d", Hour(T), Minute(T), Second(T));
}

long TIMEToDetik (TIME T)
{
    long Detik;
    Detik = 3600 * Hour(T) + 60 * Minute(T) + Second(T);
    return Detik;
}


TIME DetikToTIME (long N)
{
    TIME T;
    while (N < 0) {
        N += 86400;
    }
    T = MakeTIME((N % 86400) / 3600, (N % 3600) / 60, N % 60);
    return T;
}

boolean TEQ (TIME T1, TIME T2){
    return (Hour(T1)==Hour(T2)) && (Minute(T1)==Minute(T2)) && (Second(T1)==Second(T2));
}

boolean TNEQ (TIME T1, TIME T2){
    return !TEQ(T1,T2);
}

boolean TLT (TIME T1, TIME T2){
    return TIMEToDetik(T1)<TIMEToDetik(T2);
}

boolean TGT (TIME T1, TIME T2){
    return TIMEToDetik(T1)>TIMEToDetik(T2);
}

TIME NextDetik (TIME T)
{
    TIME Tnext;
    Tnext = DetikToTIME(TIMEToDetik(T) + 1);
    return Tnext;
}
TIME NextNDetik (TIME T, int N)
{
    TIME Tnext ;
    Tnext = DetikToTIME(TIMEToDetik(T) + N);
    return Tnext;
}
TIME PrevDetik (TIME T)
{
    TIME Tprev;
    Tprev = DetikToTIME(TIMEToDetik(T) - 1);
    return Tprev;
}
TIME PrevNDetik (TIME T, int N)
{
    TIME Tprev;
    Tprev = DetikToTIME(TIMEToDetik(T) - N);
    return Tprev;
}

long Durasi (TIME TAw, TIME TAkh){
    long durasi;
    if(TLT(TAkh,TAw)){
        durasi = TIMEToDetik(TAkh)-TIMEToDetik(TAw) + 86400;
    } else {
        durasi = TIMEToDetik(TAkh) - TIMEToDetik(TAw);
    }
    return durasi;
}
