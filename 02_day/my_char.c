#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>

int my_open_0(struct inode *inode, struct file *filp)
{
	printk("my_open_0()\n");
	return 0;
}

int my_close_0 (struct inode *inode, struct file *filp)
{
	printk("my_close_0()\n");
	return 0;
}

static struct file_operations fops_0 = 
{
	.open    = my_open_0,
	.release = my_close_0,
};

static dev_t from;
static struct cdev *my_cdev;
int my_init(void)
{
	printk("my_init()\n");
	from = MKDEV(200,0);
	register_chrdev_region( from, 1, "mydev0");

	my_cdev = cdev_alloc();
	cdev_init( my_cdev, &fops_0 );
	cdev_add( my_cdev, from, 1 );
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
	cdev_del( my_cdev );
	unregister_chrdev_region( from, 1 );
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
