#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <net/if_arp.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <netinet/in.h>

#define FNAME file1
#define BUFSIZE 128

int main(int argc, char **argv)
{
    //-------------------------------------------------------------------
    int sockfd, fd, n, size, count = 0;
    long int size1, size2;
    char buf[BUFSIZE], fname[50];
    struct sockaddr_in servaddr;
    int port;

    if (argc != 3)
    {
        printf("Usage: %s server_address port", argv[0]);
        exit(1);
    } 
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        exit(1);

    if (sscanf(argv[2], "%d", &port) <= 0)
    {
        fprintf(stderr, "%s: error: wrong parameter: port\n", argv[0]);
        return -2;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
        exit(1);

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        exit(1);
    printf("connection established\n");

    printf("Enter the name of the file u want to receive : ");
    scanf("%s", fname);
    send(sockfd, fname, sizeof(fname), 0);

    fd = open("NewFile", O_WRONLY | O_CREAT, S_IRWXU);
    while ((n = read(sockfd, buf, BUFSIZE - 1)) > 0)
    {
        buf[n] = '\0';
        printf("%s\n", buf);
        write(fd, buf, n);
        if (n < BUFSIZE - 2)
            break;
    }

    printf("file receiving completed \n");
    close(sockfd);
    close(fd);
    exit(0);
}