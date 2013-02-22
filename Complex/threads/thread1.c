#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_function(void *arg) {

    int i;

    for (i=0; i<20; i++) {
        printf("Thread says hi!\n");
        sleep(1);
    }
    return (void *) 0;
}

int main() {
    pthread_t mythread;

    sleep (5);

    if (pthread_create (&mythread, NULL, thread_function, NULL) ) {
        printf("error creating thread\n");
        abort ();
    }

    if (pthread_join (mythread, NULL)) {
        printf("error joining thread\n");
        abort ();
    }

    exit(0);

}
