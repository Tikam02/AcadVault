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
	int fd, n, size,count=0;
	long int size1,size2;
	char buf[BUFSIZE], fname[50];

	int port;
	int sock = -1;
	struct sockaddr_in address;
	struct hostent * host;
	int len;
	
	/* checking commandline parameter */
	if (argc != 3)
	{
		printf("usage: %s hostname port text\n", argv[0]);
		return -1;
	}

	/* obtain port number */
	if (sscanf(argv[2], "%d", &port) <= 0)
	{
		fprintf(stderr, "%s: error: wrong parameter: port\n", argv[0]);
		return -2;
	}

	/* create socket */
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock <= 0)
	{
		fprintf(stderr, "%s: error: cannot create socket\n", argv[0]);
		return -3;
	}

	/* connect to server */
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	host = gethostbyname(argv[1]);
	if (!host)
	{
		fprintf(stderr, "%s: error: unknown host %s\n", argv[0], argv[1]);
		return -4;
	}
	memcpy(&address.sin_addr, host->h_addr_list[0], host->h_length);
	if (connect(sock, (struct sockaddr *)&address, sizeof(address)))
	{
		fprintf(stderr, "%s: error: cannot connect to host %s\n", argv[0], argv[1]);
		return -5;
	}

	printf("Enter the name of the file u want to receive : ");
	scanf("%s",fname);
	send(sock,fname,sizeof(fname),0);

		
	//read(sockfd, size1, sizeof(size1));
	
	//printf("Size of the File is : %d ",size1);
			
	fd=open("NewFile",O_WRONLY|O_CREAT,S_IRWXU);		
	while ( (n = read(sock, buf, BUFSIZE-1)) > 0)
	{
		buf[n] = '\0';
		printf("%s\n",buf);	
		write(fd,buf,n);
		if( n < BUFSIZE-2)
			break;
	}
	
	printf("file receiving completed \n");
	close(sock);
	close(fd);
	exit(0);
}
