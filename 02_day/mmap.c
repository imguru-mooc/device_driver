#if 1
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
int main()
{
	int fd;
	char *p;
	fd = open("aaa", O_RDWR | O_TRUNC | O_CREAT , 0666 );
	ftruncate( fd, 100 );
    p = mmap( 0, 100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	p[99] = 'x';
	munmap( p, 100 );
	close(fd);
	return 0;
}
#endif

#if 0
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
	int fd;
	fd = open("aaa", O_RDWR | O_TRUNC | O_CREAT , 0666 );
	ftruncate( fd, 100 );
	lseek( fd, -1, SEEK_END );
	write(fd, "x", 1 );  //  p[99] = 'x';
	close(fd);
	return 0;
}
#endif
