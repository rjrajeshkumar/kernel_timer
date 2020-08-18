#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rajesh");
MODULE_DESCRIPTION("Timer example");
MODULE_VERSION("0.01");

//Timer interval for 10 sec
int g_time_interval = 10000;
struct timer_list g_timer;
 
void timerhandler(struct timer_list *arg)
{
    /*Restarting the timer...*/
    mod_timer(arg, jiffies + msecs_to_jiffies(g_time_interval));
 
    printk(KERN_INFO "Timer Handler invoked.\n");
}
 
static int __init drv_init(void)
{
    printk(KERN_INFO "Driver Init called.\n");
 
    /*Starting the timer.*/
    timer_setup(&g_timer, timerhandler, 0);
    mod_timer( &g_timer, jiffies + msecs_to_jiffies(g_time_interval));
 
    return 0;
}
 
static void __exit drv_exit(void)
{
    del_timer(&g_timer);
    printk(KERN_INFO "Driver exit called.\n");
}
 
module_init(drv_init);
module_exit(drv_exit);

