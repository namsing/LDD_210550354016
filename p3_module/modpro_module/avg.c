#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include "header.h"

static int HelloWorld_add(int a,int b);

static int var1 = 2;
static int var2 = 3;

module_param(var1, int, S_IRUGO);
module_param(var2,int,S_IRUGO);

static int hello_init(void)
{
	printk("Hello world\n");
	printk("average of the two digits is %d\n",(HelloWorld_add(var1,var2))/2);
	return 0;

}

static void hello_cleanup(void)
{
	printk("Goodbye\n");
}

module_init(hello_init);
module_exit(hello_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("NAMRATHA");
MODULE_DESCRIPTION("A Simple hello world LKM");



