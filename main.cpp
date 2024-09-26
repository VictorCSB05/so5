#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <limits.h> 

#define SIZE 100 

int arr[SIZE]; 
int global_max = INT_MIN;
pthread_mutex_t mtx; 

void* find_max(void* arg) {
    int start = *(int*)arg; 
    int end = start + SIZE / 2; 

    int local_max = INT_MIN;
    for (int i = start; i < end; ++i) {
        if (arr[i] > local_max) {
            local_max = arr[i];
        }
    }

    
    pthread_mutex_lock(&mtx);
    if (local_max > global_max) {
        global_max = local_max;
    }
    pthread_mutex_unlock(&mtx);
    
    return NULL;
}

int main() {
    
    srand((unsigned int)time(NULL));
    for (int i = 0; i < SIZE; ++i) {
        arr[i] = rand() % 1000; 
    }

    pthread_t t1, t2;
    int start1 = 0;
    int start2 = SIZE / 2;

    pthread_mutex_init(&mtx, NULL); 

    
    pthread_create(&t1, NULL, find_max, (void*)&start1);
    pthread_create(&t2, NULL, find_max, (void*)&start2);

    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    
    printf("O maior elemento é: %d\n", global_max);

    pthread_mutex_destroy(&mtx); 
    return 0;
}
