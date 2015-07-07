#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


#define NUM_THREADS     5


void *print_hello(void *num) {
        long t_num;
        t_num = (long) num;
        printf("Hello World! Thread num: %ld\n", t_num);
        pthread_exit(NULL);
}


int main (int argc, char *argv[]) {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    for(t = 0; t < NUM_THREADS; t++) {
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, print_hello, (void *)t);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    
    for(t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
        printf("Thread #%ld finished\n", t);
    }

    return 0;
}
