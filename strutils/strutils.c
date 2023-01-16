#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strutils.h"


int main()
{
    char *str = "   one two three threethree four five six    seven   ";
    char *deletion = "three";
    printf("original string = \"%s\"\ndeletion string = \"%s\"\n", str, deletion);
    char *final = str_rm(str, deletion, 0);
    printf("final string = \"%s\"\n", final);
    printf("final[strlen(final)] is NULL terminated? = %d\n",(final[strlen(final)] == '\0'));
    final = str_rm(str, deletion, 1);
    printf("(space limited) final string = \"%s\"\n", final);
    printf("final[strlen(final)] is NULL terminated? = %d\n",(final[strlen(final)] == '\0'));
    return 0;
}
