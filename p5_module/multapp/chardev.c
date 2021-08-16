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

struct file_operations fops_add = 
{
	.owner = THIS_MODULE,
	.open = NAME_open,
	.release = NAME_release,
	.read = Read_add,
	.write = Write_add,
};

struct file_operations fops_sub =
{

	.owner = THIS_MODULE,
	.open = NAME_open,
	.release = NAME_release,
	.read = Read_sub,
	.write = Write_sub,
}
struct file_operations fops_mul = 
{

	.owner = THIS_MODULE,
	.open = NAME_open,
	.release = NAME_release,
	.read = Read_mul,
	.write = Write_mul,
}
struct file_operations fops_div = 
{

	.owner = THIS_MODULE,
	.open = NAME_open,
	.release = NAME_release,
	.read = Read_div,
	.write = Write_div,
}


struct cdev *addDev;
struct cdev *subDev;
struct cdev *mulDev;
struct cdev *divDev;

int result_add,result_sub,result_mul,result_div;


int result1,result2,result3,result4;
static int __init chardev_init(void)
{
	int major,minor;
	dev_t Adddev,SubDev,MulDev,DivDev;
	AddDev = MKDEV(258,0);
	SubDev = MKDEV(258,1);
	MulDev = MKDEV(258,2);
	DivDev = MKDEV(258,3);
	result1 = register_chrdev_region(AddDev,1,"Adddev");
	result2 = register_chrdev_region(SubDev,1,"SubDev");
	result3 = register_chrdev_region(MulDev,1,"MulDev");
	result4 = register_chrdev_region(DivDev,1,"DivDev");
	if(result1<0||result2<0||result3<0||result4<0)
	{
		printk("\nError allocation region");
		return(-1);
	}
	addDev = cdev_alloc();
	addDev->ops = &fops_add;


	subDev = cdev_alloc();
	subDev->ops = &fops_sub;

	mulDev = cdev_alloc();
	mulDev->ops = &fops_mul;

	divDev = cdev_alloc();
	divDev->ops = &fops_div;

	result1 = cdev_add(addDev,AddDev,1);
	result2 = cdev_add(subDev,SubDev,1);
	result3 = cdev_add(mulDev,MulDev,1);
	result4 = cdev_add(divDev,DivDev,1);
	if(result1<0||result2<0||result3<0||result4<0)
	{
		printk("\nerror");
		unregister_chrdev_region(Mydev,4);
		return(-1);
	}
	return 0;
}


void __exit chardev_exit(void)
{
	printk("\nUnregistered");
	cdev_del(addDev);	
	cdev_del(subDev);	
	cdev_del(mulDev);	
	cdev_del(divDev);	
	unregister_chrdev_region(AddDev,1);
	unregister_chrdev_region(SubDev,1);
	unregister_chrdev_region(MulDev,1);
	unregister_chrdev_region(DivDev,1);
	
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

ssize_t Read_add(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp)
{
	ssize_t ret;
	unsigned long remaining
	printk("\nread command called :");
	remaining = copy_to_user((char *)Ubuff,&result_add,count);

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




ssize_t Read_sub(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp)
{
	char Kbuff[100] = "This is the data sent to device";
	ssize_t ret;
	unsigned long remaining
	printk("\nread command called :");

	remaining = copy_to_user((char *)Ubuff,&result_sub,count);
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


ssize_t Read_mul(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp)
{
	char Kbuff[100] = "This is the data sent to device";
	ssize_t ret;
	unsigned long remaining
	printk("\nread command called :");

	remaining = copy_to_user((char *)Ubuff,&result_mul,count);
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


ssize_t Read_div(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp)
{
	char Kbuff[100] = "This is the data sent to device";
	ssize_t ret;
	unsigned long remaining
	printk("\nread command called :");

	remaining = copy_to_user((char *)Ubuff,&result_div,count);
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
ssize_t Write_add(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp)
{
	int Kbuff[2],result;
	unsigned long remaining;
	ssize_t ret;
	printk("\nwriting data: \n");
	remaining = copy_from_user((char *)Kbuff,(char *)Ubuff,count);
	if(remaining == 0)
	{
		printk("data successfully read from user : \n");
		result_add = (int)Kbuff[0]+(int)Kbuff[1];


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
ssize_t Write_sub(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp)
{
	char Kbuff[100];
	unsigned long remaining;
	ssize_t ret;
	printk("\nwriting data: \n");
	remaining = copy_from_user((char *)Kbuff,(char *)Ubuff,count);
	if(remaining == 0)
	{
		printk("data successfully read from user : \n");
		result_sub = (int)Kbuff[0]-(int)Kbuff[1];


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
ssize_t Write_mul(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp)
{
	char Kbuff[100];
	unsigned long remaining;
	ssize_t ret;
	printk("\nwriting data: \n");
	remaining = copy_from_user((char *)Kbuff,(char *)Ubuff,count);
	if(remaining == 0)
	{
		printk("data successfully read from user : \n");
		result_mul = (int)Kbuff[0]*(int)Kbuff[1];

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


ssize_t Write_div(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp)
{
	char Kbuff[100];
	unsigned long remaining;
	ssize_t ret;
	printk("\nwriting data: \n");
	remaining = copy_from_user((char *)Kbuff,(char *)Ubuff,count);
	if(remaining == 0)
	{
		printk("data successfully read from user : \n");
		result_div = (int)Kbuff[0]/(int)Kbuff[1];
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





