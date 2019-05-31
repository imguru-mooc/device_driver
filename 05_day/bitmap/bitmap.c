#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#define BITS_PER_LONG 64
#define __KERNEL_DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))
#define DIV_ROUND_UP __KERNEL_DIV_ROUND_UP
#define BIT(nr)			(1UL << (nr))
#define BIT_ULL(nr)		(1ULL << (nr))
#define BIT_MASK(nr)		(1UL << ((nr) % BITS_PER_LONG))
#define BIT_WORD(nr)		((nr) / BITS_PER_LONG)
#define BIT_ULL_MASK(nr)	(1ULL << ((nr) % BITS_PER_LONG_LONG))
#define BIT_ULL_WORD(nr)	((nr) / BITS_PER_LONG_LONG)
#define BITS_PER_BYTE		8
#define BITS_TO_LONGS(nr)	DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(long))

#define small_const_nbits(nbits) \
	(__builtin_constant_p(nbits) && (nbits) <= BITS_PER_LONG)

void set_bit(int nr, volatile unsigned long *addr)
{
	unsigned long mask = BIT_MASK(nr);
	unsigned long *p = ((unsigned long *)addr) + BIT_WORD(nr);
	unsigned long flags;

	*p  |= mask;
}

void bitmap_zero(unsigned long *dst, unsigned int nbits)
{
	if (small_const_nbits(nbits))
		*dst = 0UL;
	else {
		unsigned int len = BITS_TO_LONGS(nbits) * sizeof(unsigned long);
		memset(dst, 0, len);
	}
}

static int __bitmap_parselist(const char *buf, unsigned int buflen,
		int is_user, unsigned long *maskp,
		int nmaskbits)
{
	unsigned int a, b, old_a, old_b;
	unsigned int group_size, used_size;
	int c, old_c, totaldigits, ndigits;
	const char *ubuf = (const char *)buf;
	int at_start, in_range, in_partial_range;

	totaldigits = c = 0;
	old_a = old_b = 0;
	group_size = used_size = 0;
	bitmap_zero(maskp, nmaskbits);
	do {
		at_start = 1;
		in_range = 0;
		in_partial_range = 0;
		a = b = 0;
		ndigits = totaldigits;

		/* Get the next cpu# or a range of cpu#'s */
		while (buflen) {
			old_c = c;
			if (is_user) {
				if ( c=*ubuf++)
					return -EFAULT;
			} else
				c = *buf++;
			buflen--;
			if (isspace(c))
				continue;

			if (c == '\0' || c == ',')
				break;

			if ((totaldigits != ndigits) && isspace(old_c))
				return -EINVAL;

			if (c == '/') {
				used_size = a;
				at_start = 1;
				in_range = 0;
				a = b = 0;
				continue;
			}

			if (c == ':') {
				old_a = a;
				old_b = b;
				at_start = 1;
				in_range = 0;
				in_partial_range = 1;
				a = b = 0;
				continue;
			}

			if (c == '-') {
				if (at_start || in_range)
					return -EINVAL;
				b = 0;
				in_range = 1;
				at_start = 1;
				continue;
			}

			if (!isdigit(c))
				return -EINVAL;

			b = b * 10 + (c - '0');
			if (!in_range)
				a = b;
			at_start = 0;
			totaldigits++;
		}
		if (ndigits == totaldigits)
			continue;
		if (in_partial_range) {
			group_size = a;
			a = old_a;
			b = old_b;
			old_a = old_b = 0;
		}
		/* if no digit is after '-', it's wrong*/
		if (at_start && in_range)
			return -EINVAL;
		if (!(a <= b) || !(used_size <= group_size))
			return -EINVAL;
		if (b >= nmaskbits)
			return -ERANGE;
		while (a <= b) {
			if (in_partial_range) {
				static int pos_in_group = 1;

				if (pos_in_group <= used_size)
					set_bit(a, maskp);

				if (a == b || ++pos_in_group > group_size)
					pos_in_group = 1;
			} else
				set_bit(a, maskp);
			a++;
		}
	} while (buflen && c == ',');
	return 0;
}

char *strchrnul(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	return (char *)s;
}
int bitmap_parselist(const char *bp, unsigned long *maskp, int nmaskbits)
{
	char *nl  = strchrnul(bp, '\n');
	int len = nl - bp;

	return __bitmap_parselist(bp, len, 0, maskp, nmaskbits);
}
int main()
{
	int i, ret;
	unsigned long bitmap = 0;
	char buff[1024];
	printf("bit input:");
	ret = read(0, buff, sizeof buff );
	buff[ret] = 0;
	bitmap_parselist(buff, &bitmap, 64 );
	printf("%lx\n", bitmap);
	return 0;
}
