#include "fourchettes.h"

/* fonction: fourchettes_init
 * f: la structurre à initialiser
 * nb_forks : le nombre de fourchettes/baguettes
 */
void fourchettes_init(fourchettes* f, int nb_forks){
    pthread_mutex_init(&f->m, NULL);
    pthread_cond_init(&f->c, NULL);
    f->nb_forks = nb_forks;
    f->forks = (bool*) malloc(sizeof(bool) * nb_forks);
    for (int i = 0; i < nb_forks; i++){
        f->forks[i] = true;
    }
}

/* fonction fourchettes_destroy
 * f : la structure à détruire
 */
void fourchettes_destroy(fourchettes* f){
    pthread_mutex_destroy(&f->m);
    pthread_cond_destroy(&f->c);
    free(f->forks);
}

/* fonction : fourchettes_prendre
 * f : structure contenant les fourchettes
 * place : place du philosophe
 */
void fourchettes_prendre(fourchettes* f, int place){
    int f1 = place, f2 = (place + 1) % f->nb_forks;
    pthread_mutex_lock(&f->m);
    while( !f->forks[f1] && !f->forks[f2]){
        pthread_cond_wait(&f->c, &f->m);
    }
    f->forks[f1] = false;
    f->forks[f2] = false;
    pthread_mutex_unlock(&f->m);
}

/* fonction : fourchettes_lacher
 * Permet de lacher les fourchettes tenues.
 * f : structure contenant les fourchettes
 * place : place du philosophe
 */
void fourchettes_lacher(fourchettes* f, int place){
    // TODO : potentiellement erreur
    int f1 = place, f2 = (place + 1) % f->nb_forks;
    pthread_mutex_lock(&f->m);
    f->forks[f1] = true;
    f->forks[f2] = true;
    pthread_mutex_unlock(&f->m);
    pthread_cond_signal(&f->c);
}

/* fonction : fourchettes_print
 * Affiche les fourchettes selon leur état.
 * f : structure contenant les fourchettes
 */
void fourchettes_print(fourchettes* f){
    for (int i = 0; i < f->nb_forks; i++){
        printf("[%d] %s\n", i, f->forks[i] ? "libre" : "prise");
    }
}
