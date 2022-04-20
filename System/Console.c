
#include <stdio.h>

void ConsolePrintOut(const char *string)
{
    fprintf(stdout, "%s", string);
}

void ConsolePrintErr(const char *string)
{
    fprintf(stderr, "%s", string);
}
