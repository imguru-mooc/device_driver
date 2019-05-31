#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include "my_keys.h"

static struct my_keys_button my_button_table[] = {
	{ KEY_VOLUMEUP, 23, 1 },
};

static struct my_keys_platform_data my_keys_data = {
	.buttons = my_button_table,
	.nbuttons = sizeof(my_button_table)/sizeof(my_button_table[0]),
};

static struct platform_device dev =
{
	.name = "my-keys",
	.dev = {
		.platform_data = &my_keys_data,
	},
};

int my_init(void)
{
	printk("my_init()\n");
	printk("&dev=%p\n", &dev);
	platform_device_register(&dev);
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
	platform_device_unregister(&dev);
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
