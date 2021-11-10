#include "tas.h"

void CreateTas(Tas *t)
{
    IDX_TOP_TAS(*t) = IDX_TAS_UNDEF;
}
void pushTas(Tas *t, ElTypeTas e){
    IDX_TOP_TAS(*t)++;
    TOP_TAS(*t) = e;
}
void popTas(Tas *t, ElTypeTas *e)
{
    MAX_ITEM(*t) = 3;
    *e = TOP_TAS(*t);
    IDX_TOP_TAS(*t)--;
}
boolean isTasEmpty(Tas t)
{
    return (IDX_TOP_TAS(t) == IDX_TAS_UNDEF);
}
boolean isTasFull(Tas t)
{
    return (IDX_TOP_TAS(t) == MAX_ITEM(t)-1);
}
void setMaxItem(Tas *t, int max)
{
    if(max > CAPACITY_TAS){
        MAX_ITEM(*t) = CAPACITY_TAS;
    } else {
        MAX_ITEM(*t) = max;
    }
}