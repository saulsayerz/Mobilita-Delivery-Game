#ifndef EFFECT_LIST_H
#define EFFECT_LIST_H
#define EFFECT_LIST_CAPACITY 50 
#include "boolean.h"
typedef char* ElTypeEffectlist;
typedef struct effectList {
    ElTypeEffectlist effect[EFFECT_LIST_CAPACITY];
    int NEff;
} EffectList;

#define NEFF_EFFECT_LIST(L) ((L).NEff)
#define EFFECT_LIST_ELMT(L,i) ((L).effect[(i)])

#define SENTER_PENGECIL "Senter Pengecil"
#define PINTU_KEMANA_SAJA "Pintu Kemana Saja"
#define KAIN_PEMBUNGKUS_WAKTU "Kain Pembungkus Waktu"

void createEffectList(EffectList *L);
void addEffect(EffectList *L, ElTypeEffectlist e);
void removeEffect(EffectList *L, ElTypeEffectlist e);
boolean isEffectExist(EffectList L, ElTypeEffectlist e);


#endif