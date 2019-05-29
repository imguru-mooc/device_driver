#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

int my_open_0 (struct inode *inode, struct file *filp)
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
	.open      = my_open_0,
	.release   = my_close_0,
};

int my_open_1 (struct inode *inode, struct file *filp)
{
	printk("my_open_1()\n");
	return 0;
}

int my_close_1 (struct inode *inode, struct file *filp)
{
	printk("my_close_1()\n");
	return 0;
}
static struct file_operations fops_1 = 
{
	.open      = my_open_1,
	.release   = my_close_1,
};
int my_open (struct inode *inode, struct file *filp)
{
	int minor;
	printk("my_open()\n");
	minor = MINOR(inode->i_rdev);
	if( minor == 0 )
	{
		filp->f_op = &fops_0;
		filp->f_op->open(inode, filp); // my_open_0();
	}
	else if( minor == 1 )
	{
		filp->f_op = &fops_1;
		filp->f_op->open(inode, filp); // my_open_1();
	}
	return 0;
}

static struct file_operations fops = 
{
	.open    = my_open,
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
