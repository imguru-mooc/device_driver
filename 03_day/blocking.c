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

	fd = open("myfifo", O_RDWR);

	fcntl(  0, F_SETFL, O_NONBLOCK);
	fcntl( fd, F_SETFL, O_NONBLOCK);
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
			ret = read(fd, buff, sizeof buff );
			buff[ret-1] = 0;
			printf("myfifo=[%s]\n", buff );
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
#include <poll.h>
#include <stdio.h>
int main()
{
	char buff[128];
	int ret;
	struct pollfd fds[1];
	fcntl( 0, F_SETFL, O_NONBLOCK);
	fds[0].fd     = 0;
	fds[0].events = POLLIN;

	while(1)
	{
		poll( fds, 1, -1);
		ret = read(0, buff, sizeof buff );
		if(ret < 0 )
		{
			// EWOULDBLOCK
			// printf("errno=%d, msg=%s\n", errno, strerror(errno) );
			if( errno != EWOULDBLOCK )
			 	printf("errno=%d, msg=%s\n", errno, strerror(errno) );
		}
		else
		{
			buff[ret-1] = 0;
			printf("키보드=[%s]\n", buff );
		}
	}
	return 0;
}
#endif

