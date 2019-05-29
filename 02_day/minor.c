#include <stdio.h>
#define DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))
#define BITS_PER_BYTE		8
#define BITS_TO_LONGS(nr)	DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(long))
#define DECLARE_BITMAP(name,bits) \
	unsigned long name[BITS_TO_LONGS(bits)]
#define DYNAMIC_MINORS 64 
static DECLARE_BITMAP(misc_minors, DYNAMIC_MINORS);

#define BITS_PER_LONG 32
#define BIT_MASK(nr)		(1UL << ((nr) % BITS_PER_LONG))
#define BIT_WORD(nr)		((nr) / BITS_PER_LONG)

unsigned long __ffs(unsigned long word)
{
	int num = 0;

#if BITS_PER_LONG == 64
	if ((word & 0xffffffff) == 0) {
		num += 32;
		word >>= 32;
	}
#endif
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

#define ffz(x) __ffs( ~(x) )
#define min(a,b) (((a)<(b))?(a):(b))

unsigned long find_first_zero_bit(const unsigned long *addr, unsigned long size)
{
	unsigned long idx;

	for (idx = 0; idx * BITS_PER_LONG < size; idx++) {
		if (addr[idx] != ~0UL)
			return min(idx * BITS_PER_LONG + ffz(addr[idx]), size);
	}

	return size;
}
void set_bit(int nr, volatile unsigned long *addr)
{
	unsigned long mask = BIT_MASK(nr);
	unsigned long *p = ((unsigned long *)addr) + BIT_WORD(nr);
	unsigned long flags;
	*p  |= mask;
}
int misc_register( int *minor )
{
	int is_dynamic = (*minor == 255);

	if (is_dynamic) {
		int i = find_first_zero_bit(misc_minors, DYNAMIC_MINORS);
		*minor = DYNAMIC_MINORS - i - 1;
		set_bit(i, misc_minors);
	} 
	return 0;
}

int main()
{
	int minor=255;
	set_bit(0,misc_minors);
	set_bit(1,misc_minors);
	set_bit(2,misc_minors);
	set_bit(4,misc_minors);
	while(1)
	{
		getchar();
		misc_register(&minor);
		printf("minor=%d\n", minor);
		minor=255;
	}
	return 0;
}
