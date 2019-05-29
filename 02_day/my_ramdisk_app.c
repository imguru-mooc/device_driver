#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int length, fd1, rc;
	char *nodename = "/dev/mydev";
	char message[] = " *** TESTING CHAR/DRIVER ***\n";

	length = sizeof(message);

	if (argc > 1)
		nodename = argv[1];

	fd1 = open(nodename, O_RDWR);
	printf(" opened file descriptor first time  = %d\n", fd1);

	rc = write(fd1, message, length);
	printf("return code from write = %d on %d, message=%s\n", rc, fd1,
			message);

	memset(message, 0, length);
	lseek( fd1, 0, SEEK_SET ); 
	rc = read(fd1, message, length);
	printf("return code from read  = %d on %d, message=%s\n", rc, fd1,
			message);

	close(fd1);
	exit(0);
}

