#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t E, F, mutex;
int i=0;
int buffer[5]={0};


void *Producer(){
    sem_wait(&E);
    sem_wait(&mutex);
    for(i = 0; i < 5; i++){
        buffer[i] = i;
    }
    sem_post(&mutex);
    sem_post(&F);
}


void *Consumer(){
    sem_wait(&F);
    sem_wait(&mutex);
    printf("Consumer consumes: ");
    for(i = 0; i < 5; i++){
        printf("%d ", buffer[i]);
    }
    printf("\n");
    sem_post(&mutex);
    sem_post(&E);
}


int main(){
    sem_init(&mutex, 0, 1);
    sem_init(&E,0,5);
    sem_init(&F,0,0);
    pthread_t thread1,thread2;
    pthread_create(&thread1,NULL,Producer,NULL);
    pthread_create(&thread2,NULL,Consumer,NULL);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    sem_destroy(&mutex);
    sem_destroy(&E);
    sem_destroy(&F);
    
}

