#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

static void *spin(void *arg) {
    (void)arg;
    while (1);
    return NULL;
}

int main(void) {
    pthread_t t;
    int count = 0;
    while (1) {
        if (pthread_create(&t, NULL, spin, NULL) != 0) {
            fprintf(stderr, "thread creation blocked after %d threads\n", count);
            return 1;
        }
        pthread_detach(t);
        count++;
    }
    printf("ESCAPED\n");
    return 0;
}
