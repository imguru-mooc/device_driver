#if 1
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int code;
	int value;
} EVENT;

int main()
{
	EVENT events[64];
	int ret, fd, flag;
	int i;

	fd = open("/dev/mydev", O_RDWR);

	while(1)
	{
		ret = read(fd, events, sizeof events );
		for(i=0; i<(ret/(int)sizeof(EVENT)) ; i++ )
			printf("code=%d, value=%d\n", events[i].code, events[i].value );
	}
	return 0;
}
#endif


