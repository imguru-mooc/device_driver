#if 1
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <poll.h>
#include <stdio.h>
int main()
{
	char buff[128];
	int ret, fd;
	struct pollfd fds[2];

	fd = open("/dev/mydev", O_RDWR);

	fds[0].fd     = 0;
	fds[0].events = POLLIN;
	fds[1].fd     = fd;
	fds[1].events = POLLIN;

	while(1)
	{
		poll( fds, 2, -1);
		if( fds[0].revents & POLLIN )
		{
			ret = read(0, buff, sizeof buff );
			buff[ret-1] = 0;
			printf("키보드=[%s]\n", buff );
		}
		if( fds[1].revents & POLLIN )
		{
			int temp;
			read(fd, &temp, sizeof temp );
			printf("온  도=[%d]\n", temp );
		}
	}
	return 0;
}
#endif

