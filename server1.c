#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define PERMS 0666

char fname[259];

int main()
{
int readfd,writefd,fd;z
ssize_t n;
char buff[512];

if(mkfifo(FIFO1,PERMS)<0)
	printf("Can't Create FIFO Files\n");
if(mkfifo(FIFO2,PERMS)<0)
	printf("Can't Create FIFO Files\n");
	
printf("Waiting for connection Request..\n");

readfd=open(FIFO1,O_RDONLY,0);
writefd=open(FIFO2,O_WRONLY,0);

printf("Connection Established..\n");
read(readfd,fname,255);
printf("Client has requested file %s\n",fname);

if((fd=open(fname,O_RDWR))<0)
{
strcpy(buff,"File does not exist..\n");
write(writefd,buff,strlen(buff));
}
else
{
while((n=read(fd,buff,512))>0)
	write(writefd,buff,n);
}
	
close(readfd);
unlink(FIFO1);
close(writefd);
unlink(FIFO2);
}
