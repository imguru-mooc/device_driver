#if 1
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
	char buff[128];
	int ret, fd, flag;
	int temp;

	fd = open("/dev/mydev", O_RDWR);
	flag = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, flag|O_NONBLOCK);

	while(1)
	{
		ret = read(fd, &temp, sizeof temp );
		if( ret < 0 )
		{
			if( errno != EAGAIN )
				exit(1);
			//else
			//	perror( "read" );
		}
		else
		{
			printf("온  도=[%d]\n", temp );
		}
	}
	return 0;
}
#endif

#if 0
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
int main()
{
	char buff[128];
	int ret, fd;

	fd = open("/dev/mydev", O_RDWR);

	while(1)
	{
		int temp;
		read(fd, &temp, sizeof temp );
		printf("온  도=[%d]\n", temp );
	}
	return 0;
}
#endif

