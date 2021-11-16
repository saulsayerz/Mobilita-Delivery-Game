#include <stdio.h>
#include "wordmachine.h"

boolean endWord;
Word currentWord;

void ignoreBlank()
{
    while (currentChar == BLANK)
    {
        adv();
    }
}

void startWord(char filename[])
{
    start(filename);
    ignoreBlank();
    if (currentChar == MARK)
    {
        endWord = true;
    }
    else
    {
        endWord = false;
        copyWord();
    }
}

void startInputWord()
{
    startInput();
    ignoreBlank();
    if (currentChar == MARK)
    {
        endWord = true;
    }
    else
    {
        endWord = false;
        copyWord();
    }
}

void advWord()
{
    ignoreBlank();
    if (currentChar == MARK)
    {
        endWord = true;
    }
    else
    {
        copyWord();
        ignoreBlank();
    }
}

void copyWord()
{
    int i;
    i = 0;
    while ((currentChar != MARK) && (currentChar != BLANK) && (currentChar != '\n'))
    {
        if (i < 50)
        {
            currentWord.contents[i] = currentChar;
            i++;
        }
        adv();
    }
    currentWord.length = i;
}

int charToInt(char c)
{
    return c - '0';
}

int kataToInt(Word kata)
{
    int i, hasil;
    i = 0;
    hasil = 0;
    while (i < kata.length)
    {
        hasil = hasil * 10 + charToInt(kata.contents[i]);
        i++;
    }
    return hasil;
}

char* akusisi(Word kata)
{
    char *akusisiKata;
    int i = 0;
    while (i < kata.length)
    {
        *(akusisiKata + i) = kata.contents[i];
        i++;
    }
    return akusisiKata;
}

void displayKata()
{
    int i;
    for (i = 0; i < currentWord.length; i++)
    {
        printf("%c", currentWord.contents[i]);
    }
    printf("\n");
}

int string_length(char *str)
{
    char *ptrstr;
    int result;

    ptrstr = str;
    for (result = 0; *ptrstr; ++result)
        ++ptrstr;
    return result;
}

int strings_not_equal(Word str1, char *str2)
{
    int length1;
    char *ptr1;
    char *ptr2;

    length1 = str1.length;
    if (length1 != string_length(str2))
        return 1;

    ptr1 = str1.contents;
    ptr2 = str2;
    if (*ptr1)
    {
        while ((*ptr1 == *ptr2))
        {
            --length1;
            ++ptr1;
            ++ptr2;
            if (!length1)
                return 0;
        }
        return 1;
    }
    return 0;
}

int strings_not_equal_v2(char *str1, char *str2)
{
    char *ptr1;
    char *ptr2;
    int length1;

    length1 = string_length(str1);
    if (length1 != string_length(str2))
        return 1;

    ptr1 = str1;
    ptr2 = str2;
    if (*ptr1)
    {
        while ((*ptr1 == *ptr2))
        {
            ++ptr1;
            ++ptr2;
            if (!*ptr1)
                return 0;
        }
        return 1;
    }
    return 0;
}