#include <stdio.h>
#include "kmp.h"

int main(void)
{
	char* s = get_s();
	char* t = get_s();

	int* next = get_next(t);
	int ret = kmp(s, t, 0);

	printf("The position of '%s' in '%s' is %d\n", t, s, ret);

	return 0;
}