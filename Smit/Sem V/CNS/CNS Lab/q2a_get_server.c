
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include<stdlib.h>

#define FNAME file1
#define PORT 8010
#define BUFSIZE 128
#define LISTENQ 5

int main(int argc, char **argv)
{
	int	listenfd, connfd, fd, pid, n, size;
//	FILE *fp;
	struct sockaddr_in servaddr;
	char buf[BUFSIZE],fname[50];

	struct stat stat_buf; 	
	

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(PORT);	

	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	listen(listenfd, LISTENQ);
		printf("listening\n");

	for ( ; ; ) 
	{
		connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);
		//pid=fork();
		//if(pid==0)
		//{
			printf("Handling connection request\n");
			recv(connfd,fname,50,0);
			printf("File name is %s :  ", fname);  

			fd=open(fname,O_RDONLY,S_IRUSR);
			fstat(fd, &stat_buf);
			size = stat_buf.st_size;
				
			printf(" size is %d\n", size); 
			
		//	write(connfd,size,sizeof(size));
		//	send(connfd,size,sizeof(size),0);                                                                       
		//	fd=open(fname,O_RDONLY,S_IRUSR);

			printf("\nopened file\n");
			while ( (n = read(fd, buf, BUFSIZE-1)) > 0) 
			{
				buf[n] = '\0';
				printf("%s\n",buf);
				write(connfd,buf,n);
			}
			printf("file transfer completed \n");
			close(connfd);
			close(fd);
			exit(1);
		//}
	}
}
