#include "functions/functions.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char *argv[], char *envp[]) {
    show_env(environ);

    char env_file_path[] = "/home/sifi/BSUiR_labs/4_term/SPO/lab3/env";
    char **child_environment = get_child_env(env_file_path);

    int choice;
    int child_amount = 0;

    while ((choice = getchar()) != 'q') {

        // If unusual choice - go to cycle start
        if (choice != '+' && choice != '*' && choice != '&') {
            continue;
        }

        // Create child path, depending on the choice
        char *child_path;
        switch (choice) {
            case '+': {
                child_path = getenv("CHILD_PATH");
                break;
            }

            case '*': {
                child_path = get_child_path(envp);
                break;
            }

            case '&': {
                child_path = get_child_path(environ);
                break;
            }
        }

        // Create new child name
        char child_name[9];
        if(child_amount >= 100){
            break;
        }
        sprintf(child_name, "child_%d", child_amount++);

        // Create arguments, which we will transfer to child
        char *const child_args[] = {child_name, env_file_path, NULL};

        // Create new proc
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
        } else if (pid > 0) {
            // This is parent process
            int status;
            wait(&status);

            if (WEXITSTATUS(status) != 0) {
                perror("Child process violated");
            }
        }
        if (pid == 0) {
            // This is child process
            execve(child_path, child_args, child_environment);
        }

        printf(ANSI_COLOR_RESET);
    }

    exit(EXIT_SUCCESS);
}