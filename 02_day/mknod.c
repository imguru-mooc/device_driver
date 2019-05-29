#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int mknod(const char *pathname, mode_t mode, dev_t dev);

int main()
{
	int major=243;
	int minor=0;
	char *devpath="mydev";
	mknod( devpath, 0660 | S_IFCHR, major<<8 | minor);
	// # mknod c mydev 243 0
	return 0;
}
