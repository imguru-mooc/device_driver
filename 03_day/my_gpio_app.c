#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	int fd;
	int value, ret;
	fd = open("/dev/mydev", O_RDWR);
	while(1)
	{
		getchar();
		read( fd, &value, sizeof value );
		ret = write( fd, &value, sizeof value );
		printf("USER: value=%d, ret=%d\n", value, ret );
	}
	close(fd);
	return 0;
}
