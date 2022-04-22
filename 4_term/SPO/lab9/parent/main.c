#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>

int main() {
    int fd;

    char file_path[] = "/home/sifi/BSUIR/BSUIR_labs/4_term/SPO/lab9/shared_file";

    // Work with forks
    pid_t *pid_list = NULL;
    int pid_count = 0;

    // Work with messages
    char message[256];
    size_t msg_len;

    // Work with file-shared memory
    int *map_p;

    printf("Enter: \n");
    printf("'+' to create new process\n");
    printf("'-' to kill last process\n");
    printf("'q' to quit and kill all proc\n");
    printf("Any message to send it\n");

    while (1) {

        if ((fd = open(file_path, O_RDWR)) < 0) {
            perror("fd error");
        }

        fgets(message, 256, stdin);

        switch (message[0]) {

            case '+': {
                if (message[1] != '\n') {
                    goto default_line;
                }

                pid_t pid;
                pid = fork();

                if (pid < 0) {
                    perror("Fork error");
                } else if (pid != 0) {
                    // Parent process
                    pid_count++;
                    pid_list = (pid_t *) realloc(pid_list, pid_count * sizeof(pid_t));
                    pid_list[pid_count - 1] = pid;
                } else {
                    // Child process
                    printf("New consumer has been created\n");
                    char *const args[] = {file_path, NULL};
                    execv("/home/sifi/BSUIR/BSUIR_labs/4_term/SPO/lab9/child/cmake-build-debug/child",
                          args);
                }

                break;
            }

            case '-': {
                if (message[1] != '\n') {
                    goto default_line;
                }
                --pid_count;
                kill(pid_list[pid_count], SIGKILL);
                break;
            }

            case 'q': {
                if (message[1] != '\n') {
                    goto default_line;
                }

                for (int i = 0; i < pid_count; i++) {
                    kill(pid_list[i], SIGKILL);
                }
                return 0;
            }

            default_line:

            default: {
                truncate(file_path, 0);
                write(fd, message, strlen(message));
                map_p = mmap(0, strlen(message) + 1, PROT_WRITE | PROT_READ,
                             MAP_SHARED, fd, 0);
                munmap(map_p, strlen(message) + 1);

                for (int i = 0; i < pid_count; i++) {
                    kill(pid_list[i], SIGUSR1);
                }

                break;
            }
        }
        close(fd);
    }
}
