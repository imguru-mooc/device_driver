#if 1
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	int fd;
	char buff[10];
	int ret;
	fd = open("/dev/mydev", O_RDONLY);
	ret = read( fd, buff, sizeof(buff));
	buff[ret] = 0;
	printf("buff=[%s], ret=%d\n", buff , ret );
	close(fd);
	return 0;
}
#endif

#if 0
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	int fd;
	int temp,ret;
	fd = open("/dev/mydev", O_RDONLY);
	ret = read( fd, &temp, sizeof(temp));
	printf("temp=%d, ret=%d\n", temp , ret );
	close(fd);
	return 0;
}
#endif
