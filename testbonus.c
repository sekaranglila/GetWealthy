#include <stdio.h>

int main()
{
    int bonus;

    bonus = ((rand() % (500 + 1 - 100))  + 100) * 1000;
    printf("%d", bonus);
    return 0;
}
