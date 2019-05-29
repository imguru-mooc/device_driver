#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

static struct file_operations fops;

static int my_major;
int my_init(void)
{
	printk("my_init()\n");
	my_major = register_chrdev( 0, "mydev", &fops);
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
	unregister_chrdev( my_major, "mydev" );
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
