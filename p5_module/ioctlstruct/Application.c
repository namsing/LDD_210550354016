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


struct sendat
{
	int int_1;
	int int_2;
	char char_send;
};

int main()
{
	int fd,result;
	struct sendat myStruct = {1,2,'c'};
	fd = open("/dev/MyIOCTLstruct",O_RDWR,0777);
	if(fd<0)
	{
		printf("error opening driver\n");
		exit(1);
	}

		
	
	result = ioctl(fd,WRT_SEND,&myStruct);
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
