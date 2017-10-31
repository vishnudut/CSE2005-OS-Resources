#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t writer,reader,mutex;
int readercount=0,i=0;
int buffer[5]={0};


void *Write(){
    sem_wait(&writer);
    for(i = 0; i < 5; i++){
        buffer[i] = i;
    }
    sem_post(&writer);
}


void *Read(){
    sem_wait(&mutex);
    readercount++;
    if(readercount==1){
        sem_wait(&writer);
    }
    sem_post(&mutex);

    printf("Reader reading");
    for(i = 0; i < 5; i++)
        printf(" %d", buffer[i]);
    printf("\n");

    sem_wait(&mutex);
    readercount--;
    if(readercount==0){
        sem_post(&writer);
    }
    sem_post(&mutex);
}


int main(){
    sem_init(&mutex,0,1);
    sem_init(&writer,0,1);
    sem_init(&reader,0,1);
    pthread_t thread1,thread2;
    pthread_create(&thread1,NULL,Write,NULL);
    pthread_create(&thread2,NULL,Read,NULL);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    sem_destroy(&mutex);
    sem_destroy(&reader);
    sem_destroy(&writer);
    
}

