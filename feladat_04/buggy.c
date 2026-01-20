#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Egy egyszeru struktura
typedef struct {
    char* name;
    int age;
} Person;

// HIBA: Ez a fuggveny memoriat foglal, de sehol nem szabaditjuk fel
Person* create_person(const char* name, int age) {
    Person* p = (Person*)malloc(sizeof(Person));
    if (p == NULL) {
        return NULL;
    }
    
    p->name = (char*)malloc(strlen(name) + 1);
    if (p->name == NULL) {
        free(p);
        return NULL;
    }
    
    strcpy(p->name, name);
    p->age = age;
    
    return p;
}

// HIBA: Ez a fuggveny is foglal, de nem szabadit fel
char* create_greeting(const char* name) {
    char* greeting = (char*)malloc(100);
    if (greeting == NULL) {
        return NULL;
    }
    
    sprintf(greeting, "Hello, %s!", name);
    return greeting;
}

int main() {
    printf("Memory leak demonstracio\n");
    printf("========================\n\n");
    
    // Letrehozunk egy szemelyt
    Person* john = create_person("John Doe", 25);
    if (john == NULL) {
        fprintf(stderr, "Hiba: nem sikerult szemelyt letrehozni\n");
        return 1;
    }
    
    printf("Szemely letrehozva: %s, %d eves\n", john->name, john->age);
    
    // Letrehozunk egy udvozletet
    char* greeting = create_greeting(john->name);
    if (greeting == NULL) {
        fprintf(stderr, "Hiba: nem sikerult udvozletet letrehozni\n");
        return 1;
    }
    
    printf("%s\n", greeting);
    
    // --- JAVÍTÁS INNEN ---
    
    // 1. Felszabadítjuk az üdvözlet szöveget (amit a create_greeting foglalt)
    free(greeting);
    
    // 2. Felszabadítjuk a személy nevét (amit a create_person-ben a p->name malloc foglalt)
    free(john->name);
    
    // 3. Felszabadítjuk magát a személy struktúrát (amit a create_person-ben a p malloc foglalt)
    // FONTOS: Előbb a nevet (belső pointer), és csak utána a struktúrát!
    // Ha fordítva csinálnád, a john->name már érvénytelen memória lenne.
    free(john);
    
    printf("\nMemoria sikeresen felszabaditva!\n");
    
    return 0;
}
