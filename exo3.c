#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include <sys/types.h>

#include "fourchettes.h"

#define NUM_PHILOSOPHER 7
#define NUM_EATING 20

/* struct: philosophers
 *
 * fourchettes: adresse des structures de fourchettes
 * reste: nombre de fois restantes à manger et psner
 */
typedef struct{
    fourchettes* f_t;
    int reste;
    int place;
}philosophers;

void think(){
    pid_t tid = pthread_self();
    printf("Philosopher %x is thinking...\n", tid);
    usleep(rand() % 1000000);
    printf("Philosopher %x stopped thinking.\n", tid);
}

void eat(philosophers* p){
    pid_t tid = pthread_self();
    printf("Philosopher %x is eating (%d left)...\n", tid, p->reste);
    usleep(rand() % 1000000);
    printf("Philosopher %x stopped eating.\n", tid);
}

void* philosopher (void* args){
    philosophers *p = (philosophers *)args;
    for (; p->reste >= 0; p->reste--){
        think();
        fourchettes_prendre(p->f_t, p->place);
        eat(p);
        fourchettes_lacher(p->f_t, p->place);
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
        p[i]->place = i;
    }

    fourchettes_print(&f);
    for (int i = 0; i < NUM_PHILOSOPHER; i++){
        pthread_create(&threads[i], NULL, philosopher, p[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHER; i++){
        pthread_join(threads[i], NULL);
    }
    fourchettes_print(&f);

    fourchettes_destroy(&f);
 }
