#include <stdio.h>
#include <unistd.h>

int main() {
    while (1) {
        printf("Hello, from producer!\n");
        sleep(3);
    }
    return 0;
}
