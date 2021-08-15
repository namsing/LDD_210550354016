#include<stdio.h>
#include<sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <linux/ioctl.h>
#include <asm/ioctl.h>
#include <sys/ioctl.h>
#include "ioctl.h"

int main()
{
	int fd,result;
	int args[2] = {2,3};
	char Ubuff[] = "operation sent to IOCTL";
	char Kbuff[100],ch;
	fd = open("/dev/MyIOCTL",O_RDWR,0777);
	if(fd<0)
	{
		printf("error opening driver\n");
		exit(1);
	}
	printf("enter the operation to be performed : ");
	scanf("%c",&ch);


	switch(ch)
	{
		case '+':
			ioctl(fd,ADD,args);
			break;
		case '-':
			ioctl(fd,SUB,args);
			break;
		case '*':
			ioctl(fd,MUL,args);
			break;
		case '/':
			ioctl(fd,DIV,args);
			break;

	}
	if(result<0)
	{
		printf("IOCTL Error\n");
		return(-1);
	}
	
	//write(fd,Ubuff,sizeof(Ubuff));
	//read(fd,Kbuff,50);
	//printf("%s\n",Kbuff);
	close(fd);
}
