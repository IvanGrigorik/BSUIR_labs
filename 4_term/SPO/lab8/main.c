#include "circle.h"

circle_t msg_circle;

sem_t producer_sem;
sem_t consumer_sem;
pthread_mutex_t mutex;

int hashing(char *str) {
    unsigned int hash = 0;

    char c;

    while (c = *str++) {
        hash += c;
    }

    return hash;
}

_Noreturn void *producer_routine(__attribute__((unused)) void *args) {

    int new_size;

    while (1) {
        sem_wait(&producer_sem);
        pthread_mutex_lock(&mutex);

        if (!msg_circle.message[msg_circle.head].is_filled) {
            printf(YELLOW "NEW MESSAGE NUMBER %d SENT" WHITE "\n", msg_circle.head);
            new_size = rand() % 80;
            for (int i = 0; i < new_size; i++) {
                msg_circle.message[msg_circle.head].data[i] = 49 + (rand() % 72);
            }
            msg_circle.message[msg_circle.head].size = new_size;
            msg_circle.message[msg_circle.head].is_filled = true;
            msg_circle.message[msg_circle.head].hash = hashing(msg_circle.message[msg_circle.head].data);
            msg_circle.added++;
            if (msg_circle.head == 9) {
                msg_circle.head = 0;
            } else {
                msg_circle.head++;
            }
        } else {
            printf(RED "Queue is full" WHITE "\n");
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&producer_sem);

        sleep(1);
    }
}


_Noreturn void *consumer_routine(__attribute__((unused)) void *arg) {
    char message_to_out[256];

    while (1) {
        sem_wait(&consumer_sem);
        pthread_mutex_lock(&mutex);

        if (msg_circle.message[msg_circle.tail].is_filled) {
            strcpy(message_to_out, msg_circle.message[msg_circle.tail].data);
            msg_circle.deleted++;
            printf(CYAN "Received message number %d: %s\n", msg_circle.deleted, message_to_out);
            printf("Message hash: %d\n", msg_circle.message[msg_circle.tail].hash);
            printf("Message size: %d" WHITE "\n", msg_circle.message[msg_circle.tail].size);
            msg_circle.message[msg_circle.tail].is_filled = false;

            if (msg_circle.tail == 9) {
                msg_circle.tail = 0;
            } else {
                msg_circle.tail++;
            }
            printf("\nStats:\nTotal added: %d\nTotal received: %d\n\n", msg_circle.added, msg_circle.deleted);
        } else {
            printf(RED "Queue is empty!" WHITE "\n");
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&consumer_sem);

        sleep(1);
    }
}


int main() {

    printf("Enter: \n");
    printf("'p' - create producer\n");
    printf("'c' - create consumer\n");
    printf("'P' - delete producer\n");
    printf("'C' - delete consumer\n");
    printf("'q' - quit\n");

    sem_init(&consumer_sem, 0, 1);
    sem_init(&producer_sem, 0, 1);
    pthread_mutex_init(&mutex, NULL);


    for (int i = 0; i < 10; i++) {
        msg_circle.message[i].is_filled = false;
    }

    msg_circle.head = 0;
    msg_circle.tail = 0;
    msg_circle.added = 0;
    msg_circle.deleted = 0;

    pthread_t producers[10];
    pthread_t consumers[10];
    int producer_count = 0, consumer_count = 0;

    int choice;
    while (1) {
        choice = getchar();

        switch (choice) {

            case 'p': {
                if (pthread_create(&producers[producer_count], NULL, producer_routine, NULL) != 0) {
                    perror("Failed in producer creation\n");
                }
                ++producer_count;
                break;
            }

            case 'c': {
                if (pthread_create(&consumers[consumer_count], NULL, consumer_routine, NULL) != 0) {
                    perror("Failed in producer creation\n");
                }
                ++consumer_count;
                break;
            }

            case 'P': {
                if (producer_count > 0) {
                    sem_wait(&producer_sem);
                    pthread_mutex_lock(&mutex);

                    pthread_cancel(producers[producer_count - 1]);

                    pthread_mutex_unlock(&mutex);
                    sem_post(&producer_sem);
                    --producer_count;
                }
                break;
            }

            case 'C': {
                if (consumer_count > 0) {
                    sem_wait(&consumer_sem);
                    pthread_mutex_lock(&mutex);

                    pthread_cancel(consumers[consumer_count - 1]);

                    pthread_mutex_unlock(&mutex);
                    sem_post(&consumer_sem);

                    --consumer_count;
                }
                break;
            }

            case 't': {
                break;
            }


            case 'q': {
                pthread_mutex_destroy(&mutex);
                sem_destroy(&producer_sem);
                sem_destroy(&consumer_sem);

                exit(EXIT_SUCCESS);
            }
        }
    }

}
