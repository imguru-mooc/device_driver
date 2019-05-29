#include <stdio.h>

#define ARRAY_SIZE(arr)  (sizeof(arr) / sizeof((arr)[0]))

static int major=0;
int chrdevs[255]={0,};
int main()
{
    int i;
	chrdevs[254]=1;
	chrdevs[252]=1;
	while(1)
	{
		getchar();
		for (i = ARRAY_SIZE(chrdevs)-1; i > 0; i--) {
			if (chrdevs[i] == 0)
				break;
		}

		/*
		   if (i < CHRDEV_MAJOR_DYN_END)
		   pr_warn("CHRDEV \"%s\" major number %d goes below the dynamic allocation range\n",
		   name, i);

		   if (i == 0) {
		   ret = -EBUSY;
		   goto out;
		   }
		 */
		major = i;
		chrdevs[major] = 1;
		printf("major=%d\n", i);
	}
}


