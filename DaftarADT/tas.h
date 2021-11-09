#ifndef TAS_H
#define TAS_H
#include "boolean.h"
#include "pesanan.h"
#define CAPACITY_TAS 100
#define IDX_TAS_UNDEF -1
typedef Pesanan Item;
typedef Item ElTypeTas;

typedef struct tas {
    ElTypeTas buffer[CAPACITY_TAS];
    int idxTopTas;
    int maxItem;
} Tas;

#define IDX_TOP_TAS(t) (t).idxTopTas
#define     TOP_TAS(t) (t).buffer[(t).idxTopTas]
#define     MAX_ITEM(t) (t).maxItem

void createTas(Tas *t);
void pushTas(Tas *t, ElTypeTas e);
void popTas(Tas *t, ElTypeTas *e);
boolean isTasEmpty(Tas t);
boolean isTasFull(Tas t);
void setMaxItem(Tas *t, int max);

#endif



