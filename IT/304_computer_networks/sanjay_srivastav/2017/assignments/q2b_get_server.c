
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include<stdlib.h>

#include <pthread.h>
#include <linux/in.h>
#include <unistd.h>

#define FNAME file1
#define PORT 8010
#define BUFSIZE 128
#define LISTENQ 5


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


typedef struct
{
	int sock;
	struct sockaddr address;
	int addr_len;
} connection_t;

void * process(void * ptr)
{
	char * buffer;
	int len;
	connection_t * conn;
	long addr = 0;
	char buf[BUFSIZE],fname[50];
	
	int fd, pid, n, size;
	
		struct stat stat_buf; 	

	if (!ptr) pthread_exit(0); 
	conn = (connection_t *)ptr;
	pthread_mutex_lock(&lock);
	printf("%d\n", conn->sock);
	/* read length of message */
	printf("Handling connection request\n");
	recv(conn->sock,fname,50,0);
	
	printf("File name is %s :  ", fname);  

	fd=open(fname,O_RDONLY,S_IRUSR);
	fstat(fd, &stat_buf);
	size = stat_buf.st_size;
		
	
	
//	write(connfd,size,sizeof(size));
//	send(connfd,size,sizeof(size),0);                                                                       
//	fd=open(fname,O_RDONLY,S_IRUSR);

	printf("\nopened file\n");
	while ( (n = read(fd, buf, BUFSIZE-1)) > 0) 
	{
		buf[n] = '\0';
		//printf("%s\n",buf);
		write(conn->sock,buf,n);
	}
	printf("file transfer completed \n");
	/* close socket and clean up */
	pthread_mutex_unlock(&lock);
	
	pthread_exit(0);
}


int main(int argc, char ** argv)
{
	int sock = -1,rc1;
	struct sockaddr_in address;
	int port;
	connection_t * connection;
	pthread_t tid[50];

	/* check for command line arguments */
	if (argc != 2)
	{
		fprintf(stderr, "usage: %s port\n", argv[0]);
		return -1;
	}

	/* obtain port number */
	if (sscanf(argv[1], "%d", &port) <= 0)
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

	/* bind socket to port */
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	if (bind(sock, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) < 0)
	{
		fprintf(stderr, "%s: error: cannot bind socket to port %d\n", argv[0], port);
		return -4;
	}

	/* listen on port */
	if (listen(sock, 5) < 0)
	{
		fprintf(stderr, "%s: error: cannot listen on port\n", argv[0]);
		return -5;
	}

	printf("%s: ready and listening\n", argv[0]);
	int i=0;
	while(1){
		
		connection = (connection_t *)malloc(sizeof(connection_t));
		connection->sock = accept(sock, &connection->address, &connection->addr_len);

		//for each client request creates a thread and assign the client request to it to process

	       //so the main thread can entertain next request

		if( pthread_create(&tid[i], NULL, process, (void *)connection) != 0 )

		   printf("Failed to create thread\n");

		if( i >= 50)

		{

		  i = 0;

		  while(i < 50)

		  {

		    pthread_join(tid[i++],NULL);

		  }

		  i = 0;

		}
			
			
	}
	close(connection->sock);
	
	return 0;
}
