#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Globális bankszámla egyenleg (ezen fognak veszekedni a szálak)
int balance = 0;

// 1. TODO: Definiáld a szálak számát (10)
#define NUM_THREADS 10

// 2. TODO: Definiáld, hogy hányszor növeljen minden szál (1000)
#define INCREMENTS_PER_THREAD 1000

// A szál függvény, amit minden szál végre fog hajtani
void* deposit_money(void* arg) {
    // 3. TODO: Írj egy ciklust, ami INCREMENTS_PER_THREAD-szer fut
    // Minden iterációban növeld a balance változót eggyel
    for (int i = 0; i < INCREMENTS_PER_THREAD; i++) {
        balance++; // Itt történik a versenyhelyzet!
    }
    return NULL;
}

int main() {
    // 4. TODO: Hozz létre egy pthread_t tömböt NUM_THREADS méretű elemmel
    pthread_t threads[NUM_THREADS];
    
    printf("Kezdeti egyenleg: %d dollar\n", balance);
    printf("Inditas: %d penztaros, mindegyik %d dollar befizetesevel...\n", 
           NUM_THREADS, INCREMENTS_PER_THREAD);
    
    // 5. TODO: Indítsd el a szálakat egy ciklussal
    for (int i = 0; i < NUM_THREADS; i++) {
        // pthread_create paraméterei:
        // 1. pointer a thread változóra
        // 2. attribútumok (NULL = alapértelmezett)
        // 3. a függvény, amit futtatni kell (deposit_money)
        // 4. paraméter a függvénynek (most NULL, mert nem adunk át semmit)
        if (pthread_create(&threads[i], NULL, deposit_money, NULL) != 0) {
            perror("Hiba a szal letrehozasakor");
            return 1;
        }
    }
    
    // 6. TODO: Várd meg, hogy minden szál befejeződjön
    for (int i = 0; i < NUM_THREADS; i++) {
        // pthread_join: megvárja, amíg az adott szál kilép
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Hiba a szal bevarasakor");
            return 1;
        }
    }
    
    printf("Vegso egyenleg: %d dollar\n", balance);
    printf("Vart egyenleg: %d dollar\n", NUM_THREADS * INCREMENTS_PER_THREAD);
    
    if (balance != NUM_THREADS * INCREMENTS_PER_THREAD) {
        printf("\nADATVESZTES TORTENT! Ez egy race condition.\n");
    } else {
        printf("\nSzerencses vagy - ezuttal jo lett az eredmeny.\n");
        printf("De ez nem jelenti, hogy a kod helyes!\n");
    }
    
    return 0;
}
