#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <signal.h>

void sigpipe_hand() {

    perror("Too many users!\n");
    exit(errno);
}

typedef struct clients {
    int client_socket;
    char client_name[100];
} users_t;

int main() {

    // Override SIGPIPE to show info
    signal(SIGPIPE, sigpipe_hand);

    int super_socket, addrlen, new_socket,  max_clients = 10, activity;
    int max_sd;
    struct sockaddr_in address;

    users_t users[10];

    char buffer[128];

    fd_set read_fd_sock;

    //greet message
    char *message = "Connected to server\n";

    //initialise all client_socket[] to 0 so not checked
    for (int i = 0; i < max_clients; i++) {
        users[i].client_socket = 0;
    }

    // 1) Create super_socket
    if ((super_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(errno);
    }
    // To reuse socket, if server crush
    if (setsockopt(super_socket, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
    }
    // Set socket family to internet
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;

    // Set port (can be changed)
    address.sin_port = htons(8000);

    // 2) Bind the socket to localhost port 8888
    if (bind(super_socket, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("Error in binding");
        exit(errno);
    }

    // 3) Define socket intended to receive to the connection.
    if (listen(super_socket, SOMAXCONN) < 0) {
        perror("Error in listening");
        exit(errno);
    }

    addrlen = sizeof(address);
    puts("Server started");

    while (1) {
        // Clear the socket set
        FD_ZERO(&read_fd_sock);

        // Add super_socket to set
        FD_SET(super_socket, &read_fd_sock);
        max_sd = super_socket;

        // Add client sockets to set
        for (int i = 0; i < max_clients; i++) {
            // If valid socket descriptor then add to read list
            if (users[i].client_socket > 0) {
                FD_SET(users[i].client_socket, &read_fd_sock);
            }

            // Highest file descriptor number, need it for the select function
            if (users[i].client_socket > max_sd) {
                max_sd = users[i].client_socket;
            }
        }

        // Wait for socket activity
        // timeout == NULL, so wait until we get message or program end
        activity = select(max_sd + 1, &read_fd_sock, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR)) {
            perror("Error in select");
            exit(errno);
        }

        // If something happened on the socket, then it's an incoming connection
        // 4) Accept incoming socket
        if (FD_ISSET(super_socket, &read_fd_sock)) {
            if ((new_socket = accept(super_socket, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            //send new connection greeting message
            if (send(new_socket, message, strlen(message), 0) != strlen(message)) {
                perror("send");
            }

            puts("New user connected.");
            printf("Socket fd is %d, ip is : %s, port: %d \n", new_socket,
                   inet_ntoa(address.sin_addr),
                   ntohs(address.sin_port));

            // Add new socket to array of sockets
            int i;
            for (i = 0; i < max_clients; i++) {
                //if position is empty
                if (users[i].client_socket == 0) {
                    users[i].client_socket = new_socket;
                    printf("Adding to list of sockets as %d\n", i);
                    break;
                }
            }

            memset(buffer, 0, sizeof(buffer));
            sprintf(buffer, "User %d connected\n", ntohs(address.sin_port));
            for (int j = 0; j < max_clients; j++) {
                // If valid socket descriptor then add to read list
                if (users[j].client_socket > 0
                    && users[j].client_socket != super_socket
                    && users[j].client_socket != users[i].client_socket) {
                    send(users[j].client_socket, buffer, strlen(buffer), 0);
                }
            }
        }

        // Else it's some IO operation on some other socket
        // 5) Read/write routine
        for (int i = 0; i < max_clients; i++) {
            // FD_ISSET() — check, is fd part of socket set
            if (FD_ISSET(users[i].client_socket, &read_fd_sock)) {

                // Check if it was for closing, and also read the incoming message
                if ((read(users[i].client_socket, buffer, 1024)) == 0) {

                    // Somebody disconnected , get his details and print
                    getpeername(users[i].client_socket, (struct sockaddr *) &address, (socklen_t *) &addrlen);
                    printf("Host disconnected, ip %s, port %d\n", inet_ntoa(address.sin_addr),
                           ntohs(address.sin_port));

                    // Info about disconnect
                    memset(buffer, 0, sizeof(buffer));
                    sprintf(buffer, "User %d disconnected\n", ntohs(address.sin_port));
                    for (int j = 0; j < max_clients; j++) {
                        // If valid socket descriptor then add to read list
                        if (users[j].client_socket > 0
                            && users[j].client_socket != super_socket
                            && users[j].client_socket != users[i].client_socket) {
                            send(users[j].client_socket, buffer, strlen(buffer), 0);
                        }
                    }

                    // Close the socket and mark as 0 in list for reuse
                    close(users[i].client_socket);
                    users[i].client_socket = 0;
                } else {
                    for (int j = 0; j < max_clients; j++) {
                        // If valid socket descriptor then add to read list
                        if (users[j].client_socket > 0 && users[j].client_socket != super_socket) {
                            send(users[j].client_socket, buffer, strlen(buffer), 0);
                        }
                    }
                    // Output info to the server
                    printf("%s\n", buffer);
                }
            }
        }
    }
}