#include <linux/module.h>
#include <net/sock.h>
#include <linux/netlink.h>
#include <linux/sched.h>
#include <linux/jiffies.h>
#include <linux/kthread.h>

#define MAX_PAYLOAD 1024
#define NETLINK_MESSAGE  "Hello User!!"
#define NL_EXAMPLE 19
#define NL_GROUP 1

#define MSG_INTERVAL_SEC 3

#define seconds_to_jiffies(sec) (cputime_to_jiffies(secs_to_cputime(sec)))

static struct sock *nl_sk = NULL;
static struct task_struct *sender_thread = NULL;

static int my_sender_thread (void *data){
	struct sk_buff *skb = NULL;    
	struct nlmsghdr *nlh; 
	do {
		skb = alloc_skb (NLMSG_SPACE (MAX_PAYLOAD), GFP_KERNEL); 
		nlh = (struct nlmsghdr *)skb_put (skb, NLMSG_SPACE (MAX_PAYLOAD));  
		nlh->nlmsg_len = NLMSG_SPACE (MAX_PAYLOAD);
		nlh->nlmsg_pid = 0;
		nlh->nlmsg_flags = 0;
		strcpy (NLMSG_DATA (nlh), NETLINK_MESSAGE);
		NETLINK_CB (skb).dst_group = NL_GROUP;
		netlink_broadcast (nl_sk, skb, 0, NL_GROUP, GFP_KERNEL); 
		printk (KERN_INFO "my_sender_thread sent a message at jiffies=%ld\n", jiffies);
		set_current_state (TASK_INTERRUPTIBLE); 
		schedule_timeout (seconds_to_jiffies (MSG_INTERVAL_SEC)); 
	} while (!kthread_should_stop ());   
	return 0;
}
static int  my_init (void)
{
	nl_sk = netlink_kernel_create (&init_net, NL_EXAMPLE, NULL);  
	if (nl_sk == NULL)
		return -1;
	sender_thread = kthread_run (my_sender_thread,
			NULL, "lab2_nl_sender_thread"); 
	if (IS_ERR (sender_thread)) {
		printk (KERN_INFO "Error %ld createing thread\n",
				PTR_ERR (sender_thread));
		sock_release (nl_sk->sk_socket);
		return -1;
	}
	printk (KERN_INFO "Adding netlink testing module\n");
	return 0;
}
static void  my_exit (void)
{
	printk (KERN_INFO "Removing netlink testing module\n");
	kthread_stop (sender_thread);   
	sock_release (nl_sk->sk_socket);  
}

module_exit (my_exit);
module_init (my_init);

MODULE_LICENSE ("GPL");

