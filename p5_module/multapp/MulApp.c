#include<stdio.h>
#include<sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
	int fd,result;
	int args[2] = {2,3};
	int result;
	fd = open("/dev/mulDev",O_RDWR,0777);
	if(fd<0)
	{
		printf("error opening driver\n");
		exit(1);
	}
	
	
	write(fd,args,sizeof(args));
	read(fd,&result,sizeof(int));
	printf("result of mul is %d\n",result);
	close(fd);
}
