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

#define GPIO_SW_1  23
#define GPIO_SW_2  24

#define MAX 64

typedef struct
{
	int code;
	int value;
} EVENT;

typedef struct
{
	EVENT queue[MAX];
	int rear;
	int front;
} QUEUE;

QUEUE queue;

void init( QUEUE *q )
{
	memset( q->queue, 0, sizeof q->queue);
	q->rear = q->front = 0;
}

void put( QUEUE *q, EVENT event )
{
	q->queue[q->rear] = event;
	q->rear = (q->rear+1)%MAX;
}

EVENT get(QUEUE *q)
{
	EVENT temp = q->queue[q->front];
	q->front = (q->front+1)%MAX;
	return temp;
}
int is_empty(QUEUE *q)
{
	return q->rear == q->front;
}

int is_full(QUEUE *q)
{
	return (q->rear+1)%MAX == q->front;
}


static int irq_1;
static int irq_2;
static DECLARE_WAIT_QUEUE_HEAD(my_wait);

irqreturn_t my_irq_handler_1(int irq, void *devid)
{
	int value;
	EVENT event;
	printk("my_irq_handler_1(%d, %p)\n", irq, devid);
	value = gpio_get_value(GPIO_SW_1);	
	value ^= 1;

	event.code  = GPIO_SW_1; 
	event.value = value;
	put( &queue, event );

	if( value == 1 )
		printk("SW1 Pressed  Event !!\n");
	else
		printk("SW1 Released Event !!\n");
	return IRQ_HANDLED;
}

irqreturn_t my_irq_handler_2(int irq, void *devid)
{
	int value;
	EVENT event;
	printk("my_irq_handler_2(%d, %p)\n", irq, devid);
	value = gpio_get_value(GPIO_SW_2);	
	value ^= 1;

	event.code  = GPIO_SW_2; 
	event.value = value;
	put( &queue, event );

	if( value == 1 )
	{
		printk("SW2 Pressed  Event !!\n");
		wake_up_interruptible(&my_wait); 
	}
	else
		printk("SW2 Released Event !!\n");
	return IRQ_HANDLED;
}
int my_open (struct inode *inode, struct file *filp)
{
	printk("my_open()\n");
	init(&queue);
	return 0;
}

int my_close (struct inode *inode, struct file *filp)
{
	printk("my_close()\n");
	return 0;
}

ssize_t my_read(struct file *filp, char __user *buff, size_t size, loff_t *off)
{
	int i, ret;
	EVENT event;
	printk("my_read()\n");
	if( is_empty( &queue ) )
	{
		if( filp->f_flags & O_NONBLOCK )
			return -EAGAIN;
	}
	if( !(filp->f_flags & O_NONBLOCK) )
		wait_event_interruptible( my_wait, !is_empty( &queue ) );

	for(i=0;  !is_empty( &queue ); i++ )
	{
		event = get(&queue);
		ret = copy_to_user( (EVENT*)buff+i, &event, sizeof(EVENT) );
	}
	return i*sizeof(EVENT);
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
	irq_1 = gpio_to_irq(GPIO_SW_1);
	irq_2 = gpio_to_irq(GPIO_SW_2);
    ret = request_irq(irq_1, my_irq_handler_1, flags, "MY SW1 INT", 0);
    ret = request_irq(irq_2, my_irq_handler_2, flags, "MY SW2 INT", 0);
	misc_register(&my_misc);
	gpio_direction_input(GPIO_SW_1);
	gpio_direction_input(GPIO_SW_2);
	return 0;
}

void my_exit(void)
{
	printk("my_exit()\n");
	free_irq(irq_1,0);
	free_irq(irq_2,0);
	misc_deregister(&my_misc);
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
#endif
