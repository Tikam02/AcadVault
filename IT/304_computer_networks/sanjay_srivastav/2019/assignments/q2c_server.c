#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FNAME file1
#define PORT 8010
#define BUFSIZE 128
#define LISTENQ 5

typedef struct
{
    int sock;
    struct sockaddr address;
    int addr_len;
} connection_t;

void *process(void *ptr)
{
    char buf[BUFSIZE], fname[50];
    int connfd, fd, size, n;
    connection_t *conn;
    struct stat stat_buf;

    if (!ptr)
        pthread_exit(0);
    conn = (connection_t *)ptr;
    printf("Handling connection request\n");
    recv(conn->sock, fname, 50, 0);
    printf("File name is %s :  ", fname);

    fd = open(fname, O_RDONLY, S_IRUSR);
    fstat(fd, &stat_buf);
    size = stat_buf.st_size;

    printf(" size is %d\n", size);

    printf("\nopened file\n");
    while ((n = read(fd, buf, BUFSIZE - 1)) > 0)
    {
        buf[n] = '\0';
        printf("%s\n", buf);
        write(connfd, buf, n);
    }
    printf("file transfer completed \n");
    close(connfd);
    close(fd);
    close(conn->sock);
    free(conn);
    pthread_exit(0);
}

int main(int argc, char **argv)
{
    int sock = -1;
    struct sockaddr_in address;
    int port;
    connection_t *connection;
    pthread_t thread;

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

    while (1)
    {
        /* accept incoming connections */
        connection = (connection_t *)malloc(sizeof(connection_t));
        connection->sock = accept(sock, &connection->address, &connection->addr_len);
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

    return 0;
}