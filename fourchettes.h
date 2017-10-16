#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

/* struct: fourchettes
 * nb_forks : taille du tableau
 * forks : tableau indiquant la disponibilité des fourchettes (true : libre)
 * m : mutex pour controler l'accès à la structure
 * c : condition pour faire attendre les philosophes
 */
typedef struct{
    int nb_forks;
    bool *forks;
    pthread_mutex_t m;
    pthread_cond_t c;
} fourchettes;

void fourchettes_init(fourchettes* f, int nb_forks);
void fourchettes_destroy(fourchettes* f);
void fourchettes_prendre(fourchettes* f, int place);
void fourchettes_lacher(fourchettes* f, int place);
void fourchettes_print(fourchettes* f);
