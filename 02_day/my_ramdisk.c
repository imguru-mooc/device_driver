#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

static char *ramdisk;
static size_t ramdisk_size = (16 * PAGE_SIZE);

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

static ssize_t my_write(struct file *file, const char __user * buf, size_t lbuf,
		loff_t * ppos)
{
	int nbytes, maxbytes, bytes_to_do;
	maxbytes = ramdisk_size - *ppos;
	bytes_to_do = maxbytes > lbuf ? lbuf : maxbytes;
	if (bytes_to_do == 0)
		pr_warning("Reached end of the device on a write");
	nbytes =
		bytes_to_do - copy_from_user(ramdisk + *ppos, buf, bytes_to_do);
	*ppos += nbytes;
	pr_info("\n Leaving the   WRITE function, nbytes=%d, pos=%d\n",
			nbytes, (int)*ppos);
	return nbytes;
}

static ssize_t my_read(struct file *file, char __user * buf, size_t lbuf, loff_t * ppos)
{
	int nbytes, maxbytes, bytes_to_do;
	maxbytes = ramdisk_size - *ppos;
	bytes_to_do = maxbytes > lbuf ? lbuf : maxbytes;
	if (bytes_to_do == 0)
		pr_info("Reached end of the device on a read");
	nbytes = bytes_to_do - copy_to_user(buf, ramdisk + *ppos, bytes_to_do);
	*ppos += nbytes;
	pr_info("\n Leaving the   READ function, nbytes=%d, pos=%d\n",
			nbytes, (int)*ppos);
	return nbytes;
}


static loff_t my_lseek(struct file *file, loff_t offset, int orig)
{
	loff_t testpos;
	switch (orig) {
		case SEEK_SET:	testpos = offset;	                  break;
		case SEEK_CUR:	testpos = file->f_pos + offset; 	break;
		case SEEK_END:	testpos = ramdisk_size + offset;	break;
		default:
						return -EINVAL;
	}
	testpos = testpos < ramdisk_size ? testpos : ramdisk_size;
	testpos = testpos >= 0 ? testpos : 0;
	file->f_pos = testpos;
	pr_info("Seeking to pos=%ld\n", (long)testpos);
	return testpos;
}


static struct file_operations fops = 
{
	.open    = my_open,
	.release = my_close,
	.write   = my_write,
	.read    = my_read,
	.llseek  = my_lseek,
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
	ramdisk = kmalloc(ramdisk_size, GFP_KERNEL);
	misc_register(&my_misc);
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
	misc_deregister(&my_misc);
	kfree(ramdisk);
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
