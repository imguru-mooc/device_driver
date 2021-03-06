#if 1
// interrupt version
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/wait.h>
#include <linux/poll.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>
#include <asm/uaccess.h>

#define GPIO_SW  23

static int k_temp;
static int irq;
static DECLARE_WAIT_QUEUE_HEAD(my_wait);

irqreturn_t my_irq_handler(int irq, void *devid)
{
	int value;
	printk("my_irq_handler(%d, %p)\n", irq, devid);
	value = gpio_get_value(23);	
	value ^= 1;
	if( value == 1 )
	{
		printk("Pressed  Event !!\n");
		k_temp=22;
		wake_up_interruptible(&my_wait);
	}
	else
		printk("Released Event !!\n");
	return IRQ_HANDLED;
}

int my_open (struct inode *inode, struct file *filp)
{
	printk("my_open()\n");
	k_temp = -999;
	return 0;
}

int my_close (struct inode *inode, struct file *filp)
{
	printk("my_close()\n");
	return 0;
}

ssize_t my_read(struct file *filp, char __user *buff, size_t size, loff_t *off)
{
	printk("my_read()\n");
	if( k_temp == -999 )
	{
		if( filp->f_flags & O_NONBLOCK )
			return -EAGAIN;
	}
	if( !(filp->f_flags & O_NONBLOCK) )
		wait_event_interruptible( my_wait, k_temp != -999 );
	put_user( k_temp, (int*)buff);
	k_temp=-999;
	return 4;
}

static struct file_operations fops = 
{
	.open    = my_open,
	.release = my_close,
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
	int ret;

	unsigned long flags = 3;
	printk("my_init()\n");
	irq = gpio_to_irq(23);
    ret = request_irq(irq, my_irq_handler, flags, "MY SW1 INT", 0);
	misc_register(&my_misc);
	gpio_direction_input(GPIO_SW);
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
	free_irq(irq,0);
	misc_deregister(&my_misc);
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
#endif
