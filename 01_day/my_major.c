#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

int my_open (struct inode *inode, struct file *filp)
{
	printk("my_open()\n");
	return 0;
}

int my_close (struct inode *inode, struct file *filp)
{
	printk("my_close()\n");
	return 0;
}

static struct file_operations fops = 
{
	.open    = my_open,
	.release = my_close,
};

int my_init(void)
{
	printk("my_init()\n");
	register_chrdev( 200, "mydev", &fops);
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
	unregister_chrdev( 200, "mydev" );
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
