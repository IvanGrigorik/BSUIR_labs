#include "../functions.h"
#include "../circle.h"

int main() {
    printf("Enter: \n");
    printf("'p' - create producer\n");
    printf("'c' - create consumer\n");
    printf("'P' - delete producer\n");
    printf("'C' - delete consumer\n");
    printf("'q' - quit\n");

    // Unlink semaphores, that I need in the future
    sem_unlink("producer_sem");
    sem_unlink("consumer_sem");
    sem_unlink("mutex_");

    sem_t *producer_sem = open_sem(producer_sem, "producer_sem", O_CREAT, 0664, 1);
    sem_t *consumer_sem = open_sem(consumer_sem, "consumer_sem", O_CREAT, 0664, 1);
    sem_t *mutex_ = open_sem(mutex_, "mutex_", O_CREAT, 0664, 1);

//    sem_post(producer_sem);
//    sem_post(consumer_sem);
//    sem_post(mutex_);

    pid_t *producer_pids = NULL, *consumer_pids = NULL;
    int producer_count = 0, consumer_count = 0;

    producer_pids = (int *) malloc(sizeof(int));
    consumer_pids = (int *) malloc(sizeof(int));

    int proj_id = 'l';
    key_t key = ftok("/home/sifi/BSUIR/BSUIR_labs/4_term/SPO/lab7/key", proj_id);

    circle_t *msg_circle = (circle_t *) malloc(sizeof(circle_t));
    for(int i = 0; i < 9; i++){
        msg_circle->message[i].is_filled = false;
    }
    // Initialize queue
    msg_circle->head = 0;
    msg_circle->tail = 0;
    msg_circle->added = 0;

    int shm_id = shmget(key, sizeof(circle_t), 0664 | IPC_CREAT);
    msg_circle = shmat(shm_id, NULL, 0);

    char *shm_id_c = (char *) malloc(10 * sizeof(char));
    sprintf(shm_id_c, "%d", shm_id);
    char *const args[] = {shm_id_c, NULL};

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
                } else {
                    // Child process
                    printf("New producer has been created\n");
                    execv("/home/sifi/BSUIR/BSUIR_labs/4_term/SPO/lab7/producer/cmake-build-debug/producer",
                          args);
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
                    // child_proc
                    printf("New consumer has been created\n");
                    execv("/home/sifi/BSUIR/BSUIR_labs/4_term/SPO/lab7/consumer/cmake-build-debug/consumer",
                          args);
                }

                break;
            }

            case 'P': {
                if (producer_count != 0) {
                    kill(producer_pids[producer_count - 1], SIGKILL);
                    --producer_count;
                    wait(NULL);
                }
                break;
            }

            case 'C': {
                if (consumer_count != 0) {
                    kill(consumer_pids[consumer_count - 1], SIGKILL);
                    --consumer_count;
                    wait(NULL);
                }
                break;
            }

            case 'q': {
                shmctl(shm_id, IPC_RMID,NULL);
                for (int i = 0; i < producer_count; i++) {
                    kill(producer_pids[i], SIGKILL);
                }
                for (int i = 0; i < consumer_count; i++) {
                    kill(consumer_pids[i], SIGKILL);
                }
                sem_unlink("producer_sem");
                sem_unlink("consumer_sem");
                sem_unlink("mutex_");
                sem_close(producer_sem);
                sem_close(consumer_sem);
                sem_close(mutex_);
                return 0;
            }
        }
    }

}
