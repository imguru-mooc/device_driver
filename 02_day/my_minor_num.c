#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>

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

static dev_t first;
static struct cdev *my_cdev;
static int count=1;
int my_init(void)
{
	printk("my_init()\n");
	alloc_chrdev_region(&first, 0, count, "mydev");
	printk("Major number = %d, Minor number = %d\n", 
			MAJOR(first), MINOR(first));
	my_cdev = cdev_alloc();
	cdev_init(my_cdev, &fops);
	cdev_add(my_cdev, first, count);
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
	cdev_del(my_cdev);
	unregister_chrdev_region(first, 1);
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
