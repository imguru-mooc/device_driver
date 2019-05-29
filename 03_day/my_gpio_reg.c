#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/gpio.h>
#include <asm/uaccess.h>

#define GPIO_LED 16
#define GPIO_SW  23

#define BCM_IO_BASE           0x3F000000               
#define GPIO_BASE             (BCM_IO_BASE + 0x200000)   
#define GPIO_SIZE             (256)

#define GPIO_IN(g)     (*(gpio+((g)/10)) &= ~(7<<(((g)%10)*3)))              
#define GPIO_OUT(g)    (*(gpio+((g)/10)) |= (1<<(((g)%10)*3)))

#define GPIO_SET(g)    (*(gpio+7) = 1<<g)           
#define GPIO_CLR(g)    (*(gpio+10) = 1<<g)         
#define GPIO_GET(g)    ( !!(*(gpio+13)&(1<<g)) ) 

volatile unsigned int *gpio;

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
	value = GPIO_GET( GPIO_SW );
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
	if( value == 0 )
		GPIO_CLR(GPIO_LED);
	else
		GPIO_SET(GPIO_LED);
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
	static void *map;                                   
	printk("my_init()\n");
	misc_register(&my_misc);
    map = ioremap(GPIO_BASE, GPIO_SIZE); 
	printk("%#x=>%p()\n", GPIO_BASE, map);
    gpio = (volatile unsigned int *)map;

	GPIO_OUT( GPIO_LED );
	GPIO_IN( GPIO_SW );
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
