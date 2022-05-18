#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>
#include <errno.h>

struct client_info {
    int fd;
    char *client_name;
};

#define IP 192.168.100.3

_Noreturn void *reader_routine(void *data) {

    char buffer[1024];
    char *name;
    int sock;
    struct client_info *send_s;
    send_s = (struct client_info *) data;
    sock = send_s->fd;

    while (1) {
        if((recv(sock, buffer, sizeof(buffer), 0)) == -1 ){
            perror("Error in receive");
            exit(errno);
        }
        printf("> %s\n", buffer);

        memset(buffer, 0, sizeof(buffer));
    }
}

_Noreturn void *writer_routine(void *sock_info) {

    char send_message[1024];
    char *message = malloc(1024 * sizeof(char));

    char *name;
    int sock;
    struct client_info *send_socket;
    send_socket = (struct client_info *) sock_info;
    sock = send_socket->fd;
    name = send_socket->client_name;

    while (1) {
        fgets(message, 1024, stdin);
        printf("Your message: %s\n", message);

        memset(send_message, 0, sizeof(send_message));
        strcpy(send_message, name);
        strcat(send_message, ": ");
        strcat(send_message, message);

        if ((send(sock, send_message, sizeof(send_message), 0)) == 0) {
            perror("Sending error: ");
        }
    }
}

int main() {

    int sock;
    struct sockaddr_in server_address;
    struct hostent *host;
    char name[20];

    printf("Enter nickname: ");
    scanf("%s", name);
    getchar();

    puts("Start server initializing...");

    // 1) Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error in socket creating");
        exit(1);
    }

    // Set socket family to internet
    server_address.sin_family = AF_INET;

    // Set ip (change in other computer)
    char ip[20] = {"192.168.100.3"};
    host = gethostbyname(ip);
    memcpy(&server_address.sin_addr, host->h_addr, host->h_length);

    // Set port (can be changed)
    server_address.sin_port = htons(8000);

    // 2) Request to connect
    puts("Connect to server...");
    if ((connect(sock, (struct sockaddr *) &server_address, sizeof(server_address))) != 0) {
        perror("Connection error");
        exit(0);
    }

    pthread_t send_th, write_th;
    struct client_info send;
    send.fd = sock;
    send.client_name = name;

    // Read
    pthread_create(&write_th, NULL, reader_routine, (void *) &send);
    // Write
    pthread_create(&send_th, NULL, writer_routine, (void *) &send);

    pthread_join(send_th, NULL);
    pthread_join(write_th, NULL);

    close(sock);
    return 0;
}