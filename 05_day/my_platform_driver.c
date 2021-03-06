#if 1
// interrupt version
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/input.h>
#include <linux/poll.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>
#include <linux/platform_device.h>
#include <asm/uaccess.h>
#include "my_keys.h"

#define GPIO_SW_2  24

static struct input_dev *my_input;
static int irq_1;
static int irq_2;
static const struct my_keys_platform_data *pdata;
static const struct my_keys_button *button;

irqreturn_t my_irq_handler_1(int irq, void *devid)
{
	int value;
	printk("my_irq_handler_1(%d, %p)\n", irq, devid);
	value = gpio_get_value(button->gpio);	
	value ^= button->active_low;
	input_report_key( my_input, button->code, value);
	if( value == 1 )
		printk("SW1 Pressed  Event !!\n");
	else
		printk("SW1 Released Event !!\n");
	return IRQ_HANDLED;
}

irqreturn_t my_irq_handler_2(int irq, void *devid)
{
	int value;
	printk("my_irq_handler_2(%d, %p)\n", irq, devid);
	value = gpio_get_value(GPIO_SW_2);	
	value ^= 1;

	input_report_key( my_input, GPIO_SW_2, value);
	if( value == 1 )
	{
		input_sync( my_input );
		printk("SW2 Pressed  Event !!\n");
	}
	else
		printk("SW2 Released Event !!\n");
	return IRQ_HANDLED;
}


static int my_keys_probe(struct platform_device *pdev)
{
	int ret;
	unsigned long flags = 3;
	printk("my_keys_probe(%p)\n", pdev);

	if( pdata == 0 )
		pdata = pdev->dev.platform_data;
	if( button == 0 )
		button = pdata->buttons;
	printk("code=%d, gpio=%d, active_low=%d\n", 
			button->code, button->gpio, button->active_low);

	irq_1 = gpio_to_irq(button->gpio);
	irq_2 = gpio_to_irq(GPIO_SW_2);
    ret = request_irq(irq_1, my_irq_handler_1, flags, "MY SW1 INT", 0);
    ret = request_irq(irq_2, my_irq_handler_2, flags, "MY SW2 INT", 0);
	my_input = input_allocate_device();
	__set_bit( EV_KEY, my_input->evbit);
	__set_bit( button->code, my_input->keybit);
	__set_bit( GPIO_SW_2, my_input->keybit);
	ret = input_register_device(my_input);
	gpio_direction_input(button->gpio);
	gpio_direction_input(GPIO_SW_2);
	return 0;
}

static int my_keys_remove(struct platform_device *pdev)
{
	printk("my_keys_remove()\n");
	free_irq(irq_1,0);
	free_irq(irq_2,0);
	input_unregister_device(my_input);
	input_free_device(my_input);
	pdata=0;
	button=0;
	return 0;
}

static const struct of_device_id my_keys_of_match[] = {
	{ .compatible = "my-keys", },
	{ },
};
MODULE_DEVICE_TABLE(of, my_keys_of_match);

static struct platform_driver my_keys_device_driver = {
	.probe      = my_keys_probe,
	.remove     = my_keys_remove,
	.driver     = {
		.name   = "my-keys",
		.of_match_table = of_match_ptr(my_keys_of_match),
	}
};

int my_init(void)
{
	printk("my_init()\n");
	platform_driver_register(&my_keys_device_driver);
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
	platform_driver_unregister(&my_keys_device_driver);
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
#endif
