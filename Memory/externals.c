
#include <stdlib.h>

void* AllocateImplementation(unsigned long long size)
{
	return malloc((size_t) size);
}

void FreeImplementation(void* address)
{
	free(address);
}
