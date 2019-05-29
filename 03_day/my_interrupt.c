#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>

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

static struct miscdevice my_misc =
{
	.minor =  MISC_DYNAMIC_MINOR, 
	.name  = "mydev",
	.fops  = &fops,
};

static int irq;

irqreturn_t my_irq_handler(int irq, void *devid)
{
	int value;
	printk("my_irq_handler(%d, %p)\n", irq, devid);
	value = gpio_get_value(23);	
	value ^= 1;
	if( value == 1 )
		printk("Pressed  Event !!\n");
	else
		printk("Released Event !!\n");
	return IRQ_HANDLED;
}

int my_init(void)
{
	int ret;
	unsigned long flags = 3;
	printk("my_init()\n");
	misc_register(&my_misc);
	irq = gpio_to_irq(23);
	printk("irq=%d()\n", irq);
    ret = request_irq(irq, my_irq_handler, flags, "MY SW1 INT", 0);
	gpio_direction_input(23);
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
