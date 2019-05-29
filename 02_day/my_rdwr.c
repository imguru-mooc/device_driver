#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

static int k_temp;

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

#if 1
static char k_buff[] = "Hello User !!";
ssize_t my_read (struct file *filp, char __user *buff, size_t size, loff_t *off)
{
	int len,ret;
	printk("my_read()\n");
	len = (strlen(k_buff)<(size-1))?strlen(k_buff):(size-1);
	ret = copy_to_user( buff, k_buff, len);
	return len;
}
#endif
#if 0
static char k_buff[] = "Hello User !!";
ssize_t my_read (struct file *filp, char __user *buff, size_t size, loff_t *off)
{
	int i;
	printk("my_read()\n");
	for(i=0; k_buff[i]; i++)
	{
		if( i >= (size-1) )
			break;
		put_user( k_buff[i], buff+i );   // *(buff+i) = k_buff[i];
	}
	return i;
}
#endif

#if 0
static char k_buff[] = "Hello User !!";
ssize_t my_read (struct file *filp, char __user *buff, size_t size, loff_t *off)
{
	int i;
	printk("my_read()\n");
	for(i=0; k_buff[i]; i++)
		put_user( k_buff[i], buff+i );   // *(buff+i) = k_buff[i];
	return i;
}
#endif

#if 0
ssize_t my_read (struct file *filp, char __user *buff, size_t size, loff_t *off)
{
	printk("my_read()\n");
	k_temp = 21;
	put_user( k_temp, (int*)buff );   // *(int*)buff = k_temp;
	return 4;
}
#endif

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
