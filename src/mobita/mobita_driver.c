#include <stdio.h>
#include "mobita.h"

int main()
{
    Mobita anak;
    createMobita(&anak);
    addOneToWaktu(&anak);
    addTwoToWaktu(&anak);
    addTwoToWaktu(&anak);
    decrementWaktu(&anak, 3);

    printf("%d = 1\n", WAKTU(anak));

    addUang(&anak, 50000);
    // useUang(&anak, 90000);
    useUang(&anak, 20000);

    // 40000 karena initial uang 10000
    printf("%d = 40000\n", UANG(anak));

    changePosisi(&anak, 5, 11);
    POINT pos = POSISI(anak);
    printf("%d %d = 5 11\n", Absis(pos), Ordinat(pos));

    printf("%d\n = 0", checkHeavy(&anak));
    return 0;
}