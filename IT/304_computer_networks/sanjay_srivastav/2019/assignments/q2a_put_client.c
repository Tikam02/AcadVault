#include<sys/ioctl.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<net/if_arp.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include <stdio.h>

#define FNAME file1
#define PORT 8010
#define BUFSIZE 128

int main(int argc, char **argv)
{
	int sockfd, fd, n, size,count=0;
	long int size1,size2;
	char buf[BUFSIZE], fname[50];
	struct sockaddr_in servaddr;
    struct stat stat_buf;

    if (argc != 2) { 
	printf("Usage: %s server_address", argv[0]); 
	exit(1);
	}

	printf("11\n");
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		exit(1);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(PORT);	
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		exit(1);

	printf("22\n");

	if (connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0)
		exit(1);
	printf("connection established\n");

	printf("Enter the name of the file u want to send : ");
	scanf("%s",fname);
    printf("Sending File %s :  ", fname);

    fd = open(fname, O_RDONLY, S_IRUSR);
    fstat(fd, &stat_buf);
    size = stat_buf.st_size;

    printf(" size is %d\n", size);
    while ( (n = read(fd, buf, BUFSIZE-1)) > 0)
	{
		buf[n] = '\0';
		printf("%s\n",buf);	
		write(sockfd,buf,n);
		if( n < BUFSIZE-2)
			break;
	}
	
	printf("file transfer completed \n");
	close(sockfd);
	close(fd);
	exit(0);
}
