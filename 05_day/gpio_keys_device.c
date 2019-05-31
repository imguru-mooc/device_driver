#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <linux/gpio_keys.h>

static struct gpio_keys_button simpad_button_table[] = {
	{ KEY_POWER, 23, 1, "power button" },
};

static struct gpio_keys_platform_data simpad_keys_data = {
	.buttons = simpad_button_table,
	.nbuttons = ARRAY_SIZE(simpad_button_table),
};

static struct platform_device simpad_keys = {
	.name = "gpio-keys",
	.dev = {
		.platform_data = &simpad_keys_data,
	},
};

static int my_init(void)
{
	printk("my_init()\n");
	platform_device_register(&simpad_keys);
	return 0;
}

static void my_exit(void)
{
	printk("my_exit()\n");
	platform_device_unregister(&simpad_keys);
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
