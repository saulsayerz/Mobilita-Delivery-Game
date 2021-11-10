#ifndef EFFECT_LIST_H
#define EFFECT_LIST_H
#define EFFECT_LIST_CAPACITY 50 
#include "boolean.h"
typedef char* ElType;
typedef struct effectList {
    ElType effect[EFFECT_LIST_CAPACITY];
    int NEff;
} EffectList;

#define NEFF_EFFECT_LIST(L) ((L).NEff)
#define EFFECT_LIST_ELMT(L,i) ((L).effect[(i)])

#define SENTER_PENGECIL "Senter Pengecil"
#define PINTU_KEMANA_SAJA "Pintu Kemana Saja"
#define KAIN_PEMBUNGKUS_WAKTU "Kain Pembungkus Waktu"

void createEffectList(EffectList *L);
void addEffect(EffectList *L, ElType e);
void removeEffect(EffectList *L, ElType e);
boolean isEffectExist(EffectList L, ElType e);


#endif