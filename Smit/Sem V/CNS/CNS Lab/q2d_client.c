#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <net/if_arp.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define FNAME file1
#define BUFSIZE 128

int main(int argc, char **argv)
{
    int sockfd = -1;
    int port;
    struct sockaddr_in address;
    struct hostent *host;
    long int size1, size2;
    char buf[BUFSIZE] = {'\0'}, fname[50];
    struct hostent *hostname;
    int n, fd;
    if (argc != 3)
    {
        printf("usage is : %s serverIPaddress port", argv[0]);
        exit(1);
    }

    if (sscanf(argv[2], "%d", &port) <= 0)
    {
        fprintf(stderr, "%s: error: wrong parameter: port\n", argv[0]);
        return -2;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        fprintf(stderr, "%s: error: cannot create socket\n", argv[0]);
        return -3;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    hostname = gethostbyname(argv[1]);
    //DNS lookup
    if (!hostname)
    {
        fprintf(stderr, "%s: error: unknown host %s\n", argv[0], argv[1]);
        return -4;
    }
    memcpy(&address.sin_addr, hostname->h_addr_list[0], hostname->h_length);
    if (connect(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        fprintf(stderr, "%s: error: cannot connect to host %s\n", argv[0], argv[1]);
        return -5;
    }
    else
    {
        printf("connection established\n");
    }

    printf("Enter the name of the file u want to modify : ");
    scanf("%s", fname);
    send(sockfd, fname, sizeof(fname), 0);
    //fd=open(fname,O_WRONLY|O_CREAT,S_IRWXU);
    printf("please enter what is to be written in file\n");
    scanf("%s", buf);

    n = write(sockfd, buf, sizeof(buf) / sizeof(buf[0]));
    if (n < 0)
    {
        fprintf(stderr, "ERROR writing to socket");
        return -6;
    }
    printf("applied modification");
    close(sockfd);
    exit(0);
}