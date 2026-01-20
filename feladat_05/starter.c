#include <stdio.h>
#include <stdlib.h>

int main() {
    // 1. TODO: Hozz letre egy dinamikus int tombot 2 elem merettel
    // Kezdetben csak 2 számnak foglalunk helyet
    int* data = (int*)malloc(2 * sizeof(int));
    
    int capacity = 2;  // Jelenlegi kapacitas (fizikai méret)
    int size = 0;      // Jelenleg hany elem van benne (logikai méret)
    
    // 2. TODO: Ellenorizd, hogy a malloc sikeres volt-e
    if (data == NULL) {
        perror("Nem sikerult a memoriafoglalas");
        return 1;
    }
    
    printf("Dinamikus tomb (kezdeti kapacitas: %d)\n", capacity);
    printf("Irj be szamokat (0 = vege):\n");
    
    while (1) {
        int number;
        printf("> ");
        if (scanf("%d", &number) != 1) {
            printf("Hibas bemenet!\n");
            // "Lenyeljük" a hibás karaktereket a pufferből, hogy ne ragadjon be
            while(getchar() != '\n');
            continue; 
        }
        
        if (number == 0) {
            break;  // Vege a bevitelnek
        }
        
        // 3. TODO: Ha a tomb betelt, duplázzuk a meretet
        if (size == capacity) {
            int new_capacity = capacity * 2;
            printf("[INFO] Tomb betelt (%d). Atmeretezes: %d -> %d\n", 
                   capacity, capacity, new_capacity);
            
            // FONTOS: Safe realloc minta!
            // Egy ideiglenes változóba mentjük az eredményt.
            int* temp = (int*)realloc(data, new_capacity * sizeof(int));
            
            if (temp == NULL) {
                // Ha baj van, az eredeti 'data' még megvan, nem veszett el!
                fprintf(stderr, "Hiba: Nincs eleg memoria az atmeretezeshez!\n");
                break;
            }
            
            // Ha sikeres volt, frissítjük a pointert és a kapacitást
            data = temp;
            capacity = new_capacity;
        }
        
        // 4. TODO: Add hozza a szamot a tombhoz
        data[size] = number;
        size++;
    }
    
    // Kiirjuk az eredmenyt
    printf("\nBeirt szamok (%d db): ", size);
    
    // 5. TODO: Irj egy ciklust, ami kiirja az osszes szamot
    for (int i = 0; i < size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    
    // 6. TODO: Szabaditsd fels a memoriat!
    // Ne felejtsük el visszaadni a rendszerek!
    free(data);
    
    return 0;
}
