#include "listpos.c"

int main () {
    ListPos L1, L2,total ;
    int min, maks;
    readList(&L1);
    readList(&L2);
    //total = plusMinusTab(L1,L2,false);
    //displayList(total);
    //printf("%d", isListEqual(L1,L2));
    //printf("%d", indexOf(L1, 5));
    extremes(L1,&maks,&min);
    printf("%d", min);
    printf("%d", maks);
    //sort(&L1,false);
    //displayList(L1);
    //printf("%d", isAllEven(L1));
    return 0 ;
}