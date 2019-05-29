#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/mm.h>

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

int my_mmap (struct file *filp, struct vm_area_struct *vma)
{
	unsigned long pfn;
	unsigned long p = __get_free_pages(GFP_KERNEL, 0);
	pfn = __pa(p);
	remap_pfn_range( vma, vma->vm_start, pfn>>12,  4096, vma->vm_page_prot);
	return 0;
}

static struct file_operations fops = 
{
	.open    = my_open,
	.release = my_close,
	.mmap    = my_mmap,
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
