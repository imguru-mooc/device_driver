#if 1
#include <stdio.h>
int main()
{
	unsigned int info = 0;

	info |= 1<<10;
	info |= 4<<7;
	info |= 77;

	printf("year=%d, sex=%d, score=%d\n",
			(info>>7)&0x7, (info>>10)&0x1, info&0x7f );

	return 0;
}
#endif
#if 0
#include <stdio.h>
int main()
{
	int year;
	int sex;
	int score;

	year = 4;
	sex  = 1;
	score = 77;

	printf("year=%d, sex=%d, score=%d\n",
			year, sex, score );

	return 0;
}
#endif
