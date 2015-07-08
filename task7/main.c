#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define NUM_THREADS	2
#define BUFF_SIZE       20
float* global_buff; // данные с которыми будут работать потоки
int global_i = 0;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void calculate(float* val) {
    *val = (*val / 7 * 15 + 3) / 4 * 7 * (*val) /44 * 300; //иммитация очень важных расчетов
    sleep(1);
}

void init_buff(float** buff, int val) {
    int i;

    *buff = (float*)malloc(sizeof(float) * BUFF_SIZE); 
    for(i = 0; i < BUFF_SIZE; i++) {
        (*buff)[i] = val;
    }

}

int check_buff(float* buff, float standart) {
    int i;
    for(i = 0; i < BUFF_SIZE; i++) {
        if(buff[i] != standart) {
            printf("error position: %d\n", i);
            return 0;
        }
    }
    return 1;

}

void* work_loop(void* info) {
    long t_num, t_id;
    int i;

    while(global_i < BUFF_SIZE) {
 	pthread_mutex_lock(&mut);       
	i = global_i;
        global_i++;
        pthread_mutex_unlock(&mut);
	calculate(&global_buff[i]);
    }
    pthread_exit(NULL);
}

int main () {
    pthread_t threads[NUM_THREADS];
    int rc, t;

    float standart;
    float input_value = 5;
    init_buff(&global_buff, input_value);//заполняем буфер 
    for(t = 0; t < NUM_THREADS; t++) {
        printf("In main: creating thread %d\n", t);
        rc = pthread_create(&threads[t], NULL, work_loop, NULL);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    for(t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
        printf("Thread #%d finished\n", t);
    }
    
    standart = input_value;
    calculate(&standart);
    //global_buff[5] = 0;//вносим ошибку
    if(check_buff(global_buff, standart)) {
        printf("check: SUCCESS\n");
    }
    else {
        printf("check: FAIL\n");
    }
return 0;
}
