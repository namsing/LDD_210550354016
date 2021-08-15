#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>

#define NAME Mydevice

int NAME_open(struct inode *inode, struct file *filp);
int NAME_release(struct inode *inode, struct file *filp);
ssize_t Read_add(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp);
ssize_t Read_sub(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp);
ssize_t Read_mul(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp);
ssize_t Read_div(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp);
ssize_t Write_add(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp);
ssize_t Write_sub(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp);
ssize_t Write_mul(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp);
ssize_t Write_div(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp);

struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = NAME_open,
	.release = NAME_release,
};

struct cdev *my_cdev;


static int __init chardev_init(void)
{
	int result1,result2,result3,result4;
	int major,minor;
	dev_t Mydev,SubDev,MulDev,DivDev;
	Mydev = MKDEV(258,0);
	//SubDev = MKDEV(258,1);
	//MulDev = MKDEV(258,2);
	//DivDev = MKDEV(258,3);
	result = register_chrdev_region(Mydev,4,"Mydev");
//	result2 = register_chrdev_region(SubDev,1,"SubDev");
//	result3 = register_chrdev_region(MulDev,1,"MulDev");
//	result4 = register_chrdev_region(DivDev,1,"DivDev");
	if(result<0)
	{
		printk("\nError allocation region");
		return(-1);
	}
	my_cdev = cdev_alloc();
	my_cdev->ops = &fops;

	result = cdev_add(my_cdev,Mydev,4);
	if(result<0)
	{
		printk("\nerror");
		unregister_chrdev_region(Mydev,4);
		return(-1);
	}
	return 0;
}


void __exit chardev_exit(void)
{
	dev_t Mydev;
	int MAJOR, MINOR;
	Mydev = MKDEV(258,0);
	MAJOR = MAJOR(Mydev);
	MINOR = MINOR(Mydev);
	printk("\nThe major is %d, and minor is %d",MAJOR,MINOR);
	unregister_chrdev_region(Mydev,4);
	cdev_del(my_cdev);
	printk("\nUnregistered");
	
	
}

int NAME_open(struct inode *inode, struct file *filp)
{
	printk("\nThis is an open call");
	int minor;
	minor = MINOR(Mydev);
	switch(minor)
	{
		case 0:
			fops.read = Read_add;
			fops.write = Write_add;
			break;
		case 1:
			fops.read = Read_sub;
			fops.write= Write_sub;
			break;
		case 2:
			fops.read = Read_mul;
			fops.Write = Write_mul;
			break;
		case 3:
			fops.read = read_div;
			fops.write = Write_div;
			break;
	}

	return 0;
}


int NAME_release(struct inode *inode, struct file *filp)
{
	printk("\nThis is a close call");
	return 0;
}

ssize_t Read_add(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp)
{
	char Kbuff[100] = "This is the data sent to device";
	ssize_t ret;
	unsigned long remaining
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





