#if 1
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
int main()
{
	int fd;
	char *p;
	fd = open("/dev/mydev", O_RDWR  );
    p = mmap( 0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	printf("p=%p\n", p );
	getchar();
	sprintf(p, "hello mmap");
	printf( "[%s]\n", p);
	munmap( p, 4096 );
	getchar();
	close(fd);
	return 0;
}
#endif

