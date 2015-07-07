#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define NUM_THREADS     1
#define BUFF_SIZE       10000000
#define AREA_SIZE       BUFF_SIZE / NUM_THREADS

float global_buff[BUFF_SIZE]; // данные с которыми будут работать потоки

void calculate(float* val) {
    *val = (*val / 7 * 15 + 3) / 4 * 7 * (*val) /44 * 300; //иммитация очень важных расчетов
}

void init_buff(float* buff, int val) {
    int i;
    for(i = 0; i < BUFF_SIZE; i++) {
        buff[i] = val;
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
    int start;
    int end;


    start = ((int*)info)[0];// получаем индекс начала области, которую будет обрабатывать данный поток
    end =  ((int*)info)[1];// получаем индекс конеца области, которую будет обрабатывать данный поток
    for (i = start; i < end; i++) {//обрабатываем выделенную область
        //printf("Hello World! Thread start: %d, end: %d, i: %d\n", start, end, i);
        calculate(&global_buff[i]);
        //printf("value = %f",global_buff[i]);
    }
    pthread_exit(NULL);
}

int main () {
    pthread_t threads[NUM_THREADS];
    int rc, area_start, area_end;
    long t;
    int info[NUM_THREADS][2]; //информация для потока [0] - начало области общета [1] - конец области
    clock_t start_t, end_t;
    double total_t;

    float standart;
    float input_value = 5;
    
    init_buff(global_buff, input_value);//заполняем буфер 


    start_t = clock();
    for(t = 0; t < NUM_THREADS; t++) {
        area_start = t * AREA_SIZE;
        area_end = (t + 1) * AREA_SIZE;
        info[t][0] = area_start;
        info[t][1] = area_end;
        printf("In main: creating thread %ld  start: %d end: %d\n", t, area_start, area_end);
        rc = pthread_create(&threads[t], NULL, work_loop, (void *)info[t]);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    for(t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
        printf("Thread #%ld finished\n", t);
    }
    
    
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time: %fms\n", total_t);
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

