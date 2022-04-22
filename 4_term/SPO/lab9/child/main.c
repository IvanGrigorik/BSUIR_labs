#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>

int fd;
unsigned char *text;
size_t size;

struct stat stat_buf;

void user_action(int sig_number) {

    fstat(fd, &stat_buf);
    size = stat_buf.st_size;

    text = mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);
    if (text == MAP_FAILED) {
        perror("Mmap failed");
    }
    printf("\033[32m" "%s" "\033[37m\n", text);
    munmap(text, size);
}

int main(int argc, char *argv[]) {

    signal(SIGUSR1, user_action);

    fd = open(argv[0], O_RDWR);

    while (1) {

    }
}
