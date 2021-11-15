#include "matrix.c"

int main() {
    Matrix m1,m2,m3;
    float hasildet;
    CreateMatrix(3,3,&m1);
    //CreateMatrix(3,3,&m2);
    readMatrix(&m1,3,3);
    //readMatrix(&m2,2,3);
    //m3 = multiplyMatrix(m1, m2);
    displayMatrix(m1);
    //printf("\n");
    printf("\n%f", determinant(m1));
    /*transpose(&m1);
    displayMatrix(m1);
    printf("\n");
    displayMatrix(m2);
    printf("\n");
    //displayMatrix(m3); */
    return 0;
}