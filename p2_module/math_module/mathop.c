#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/moduleparam.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("NAMRATHA");

static int var1 = 12;
static int var2 = 2;
static char* varstr = "a";

module_param(var1, int, S_IRUGO);
module_param(var2, int, S_IRUGO);
module_param(varstr, charp, S_IRUGO);


static int my_add(int a, int b)
{
	return a+b;
}

static int my_sub(int a, int b)
{
	return a-b;
}

static int my_mul(int a , int b)
{
	return a*b;
}
static int my_div(int a, int b)
{
	return a/b;
}


static int param_init(void)
{

	printk("hello world\n");
	printk("the string passes is : %s\n ",varstr);
	if(*varstr=='a')
	{
		printk("sum is %d\n",my_add(var1,var2));
	}
	else if(*varstr=='s')
	{
		printk("difference is %d\n",my_sub(var1,var2));
	}
	else if(*varstr=='m')
	{
		printk("product is %d\n",my_mul(var1,var2));

	}
	else if(*varstr=='d')
	{
		printk("quotient is %d\n",my_div(var1,var2));
	}
	return 0;

}
static void param_cleanup(void)
{
	printk("program ended\n");

}

module_init(param_init);
module_exit(param_cleanup);
