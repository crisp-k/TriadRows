#include <stdio.h>
#include <string.h>

int main(void)
{
    char string1[10] = "Abat";
    char string2[10] = "BThat";

    printf("Val: %d\n", strcmp(string2, string1));

    return 0;
}