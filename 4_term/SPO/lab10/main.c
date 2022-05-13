#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <aio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 100
char *buffer;

char *files[] = {"../files/file1", "../files/file2", "../files/file3", NULL};
char output_file[] = {"../files/all.txt"};

pthread_mutex_t m_reader, m_writer;

bool next_read = true, next_write = false;
struct aiocb *reader, *writer;

void *reader_routine() {
    reader = malloc(sizeof(struct aiocb));

    reader->aio_reqprio = 0;
    reader->aio_offset = 0;
    reader->aio_sigevent.sigev_notify = SIGEV_SIGNAL;
    reader->aio_sigevent.sigev_signo = SIGUSR1;

    for (int i = 0; i < 3; i++) {
        while (!next_read);
        next_read = false;

        buffer = malloc(BUFFER_SIZE);

        if ((reader->aio_fildes = open(files[i], O_RDONLY)) == -1) {
            perror("File open error");
            exit(EXIT_FAILURE);
        }

        reader->aio_buf = buffer;
        reader->aio_nbytes = BUFFER_SIZE;

        aio_read(reader);
        while (!next_read);
        printf("Now file %s read. Reader info: %s\n", files[i], reader->aio_buf);
    }

    return NULL;
}

void *writer_routine() {
    int offset = 0;
    writer = malloc(sizeof(struct aiocb));
    writer->aio_reqprio = 0;
    writer->aio_sigevent.sigev_notify = SIGEV_SIGNAL;
    writer->aio_sigevent.sigev_signo = SIGUSR2;

    for (int i = 0; i < 3; i++) {

        while (!next_write);
        next_write = false;

        if ((writer->aio_fildes = open(output_file, O_RDWR | O_CREAT)) == -1) {
            perror("\nOut file error");
            exit(EXIT_FAILURE);
        }
        writer->aio_offset = offset;
        offset += strlen(buffer);
        writer->aio_nbytes = strlen(buffer);
        writer->aio_buf = buffer;

        printf("Now file %s writen. Writen info: %s\n", files[i], writer->aio_buf);
        aio_write(writer);
    }

    return NULL;
}

void end_read(__attribute__((unused)) int signum) {
    next_read = false;
    next_write = true;
}

void end_write(__attribute__((unused)) int signum) {
    next_write = false;
    next_read = true;
}

int main() {
    truncate(output_file, 0);
    signal(SIGUSR1, end_read);
    signal(SIGUSR2, end_write);

    pthread_t th;
    pthread_create(&th, NULL, reader_routine, NULL);
    writer_routine();

    pthread_join(th, NULL);

    free(reader);
    free(writer);
}