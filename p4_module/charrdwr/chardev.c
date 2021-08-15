#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>

#define NAME MyDevice

int NAME_open(struct inode *inode, struct file *filp);
int NAME_release(struct inode *inode, struct file *filp);
ssize_t NAME_read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp);
ssize_t NAME_write(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp);
struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = NAME_open,
	.read = NAME_read,
	.write = NAME_write,
	.release = NAME_release,
};

struct cdev *my_cdev;


static int __init chardev_init(void)
{
	int result;
	int MAJOR,MINOR;
	dev_t Mydev;
	Mydev = MKDEV(256,0);
	MAJOR = MAJOR(Mydev);
	MINOR = MINOR(Mydev);
	printk("\nThe major is %d, and minor is %d",MAJOR,MINOR);
	result = register_chrdev_region(Mydev,1,"MyDevice");
	if(result<0)
	{
		printk("\nError allocation region");
		return(-1);
	}
	my_cdev = cdev_alloc();
	my_cdev->ops = &fops;

	result = cdev_add(my_cdev,Mydev,1);
	if(result<0)
	{
		printk("\nerror");
		unregister_chrdev_region(Mydev,1);
		return(-1);
	}
	return 0;
}


void __exit chardev_exit(void)
{
	dev_t Mydev;
	int MAJOR, MINOR;
	Mydev = MKDEV(256,0);
	MAJOR = MAJOR(Mydev);
	MINOR = MINOR(Mydev);
	printk("\nThe major is %d, and minor is %d",MAJOR,MINOR);
	unregister_chrdev_region(Mydev,1);
	cdev_del(my_cdev);
	printk("\nUnregistered");
	
	
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

ssize_t NAME_read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp)
{
	char Kbuff[100] = "This is the data sent to device";
	ssize_t ret;
	unsigned long remaining;
	printk("\nread command called :");
	remaining = copy_to_user((char *)Ubuff,(char *)Kbuff,count);

	if(remaining == 0)
	{
		printk("\ndata succesfully copied");
		return count;
	}
	else if(remaining>0)
	{
		printk("data still remaining to be read");
		return (count - remaining);
	}
	else
	{
		printk("\n error reading data\n");
		ret = -EFAULT;
		return ret;
	}
	return 0;
}

ssize_t NAME_write(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp)
{
	char Kbuff[100];
	unsigned long remaining;
	ssize_t ret;
	printk("\nwriting data: \n");
	remaining = copy_from_user((char *)Kbuff,(char *)Ubuff,count);
	if(remaining == 0)
	{
		printk("data successfully read from user : %s",Ubuff);
		return count;
	}
	else if(remaining>0)
	{
		printk("data partially read from user : %s",Kbuff);
		return (count-remaining);
	}
	else
	{
		printk("error writing data\n");
		ret = -EFAULT;
		return ret;
	}
	
	return 0;
}

module_init(chardev_init);
module_exit(chardev_exit);





