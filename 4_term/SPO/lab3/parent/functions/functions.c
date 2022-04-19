//
// Created by sifi on 04.03.2022.
//

#include "functions.h"

int sort_string(const void *str1, const void *str2) {
    char *const *pp1 = str1;
    char *const *pp2 = str2;
    return strcmp(*pp1, *pp2);
};

void show_env(char *env[]) {

    // Set color to magenta
    printf(ANSI_COLOR_CYAN);

    int env_start = 0, env_end = 0;
    while (env[env_end]) {
        env_end++;
    }

    qsort(env, env_end, sizeof(*env), sort_string);

    for (int i = 0; i < env_end; i++) {
        printf("%s\n", env[i]);
    }

    // Reset color
    printf(ANSI_COLOR_RESET);
}

char **get_child_env(char *env_file_path) {
    FILE *env_names = fopen(env_file_path, "r");
    if (!env_names) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char **env = malloc(sizeof(char *));

    const int MAX_PATH_SIZE = 256;
    char buffer[MAX_PATH_SIZE];

    int env_amount = 0;

    while (fgets(buffer, MAX_PATH_SIZE, env_names) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';

        char *env_value = getenv(buffer);
        if (env_value) {
            env[env_amount] = malloc((strlen(buffer) + strlen(env_value) + 2) * sizeof(char)); // +2 to '\n' and '='

            strcpy(env[env_amount], buffer);
            strcat(env[env_amount], "=");
            strcat(env[env_amount], env_value);

            env = realloc(env, (++env_amount + 1) * sizeof(char *));
        }
    }
    env[env_amount] = NULL;
    fclose(env_names);

    return env;
}

char* get_child_path(char** environments){
    for(; *environments; ++environments){
        if(!strncmp(*environments, "CHILD_PATH", strlen("CHILD_PATH"))){
            return *environments + strlen("CHILD_PATH=");
        }
    }

    return NULL;
}