#include "effect_list.h"
#include <stdio.h>

void createEffectList(EffectList *L){
    NEFF_EFFECT_LIST(*L) = 0;
}
void addEffect(EffectList *L, ElTypeEffectlist e){
    if(NEFF_EFFECT_LIST(*L) == EFFECT_LIST_CAPACITY){
        printf("Effect List is full\n");
    } else {
        EFFECT_LIST_ELMT(*L, NEFF_EFFECT_LIST(*L)) = e;
        NEFF_EFFECT_LIST(*L)++;
    }
}
void removeEffect(EffectList *L, ElTypeEffectlist e){
    int i = 0;
    while (i < NEFF_EFFECT_LIST(*L) && strings_not_equal_v2(EFFECT_LIST_ELMT(*L, i), e)){
        i++;
    }

    if(i < NEFF_EFFECT_LIST(*L)){
        //pergeseran array 
        for(int j = i; j < NEFF_EFFECT_LIST(*L) - 1; j++){
            EFFECT_LIST_ELMT(*L, j) = EFFECT_LIST_ELMT(*L, j + 1);
        }
        NEFF_EFFECT_LIST(*L)--;
    }
}
boolean isEffectExist(EffectList L, ElTypeEffectlist e){
    int i = 0;
    while (i < NEFF_EFFECT_LIST(L) && strings_not_equal_v2(EFFECT_LIST_ELMT(L, i), e)){
        i++;
    }
    return i < NEFF_EFFECT_LIST(L);
}