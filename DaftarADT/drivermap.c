#include <stdio.h>
#include "map.c"

int main() {
    Map peta;
    CreateMap(&peta);
    MAPCOL(peta) = 8;
    MAPROW(peta) = 8;
    displayMap(peta);
    konfigurasi();
    return 0;
}