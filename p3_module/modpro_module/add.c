#include<linux/init.h>
#include<linux/module.h>
#include <linux/moduleparam.h>


MODULE_LICENSE("GPL");

int HelloWorld_type = 1;


static int hello_init(void)
{
	printk("Hello world\n");
	return 0;
	

}

static int HelloWorld_add(int a,int b)
{
	return (a+b);
}
EXPORT_SYMBOL_GPL(HelloWorld_add);

static void hello_cleanup(void)
{
	printk("Goodbye\n");
}

module_init(hello_init);
module_exit(hello_cleanup);




