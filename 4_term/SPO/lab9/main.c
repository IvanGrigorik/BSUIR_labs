#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define __USE_GNU

#include <sys/mman.h>

typedef struct {
    char msg_text[128];
    size_t msg_size;
    int index;
} msg_t;

msg_t *map;
sem_t *sem;

_Noreturn void *listener_routine(__attribute__((unused)) void *args) {
    int temp_index = 0;

    while (1) {
        sem_wait(sem);
        if (map->index != temp_index) {

            printf("Message: %s\n", map->msg_text);
            temp_index = map->index;
        }
        sem_post(sem);
    }
}

int main() {

    sem = sem_open("lab9", O_CREAT | O_RDWR, 0777, 1);
    if (sem == SEM_FAILED) {
        perror("Semaphore open error");
        exit(EXIT_FAILURE);
    }

    int fd = open("/home/sifi/BSUIR/BSUIR_labs/4_term/SPO/lab9/shared_memory", O_RDWR);
    map = mmap(NULL, sizeof(msg_t), PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    if(map == MAP_FAILED){
        perror("mmap failed");
    }
    map->index = 0;
    close(fd);

    // Create new thread for listen from virtual memory
    pthread_t listener;
    pthread_create(&listener, NULL, listener_routine, NULL);

    char text[128];
    while (1) {

        fgets(text, 128, stdin);

        if (text[0] == 'q' && text[1] == '\n') {
            sem_unlink("lab9");
            exit(EXIT_SUCCESS);
        }

        sem_wait(sem);

        strcpy(map->msg_text, text);
        map->index++;

        sem_post(sem);
    }
}

// Открыть пару терминалов. Можно писать в каждый терминал, и потом каждый терминал будет выводить это сообщение
// Один поток слушает (смотрит, изменилось ли что-то в отображённой памяти). Второй пишет