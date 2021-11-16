//Nama : Saul Sayers
//NIM  : 13520094
//Kelas: K02 Alstrukdat
//PRA-PRAKTIKUM 6

#include <stdio.h>
#include "charmachine.h"
#include "wordmachine.h"
#include "../boolean.h"

boolean endWord;
Word currentWord;

void ignoreBlank(){
    while(currentChar == BLANK)
    {
        adv();
    }
}

void startWord(char filename[]){
    start(filename);
    ignoreBlank();
    if (currentChar == MARK) {
        endWord = true;
    }
    else {
        endWord = false;
        copyWord();
    }
}

void advWord () {
    ignoreBlank();
    if (currentChar == MARK) {
        endWord = true;
    }
    else {
        copyWord();
        ignoreBlank();
    }
}

void copyWord() {
    int i;
    i = 0;
    while ((currentChar != MARK) && (currentChar != BLANK) && (currentChar != '\n')){
        if (i<50) {
            currentWord.contents[i] = currentChar;
            i++;
        }
        adv();
    }
    currentWord.length = i;
}

int charToInt(char c){
    return c - '0';
}

int kataToInt(Word kata){
    int i, hasil;
    i = 0;
    hasil = 0;
    while (i < kata.length) {
        hasil = hasil*10 + charToInt(kata.contents[i]);
        i ++ ;
    }
    return hasil;
}

void displayKata() {
    int i ;
    for (i=0; i < currentWord.length; i++) {
        printf("%c", currentWord.contents[i]);
    }
    printf("\n");
}
