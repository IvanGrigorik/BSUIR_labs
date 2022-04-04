#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <malloc.h>

pthread_mutex_t mutex;

char string[][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};

void *routine(void *arg) {

    int index = *(int *) arg;

    while (1) {
        pthread_mutex_lock(&mutex);

        for (int i = 0; string[index][i] != '\0'; i++) {
            putchar(string[index][i]);
        }
        printf("\n");
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }

}

int main() {
    pthread_mutex_init(&mutex, NULL);

    pthread_t th[10];
    for (int i = 0; i < 10; i++) {
        int *index = malloc(sizeof(int));
        *index = i;
        if (pthread_create(&th[i], NULL, routine, index) != 0) {
            perror("Failed: ");
        }
    }

    char c;

    while (1) {
        c = getchar();
        if (c == 'q') {
            for (int i = 0; i < 10; i++) {
                pthread_cancel(th[i]);
            }
            break;
        }
    }

    for (int i = 0; i < 10; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed: ");
        }
    }

    pthread_mutex_destroy(&mutex);

    printf("\n");
    return 0;
}