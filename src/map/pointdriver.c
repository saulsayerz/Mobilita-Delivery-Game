#include <stdio.h>

typedef struct TES {int x; int y;} point ;

int main () {
    point A ;
    A.x = 2;
    A.y = 4;
    printf("%d %d", A.x, A.y) ;
    return 0;
}
