#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#define PORT 8010
#define BUFSIZE 128
#define LISTENQ 5

int main(int argc, char **argv)
{
	int	listenfd, connfd, fd, pid, n, n2, size;
	struct sockaddr_in servaddr;
	char buf[BUFSIZE],fname[50], *data;
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
        printf("Handling connection request\n");
        //-----------------------------------
        struct dirent *de; // Pointer for directory entry
        // opendir() returns a pointer of DIR type.
        DIR *dr = opendir(".");
        if (dr == NULL) // opendir returns NULL if couldn't open directory
        {
            printf("Could not open current directory");
            return 0;
        }
        fd = open("ListFile", O_RDWR | O_CREAT, S_IRWXU);
        while ((de = readdir(dr)) != NULL)
        {
            write(connfd, de->d_name, strlen(de->d_name));
        }
        closedir(dr);
        //-----------------------------------
        printf("List completed \n");
        close(connfd);
        close(fd);
        exit(1);
	}
}