#include "tas.h"

void createTas(Tas *t)
{
    IDX_TOP_TAS(*t) = IDX_TAS_UNDEF;
    MAX_ITEM(*t) = 3;
    UPPERMOST_PERISHABLE_INITIAL_TIME(*t) = -1;
}
void pushTas(Tas *t, ElTypeTas e)
{
    IDX_TOP_TAS(*t)
    ++;
    TOP_TAS(*t) = e;
    if (JENIS(e) == 'P')
    {
        UPPERMOST_PERISHABLE_INITIAL_TIME(*t) = PERISH(e);
    }
}
void popTas(Tas *t, ElTypeTas *e)
{
    Tas temp;
    ElTypeTas tempEl;
    boolean perishableFound = false;
    
    MAX_ITEM(*t) = 3;
    *e = TOP_TAS(*t);
    IDX_TOP_TAS(*t)
    --;

    temp = *t;
    while (!isTasEmpty(temp) && !perishableFound)
    {
        popTas(&temp, &tempEl);
        if (JENIS(tempEl) == 'P')
        {
            UPPERMOST_PERISHABLE_INITIAL_TIME(*t) = PERISH(tempEl);
            perishableFound = true;
        }
    }
}
boolean isTasEmpty(Tas t)
{
    return (IDX_TOP_TAS(t) == IDX_TAS_UNDEF);
}
boolean isTasFull(Tas t)
{
    return (IDX_TOP_TAS(t) >= MAX_ITEM(t) - 1);
}
void setMaxItem(Tas *t, int max)
{
    if (max > CAPACITY_TAS)
    {
        MAX_ITEM(*t) = CAPACITY_TAS;
    }
    else
    {
        MAX_ITEM(*t) = max;
    }
}
void decreasePerishableTimeInTas(Tas *t)
{
    Tas j = *t;
    Tas g;
    createTas(&g);
    Pesanan e;
    while (!isTasEmpty(j))
    {
        popTas(&j, &e);
        if (e.perishable > 0)
        {
            e.perishable--;
        }

        if (e.perishable != 0)
        {
            pushTas(&g, e);
        }
    }

    while (!isTasEmpty(g))
    {
        popTas(&g, &e);
        pushTas(&j, e);
    }
    *t = j;
}


void resetMostRecentlyPerishableTimeInTas(Tas *t)
{
    if (UPPERMOST_PERISHABLE_INITIAL_TIME(*t) == -1)
    {
        // DO NOTHING
    }
    else
    {
        Tas j = *t;
        Tas g;
        createTas(&g);
        Pesanan e;
        while (JENIS(TOP_TAS(j)) != 'P')
        {
            popTas(&j, &e);
            pushTas(&g, e);
        }

        if (JENIS(TOP_TAS(j)) == 'P')
        {
            PERISH(TOP_TAS(j)) = UPPERMOST_PERISHABLE_INITIAL_TIME(*t);
        }
        while (!isTasEmpty(g))
        {
            popTas(&g, &e);
            pushTas(&j, e);
        }

        *t = j;
    }
}
