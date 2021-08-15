#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include "ioctl.h"
#define NAME MyIOCTL
#define SUCCESS 1

int NAME_open(struct inode *inode, struct file *filp);
int NAME_release(struct inode *inode, struct file *filp);
long NAME_ioctl(struct file *filp,unsigned int cmd, unsigned long arg);


struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = NAME_open,
	.release = NAME_release,
	.unlocked_ioctl = NAME_ioctl,
};

struct cdev *my_cdev;


static int __init chardev_init(void)
{
	int result;
	int MAJOR,MINOR;
	dev_t Mydev;
	Mydev = MKDEV(255,0);
	MAJOR = MAJOR(Mydev);
	MINOR = MINOR(Mydev);
	printk("\nThe major number is %d, and minor number  is %d",MAJOR,MINOR);
	result = register_chrdev_region(Mydev,1,"MyIOCTL");
	if(result<0)
	{
		printk("\nError");
		return(-1);
	}
	my_cdev = cdev_alloc();
	my_cdev->ops = &fops;

	result = cdev_add(my_cdev,Mydev,1);
	if(result<0)
	{
		printk("\nerror obtaining region");
		unregister_chrdev_region(Mydev,1);
		return(-1);
	}
	return 0;
}


void __exit chardev_exit(void)
{
	dev_t Mydev;
	int MAJOR, MINOR;
	Mydev = MKDEV(255,0);
	MAJOR = MAJOR(Mydev);
	MINOR = MINOR(Mydev);
	printk("\nThe major number is %d, and minor number is %d",MAJOR,MINOR);
	unregister_chrdev_region(Mydev,1);
	cdev_del(my_cdev);
	printk("\nUnregistered");
	return;
	
}

int NAME_open(struct inode *inode, struct file *filp)
{
	printk("\nThis is an open call");
	return 0;
}


int NAME_release(struct inode *inode, struct file *filp)
{
	printk("\nThis is a close call");
	return 0;
}

long NAME_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
{
	int var1,var2;
	int UBuff[20];
	int res;
	int *p;
	ssize_t retval = SUCCESS;
	printk("IOCTL function : \n");
	p = UBuff;

	res = copy_from_user(UBuff,(int *)arg,2*sizeof(int));
	var1 = p[0];
	var2 = p[1];

	printk("var1 & var2 are: %d,%d\n",var1,var2);

	switch(cmd)
	{
		case ADD:
			printk("addition of the two numbers is : %d\n",var1+var2);
			break;
		case SUB:
			printk("subtraction of the two numbers is : %d\n",var1-var2);
			break;
		case MUL:
			printk("product of the two numbers is : %d\n",var1*var2);
			break;
		case DIV:
			printk("division of the two numbers is : %d\n",var1/var2);
			break;
	}
	return retval;
}


module_init(chardev_init);
module_exit(chardev_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("NAMRATHA");
MODULE_DESCRIPTION("A Simple hello program");

