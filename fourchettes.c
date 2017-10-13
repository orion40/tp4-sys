#include "fourchettes.h"

typedef struct{
    int nb_forks;
    bool *forks;
    pthread_mutex_t *m;
    pthread_cond_t *c;
} fourchettes;

void fourchettes_init(fourchettes* f, int nb_forks){
    pthread_mutex_init(f->m, NULL);
    pthread_cond_init(f->c, NULL);
    f->nb_forks = nb_forks;
    f->forks = (bool*) malloc(sizeof(bool) * nb_forks);

}

void fourchettes_destroy(fourchettes* f){

}

void fourchettes_prendre(fourchettes* f, int place){
    pthread_mutex_lock(f->m);
    while( !f->forks[place] && !f->forks[(place+1) % f->nb_fourchettes]){
        pthread_cond_wait(f->c, f->m);
    }
    prendre_fourchettes(place);
    pthread_mutex_unlock(f->m);
}

void fourchettes_lacher(fourchettes* f, int place){

}

void fourchettes_print(fourchettes* f){
    for (int i = 0; i < f->nb_forks; i++){
        printf("[%d] %s\n", f->forks[i] ? "libre" : "prise");
    }
}
