#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Globalis bankszamla egyenleg
int balance = 0;

// 1. TODO: Deklaralj egy pthread_mutex_t valtozot ide
// Ez a "kulcs", ami védi a bankszámlát
pthread_mutex_t mutex;

#define NUM_THREADS 10
#define INCREMENTS_PER_THREAD 1000

// A szal fuggveny, amit minden szal vegre fog hajtani
void* deposit_money(void* arg) {
    for (int i = 0; i < INCREMENTS_PER_THREAD; i++) {
        // 2. TODO: Zarold a mutexet itt (pthread_mutex_lock)
        // Mielőtt hozzányúlunk a közös változóhoz, bezárjuk az ajtót!
        pthread_mutex_lock(&mutex);
        
        balance++;
        
        // 3. TODO: Oldsd fel a mutexet itt (pthread_mutex_unlock)
        // Miután végeztünk, kinyitjuk az ajtót a többieknek
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    
    // 4. TODO: Inicializald a mutexet
    // Ezt még a szálak indítása előtt kell megtenni!
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Mutex inicializalas hiba");
        return 1;
    }
    
    printf("Kezdeti egyenleg: %d dollar\n", balance);
    printf("Inditas: %d penztaros, mindegyik %d dollar befizetesevel...\n", 
           NUM_THREADS, INCREMENTS_PER_THREAD);
    printf("MOST MAR MUTEX VEDELEMMEL!\n\n");
    
    // Szalak inditasa
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, deposit_money, NULL) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }
    
    // Szalak bevarasa
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }
    
    // 5. TODO: Szuntessed meg a mutexet (pthread_mutex_destroy)
    // Ha már nincs rá szükség, takarítsunk fel
    pthread_mutex_destroy(&mutex);
    
    printf("Vegso egyenleg: %d dollar\n", balance);
    printf("Vart egyenleg: %d dollar\n", NUM_THREADS * INCREMENTS_PER_THREAD);
    
    if (balance == NUM_THREADS * INCREMENTS_PER_THREAD) {
        printf("\nSIKER! A mutex megvedi a kozos valtozot.\n");
    } else {
        printf("\nHIBA! Meg mindig van adatvesztes. Ellenorizd a mutex hasznalatat!\n");
    }
    
    return 0;
}
