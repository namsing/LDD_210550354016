#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>

#define NAME MyCharDyn

int NAME_open(struct inode *inode, struct file *filp);
int NAME_release(struct inode *inode, struct file *filp);
//ssize_t NAME_read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp);
//ssize_t NAME_write(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp);
struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = NAME_open,
//	.read = NAME_read,
//	.write = NAME_write,
	.release = NAME_release,
};

struct cdev *my_cdev;


static int __init chardev_init(void)
{
	int result;
	int MAJOR,MINOR;
	dev_t Mydev;
	result = alloc_chrdev_region(&Mydev,0,1,"MyCharDyn");
	if(result<0)
	{
		printk("Error allocating device number\n");
		return(-1);
	}else
	{
		printk("successfully allocated device number\n");
	}
	MAJOR = MAJOR(Mydev);
	MINOR = MINOR(Mydev);
	printk("\nThe major number is %d, and minor number  is %d",MAJOR,MINOR);
	result = register_chrdev_region(Mydev,1,"MyCharDyn");
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
	alloc_chrdev_region(&Mydev,0,1,"MyCharDyn");
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


module_init(chardev_init);
module_exit(chardev_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("NAMRATHA");
MODULE_DESCRIPTION("A Simple hello program");

