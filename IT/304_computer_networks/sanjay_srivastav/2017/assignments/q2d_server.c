#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/in.h>
#include <unistd.h>

#define LISTENQ 10
#define BUFSIZE 128
pthread_mutex_t lock;

typedef struct
{
    int sock;
    struct sockaddr address;
    int addr_len;
} connection_t;

void process(void *ptr)
{
    int fd, n, size;
    char fname[50];
    struct stat stat_buf;

    connection_t *conn;
    long addr = 0;

    if (!ptr)
        pthread_exit(0);
    conn = (connection_t *)ptr;

    addr = (long)((struct sockaddr_in *)&conn->address)->sin_addr.s_addr;
    char *buf = (char *)malloc((BUFSIZE) * sizeof(char));
    printf("Handling connection request\n");
    recv(conn->sock, fname, 50, 0);
    printf("File name is %s :  ", fname);

    pthread_mutex_lock(&lock);
    fd = open(fname, O_WRONLY | O_CREAT, S_IRWXU);

    printf("\nopened file\n");
    n = read(conn->sock, buf, BUFSIZE);
    if (n < 0)
    {
        printf("error in reading socket data!\n");
        pthread_exit(1);
    }
    int i = 0;
    while (buf[i] != '\0' && i < BUFSIZE - 1)
        i++;
    write(fd, buf, i--);

    close(fd);
    printf("file modification completed \n");
    pthread_mutex_unlock(&lock);
    close(conn->sock);
    free(conn);
    free(buf);
    pthread_exit(0);
}

int main(int argc, char **argv)
{

    int sockfd = -1;
    struct sockaddr_in address;
    int port;
    connection_t *connection;
    pthread_t thread;

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init has failed\n");
        return 1;
    }
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
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd <= 0)
    {
        fprintf(stderr, "%s: error: cannot create socket\n", argv[0]);
        return -3;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        fprintf(stderr, "%s: error: cannot bind socket to port %d\n", argv[0], port);
        return -4;
    }
    if (listen(sockfd, LISTENQ) < 0)
    {
        fprintf(stderr, "%s: error: cannot listen on port\n", argv[0]);
        return -5;
    }
    printf("%s: ready and listening\n", argv[0]);

    while (1)
    {
        connection = (connection_t *)malloc(sizeof(connection_t));
        connection->sock = accept(sockfd, &connection->address, &connection->addr_len);
        if (connection->sock <= 0)
        {
            free(connection);
        }
        else
        {
            /* start a new thread but do not wait for it */
            pthread_create(&thread, 0, process, (void *)connection);
            pthread_detach(thread);
        }
    }

    pthread_mutex_destroy(&lock);
    return 0;
}