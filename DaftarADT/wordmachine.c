//Nama : Saul Sayers
//NIM  : 13520094
//Kelas: K02 Alstrukdat
//PRA-PRAKTIKUM 6

#include <stdio.h>
#include "charmachine.h"
#include "wordmachine.h"
#include "boolean.h"

boolean endWord;
Word currentWord;

void ignoreBlank(){
    while(currentChar == BLANK)
    {
        adv();
    }
}

void startWord(){
    start();
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
    while ((currentChar != MARK) && (currentChar != BLANK)){
        if (i<50) {
            currentWord.contents[i] = currentChar;
            i++;
        }
        adv();
    }
    currentWord.length = i;
}
