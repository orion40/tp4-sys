#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include <sys/types.h>

#include "fourchettes.h"

#define NUM_PHILOSOPHER 7
#define NUM_EATING 20
#define NUM_TESTS 1

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

void usage (char* prog){
    printf("Usage: %s <num of philisopher> <num of forks> <num of tests>\n"
            , prog);
    exit(0);
}

int main(int argc, char* argv[]){
    int num_philosopher = NUM_PHILOSOPHER;
    int food_quantity = NUM_EATING;
    int num_of_tests = NUM_TESTS;
    switch (argc){
        case 4:
            num_of_tests = atoi(argv[3]);
        case 3:
            food_quantity = atoi(argv[2]);
        case 2:
            num_philosopher = atoi(argv[1]);
            break;
        default:
            usage(argv[0]);
            break;
    }
    pthread_t threads[num_philosopher];
    philosophers* p[num_philosopher];
    fourchettes f;

    fourchettes_init(&f, num_philosopher);

    for (int i = 0; i < num_philosopher; i++){
        p[i] = (philosophers*) malloc(sizeof(philosophers));
        p[i]->f_t = &f;
        p[i]->reste = food_quantity;
        p[i]->place = i;
    }

    fourchettes_print(&f);
    for (int i = 0; i < num_philosopher; i++){
        pthread_create(&threads[i], NULL, philosopher, p[i]);
    }

    for (int i = 0; i < num_philosopher; i++){
        pthread_join(threads[i], NULL);
    }
    fourchettes_print(&f);
    if (fourchettes_all_free(&f)){
        printf("Toutes les fourchettes ont été libérées.\n");
    }else {
        printf("Erreur, des fourchettes n'ont pas été libérées.\n");
        exit(1);
    }

    fourchettes_destroy(&f);
}
