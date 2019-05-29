#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

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

#define LED_ON     _IO( 'c', 0 )
#define LED_OFF    _IO( 'c', 1 ) 
#define LED_RATIO  _IOW( 'c', 2 , int) 

long my_ioctl(struct file *filp, unsigned int arg, unsigned long opt)
{
	printk("my_ioctl()\n");
	
	if( _IOC_TYPE(arg) != 'c' ) 
		return -EINVAL;

	if( _IOC_NR(arg) > 2 ) 
		return -EINVAL;

	switch( arg )
	{
		case  LED_ON  : printk("LED_ON\n"); break;
		case  LED_OFF : printk("LED_OFF\n"); break;
		case  LED_RATIO : 
						{
							int ratio;
							int ret;
							ret = copy_from_user( &ratio, (void*)opt, _IOC_SIZE(arg) );
							printk("LED_RATIO, ratio=%d\n", ratio); 
						} break;
	}
	return 0;
}

static struct file_operations fops = 
{
	.open           = my_open,
	.release        = my_close,
	.unlocked_ioctl = my_ioctl,
	.compat_ioctl   = my_ioctl,
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
