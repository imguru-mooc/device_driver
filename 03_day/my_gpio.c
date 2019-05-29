#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/gpio.h>
#include <asm/uaccess.h>

#define GPIO_LED 16
#define GPIO_SW  23

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

ssize_t my_read  (struct file *filp, char __user *buff, size_t size, loff_t *off)
{
	int value =0;
	printk("my_read()\n");
	value = gpio_get_value( GPIO_SW );
	value ^= 1;
	put_user( value, (int*)buff);
	return 4;
}

ssize_t my_write (struct file *filp, const char __user *buff, size_t size, loff_t *off)
{
	int value;
	printk("my_write()\n");
	get_user( value, (int*)buff);
	printk("KERNEL: value=%d\n", value );
	gpio_set_value( GPIO_LED, value );
	return 4;
}

static struct file_operations fops = 
{
	.open    = my_open,
	.release = my_close,
	.write   = my_write,
	.read    = my_read,
};

static struct miscdevice my_misc =
{
	.minor =  MISC_DYNAMIC_MINOR, 
	.name  = "mydev",
	.fops  = &fops,
};

int my_init(void)
{
	printk("my_init()\n");
	misc_register(&my_misc);
	gpio_direction_output(GPIO_LED, 0);
	gpio_direction_input(GPIO_SW);
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
	misc_deregister(&my_misc);
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
