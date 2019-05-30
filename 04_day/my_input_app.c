#if 1
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>

int main()
{
	struct input_event events[64];
	int ret, fd, flag;
	int i;

	fd = open("/dev/input/event0", O_RDWR);

	while(1)
	{
		ret = read(fd, events, sizeof events );
		for(i=0; i<(ret/(int)sizeof(struct input_event)) ; i++ )
			printf("type=%d, code=%d, value=%d\n", 
					events[i].type, events[i].code, events[i].value );
	}
	return 0;
}
#endif


