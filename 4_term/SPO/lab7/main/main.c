#include "functions.h"
#include <unistd.h>
#include <sys/wait.h>

#include "circle.h"

int main() {

    // Unlink semaphores, that I need in the future
    sem_unlink("producer_sem");
    sem_unlink("consumer_sem");
    sem_unlink("mutex_");

    sem_t *producer_sem = open_sem(producer_sem, "producer_sem", O_CREAT, 0664, 0);
    sem_t *consumer_sem = open_sem(consumer_sem, "consumer_sem", O_CREAT, 0664, 0);
    sem_t *mutex_ = open_sem(mutex_, "mutex_", O_CREAT, 0664, 1);

    pid_t *producer_pids = NULL, *consumer_pids = NULL;
    int producer_count = 0, consumer_count = 0;

    producer_pids = (int *) malloc(sizeof(int));
    consumer_pids = (int *) malloc(sizeof(int));

    int proj_id = 'l';
    key_t key = ftok("/home/sifi/BSUIR/BSUIR_labs/4_term/SPO/lab7/key", proj_id);

    circle_t *msg_circle = (circle_t *) malloc(sizeof(circle_t));
    int shm_id = shmget(key, sizeof(circle_t), 0664 | IPC_CREAT);
    msg_circle->cur_pos = 0;
    msg_circle = shmat(shm_id, NULL, 0);

    int choice;

    while (1) {
        choice = getchar();

        switch (choice) {


            case 'p': {
                pid_t pid = fork();
                if (pid == -1) {
                    perror("Fork error: ");
                    break;
                }
                if (pid != 0) {
                    // Parent process
                    ++producer_count;
                    producer_pids = realloc(producer_pids, producer_count * sizeof(pid_t));
                    producer_pids[producer_count - 1] = pid;
                    printf("\n%d - %d", producer_pids[producer_count - 1], pid);
                } else {
                    // Child process
                    execv("/home/sifi/BSUIR/BSUIR_labs/4_term/SPO/lab7/producer/cmake-build-debug/producer", NULL);
                    printf("New producer has been created\n");
                }

                break;
            }

            case 'c': {
                pid_t pid = fork();
                if (pid == -1) {
                    perror("Fork error: ");
                    break;
                }
                if (pid != 0) {
                    // Parent proc
                    ++consumer_count;
                    consumer_pids = realloc(consumer_pids, consumer_count * sizeof(pid_t));
                    consumer_pids[consumer_count - 1] = pid;
                } else {
                    execv("/home/sifi/BSUIR/BSUIR_labs/4_term/SPO/lab7/consumer/cmake-build-debug/consumer", NULL);
                    printf("New consumer has been created\n");
                }

                break;
            }

            case 'P': {
                printf("\n%d", producer_pids[producer_count - 1]);
                if(producer_count != 0) {
                    kill(producer_pids[producer_count - 1], SIGKILL);
                    --producer_count;
                    wait(NULL);
                }
                break;
            }

            case 'C': {
                if(consumer_count != 0) {
                    kill(consumer_pids[consumer_count - 1], SIGKILL);
                    --consumer_count;
                    wait(NULL);
                }
                break;

                break;
            }

            case 'q': {
                shmdt(msg_circle);
                sem_unlink("producer_sem");
                sem_unlink("consumer_sem");
                sem_unlink("mutex_");
                return 0;
            }
        }
    }

}
