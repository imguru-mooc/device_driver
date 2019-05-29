#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <stdio.h>

#define LED_ON     _IO( 'c', 0 )
#define LED_OFF    _IO( 'c', 1 )
#define LED_RATIO    _IOW( 'c', 2, int )

int main()
{
	int fd, ret, ratio=222;
	fd = open("/dev/mydev", O_RDWR);
    ret = ioctl(fd, LED_ON);
	if( ret < 0 )
	{
		printf("errno=%d\n", errno );
	}
    ret = ioctl(fd, LED_OFF);
	if( ret < 0 )
	{
		printf("errno=%d\n", errno );
	}
    ret = ioctl(fd, LED_RATIO, &ratio);
	if( ret < 0 )
	{
		printf("errno=%d\n", errno );
	}
	close(fd);
	return 0;
}
