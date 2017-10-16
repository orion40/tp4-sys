#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include <sys/types.h>

#include "fourchettes.h"

#define NUM_PHILOSOPHER 5
#define NUM_EATING 20

/* struct: philosophers
 *
 * fourchettes: adresse des structures de fourchettes
 * reste: nombre de fois restantes à manger et psner
 */
typedef struct{
    fourchettes* f_t;
    int reste;
}philosophers;

void think(){
    pid_t tid = pthread_self();
    printf("Philosopher %x is thinking...\n", tid);
    usleep(rand() % 1000000);
    printf("Philosopher %x stopped thinking.\n", tid);
}

void eat(){
    pid_t tid = pthread_self();
    printf("Philosopher %x is eating...\n", tid);
    usleep(rand() % 1000000);
    printf("Philosopher %x stopped eating.\n", tid);
}

void* philosopher (void* args){
    philosophers *p = (philosophers *)args;
    for (int i = 0; i < p->reste; i++){
        think();

        //eat();
    }

    return NULL;
}

int main(int argc, char* argv[]){
    pthread_t threads[NUM_PHILOSOPHER];
    philosophers* p[NUM_PHILOSOPHER];
    fourchettes f;

    fourchettes_init(&f, NUM_PHILOSOPHER);

    for (int i = 0; i < NUM_PHILOSOPHER; i++){
        p[i] = (philosophers*) malloc(sizeof(philosophers));
        p[i]->f_t = &f;
        p[i]->reste = NUM_EATING;
    }

    for (int i = 0; i < NUM_PHILOSOPHER; i++){
        pthread_create(&threads[i], NULL, philosopher, p[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHER; i++){
        pthread_join(threads[i], NULL);
    }

    fourchettes_destroy(&f);
 }
