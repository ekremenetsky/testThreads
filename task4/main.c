#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS     5

int global_i = 0;

void* increment(void *num) {
    int i = 0;
    while(i++ < 10) {
        global_i++;
        printf("global_i = %d\n", global_i);
        sleep(1);
        fflush(stdout);
    }
    pthread_exit(NULL);
}



void* decriment(void *num) {
    int i = 0;
    while(i++ < 10) {
        global_i--;
        printf("global_i = %d\n", global_i);
        fflush(stdout);
        sleep(1);
    }
    pthread_exit(NULL);
}




int main (int argc, char *argv[]) {
    pthread_t threads_inc;
    pthread_t threads_dec;
    int rc;
    long t = 0;

    printf("start prog\n");
    fflush(stdout);
    rc = pthread_create(&threads_inc, NULL, increment, (void *)t);
    if (rc) {
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
    }

    rc = pthread_create(&threads_dec, NULL, decriment, (void *)t);
    if (rc) {
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
    }


    //sleep(10);
    pthread_join(threads_dec, NULL);
    pthread_join(threads_inc, NULL);
return 0;
}

