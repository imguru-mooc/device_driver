#include <stdio.h>
unsigned int __ffs(unsigned int word)
{
	int num = 0;

	if ((word & 0xffff) == 0) {
		num += 16;
		word >>= 16;
	}
	if ((word & 0xff) == 0) {
		num += 8;
		word >>= 8;
	}
	if ((word & 0xf) == 0) {
		num += 4;
		word >>= 4;
	}
	if ((word & 0x3) == 0) {
		num += 2;
		word >>= 2;
	}
	if ((word & 0x1) == 0)
		num += 1;
	return num;
}

#define ffz(x)  __ffs(~(x))
int main()
{
	unsigned int bitmap = 0x0f; 
	unsigned int index = 0; 
	index = ffz(bitmap);
	printf("index=%d\n", index );
	return 0;
}
