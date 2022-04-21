
#include <stdio.h>

void Console_PrintOut(const char *string)
{
    fprintf(stdout, "%s", string);
}

void Console_PrintErr(const char *string)
{
    fprintf(stderr, "%s", string);
}
