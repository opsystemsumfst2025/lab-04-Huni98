#include <stdio.h>
#include <stdlib.h>

// JAVÍTOTT FÜGGVÉNYEK

void null_pointer_bug() {
    printf("\n--- 1. Teszt: NULL pointer javítása ---\n");
    
    // JAVÍTÁS: Nem NULL-ra mutatunk, hanem foglalunk neki helyet
    int* ptr = (int*)malloc(sizeof(int));
    if (ptr == NULL) return; // Mindig ellenőrizzük!

    *ptr = 42;
    printf("Sikerült írni a pointerre: %d\n", *ptr);
    
    // Ne felejtsük el felszabadítani
    free(ptr);
}

void array_overflow_bug() {
    printf("\n--- 2. Teszt: Tömb túlindexelés javítása ---\n");
    
    int array[10];
    
    // JAVÍTÁS: i <= 15 helyett i < 10
    // Így nem írunk túl a tömb határain
    for (int i = 0; i < 10; i++) {
        array[i] = i * 10;
        printf("array[%d] = %d\n", i, array[i]);
    }
}

void use_after_free_bug() {
    printf("\n--- 3. Teszt: Use after free javítása ---\n");
    
    int* data = (int*)malloc(5 * sizeof(int));
    if (data == NULL) {
        fprintf(stderr, "Malloc hiba\n");
        return;
    }
    
    // Feltöltjük a tömböt
    for (int i = 0; i < 5; i++) {
        data[i] = i + 100;
    }
    
    printf("Adatok: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    
    // JAVÍTÁS: A 'rossz' részt (a free utáni írást) kitöröltük vagy a free elé tettük.
    // Itt most demonstrációképp módosítjuk az értékeket MÉG a free előtt:
    printf("Módosítjuk az adatokat (még a free előtt)...\n");
    for (int i = 0; i < 5; i++) {
        data[i] = i + 200; 
    }

    // És csak a legvégén szabadítjuk fel
    free(data);
    printf("Memória felszabadítva. Vége.\n");
}

int main() {
    printf("Segmentation Fault Javítva\n");
    printf("==========================\n");
    
    // Most már mindegyiket biztonságosan lefuttathatjuk
    null_pointer_bug();
    array_overflow_bug();
    use_after_free_bug();
    
    printf("\nProgram vége. Minden hiba kijavítva!\n");
    return 0;
}
