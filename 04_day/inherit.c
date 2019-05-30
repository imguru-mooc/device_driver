#if 1
#include <stdio.h>
struct AAA
{
	int a;
};

struct BBB
{
	struct AAA aaa;
	int b;
};

int main()
{
	struct BBB bbb;
	printf("sizeof(bbb)=%lu\n", sizeof(bbb));
	return 0;
}
#endif
#if 0
#include <stdio.h>
class AAA
{
	int a;
};

class BBB : public AAA
{
	int b;
};

int main()
{
	BBB bbb;
	printf("sizeof(bbb)=%lu\n", sizeof(bbb));
	return 0;
}
#endif
