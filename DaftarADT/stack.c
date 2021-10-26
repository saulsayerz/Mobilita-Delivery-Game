// NAMA  : SAUL SAYERS
// NIM   : 13520094 / 16520075
// KELAS : K02 Alstrukdat
// PRA PRAKTIKUM  8 ADT STACK

#include <stdio.h>
#include "stack.h"

void CreateStack(Stack *s){
    IDX_TOP(*s) = IDX_UNDEF ;
}

boolean isEmpty(Stack s){
    return IDX_TOP(s) == IDX_UNDEF ;
}

boolean isFull(Stack s){
    return IDX_TOP(s) == CAPACITY - 1 ;
}

void push(Stack *s, ElType val){
    IDX_TOP(*s) += 1;
    TOP(*s) = val;
}

void pop(Stack *s, ElType *val){
    *val = TOP(*s) ;
    IDX_TOP(*s) -= 1;
}
