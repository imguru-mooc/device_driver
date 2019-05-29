#if 1
#include <unistd.h>
#include <stdio.h>

int main()
{
	ssize_t ret;
	char buff[10];
    ret = read(0, buff, sizeof buff);
	buff[ret-1] = 0;
	printf("buff=[%s], ret=%lu\n", buff, ret );
	return 0;
}
#endif

#if 0
#include <unistd.h>
#include <stdio.h>

int main()
{
	ssize_t ret;
	char buff[128];
    ret = read(0, buff, sizeof buff);
	printf("ret=%lu\n", ret );
	return 0;
}
#endif
