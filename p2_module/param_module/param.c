#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("NAMRATHA");

static int var = 12;

module_param(var, int, S_IRUGO);
static int param_init(void)
{

	printk("hello world\n");
	printk("value of integer is : %d\n ",var);
	return 0;

}
static void param_cleanup(void)
{
	printk("program ended\n");

}

module_init(param_init);
module_exit(param_cleanup);
