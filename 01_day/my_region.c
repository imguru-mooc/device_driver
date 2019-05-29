#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

static dev_t from;
int my_init(void)
{
	printk("my_init()\n");
	from = MKDEV(200,0);
	register_chrdev_region( from, 1, "mydev0");
	register_chrdev_region( from+1, 1, "mydev1");
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
	unregister_chrdev_region( from, 1 );
	unregister_chrdev_region( from+1, 1);
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
