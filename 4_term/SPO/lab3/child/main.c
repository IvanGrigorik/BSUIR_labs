#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

int main(int argc, char *argv[]) {

    printf(ANSI_COLOR_YELLOW);

    if (argc != 2) {
        perror("Wrong argc value");
        exit(1);
    }

    printf("Child name: %s\n", argv[0]);
    printf("PID: %d\n", getpid());
    printf("PPID: %d\n", getppid());

    FILE *env_names = fopen(argv[1], "r");

    const int MAX_PATH_SIZE = 256;
    char buffer[MAX_PATH_SIZE];

    while (fgets(buffer, MAX_PATH_SIZE, env_names) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';

        char *env_value = getenv(buffer);

        if (env_value) {
            printf("%s = %s\n", buffer, env_value);
        }
    }
    printf(ANSI_COLOR_RESET);
    fclose(env_names);

    exit(0);
}
