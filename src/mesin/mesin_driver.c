#include <stdio.h>
#include "wordmachine.h"

int main()
{
    startInputWord();
    // display kata sampai MARK (~)
    while (currentChar != MARK)
    {
        displayKata();
        advWord();
    }

    return 0;
}