#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    char words[10][20]; // Zweidimensionales Array zum Speichern von bis zu 10 Wörtern mit maximal 20 Zeichen pro Wort
    int wordCount = 0; // Zähler für die Anzahl der eingegebenen Wörter
    int flag = 0; // Flagge zur Kennzeichnung der Abbruchbedingung

    // Schleife zum Einlesen von Wörtern von der Konsole, bis die Abbruchbedingung erfüllt ist
    while (wordCount < 10 && flag == 0) {
        scanf("%s", words[wordCount]); // Wort von der Konsole einlesen
        if (strcmp(words[wordCount], "ZZZ") == 0) {
            flag = 1; // Flagge setzen, um die Schleife zu beenden, wenn "ZZZ" eingegeben wird
        }
        if (strlen(words[wordCount]) > 20) {
            printf("Wort zu lang, es sind nur maximal 20 Zeichen erlaubt.\n"); // Fehlermeldung ausgeben, wenn das Wort die maximale Länge überschreitet
            exit(0); // Programm beenden
        }
        wordCount += 1; // Wortanzahl erhöhen
    }

    // Sortieren der Wörter in alphabetischer Reihenfolge mit dem Selection-Sort-Algorithmus
    for (int k = 0; k < 10; k++) {
        int min = k;
        for (int i = k + 1; i < 10; i++) {
            if (strcmp(words[i], words[min]) < 0) {
                min = i; // Index des kleinsten Worts aktualisieren
            }
        }
        if (strcmp(words[min], words[k]) != 0) {
            char temp;
            temp = *words[min]; // Wörter tauschen
            *words[min] = *words[k];
            *words[k] = temp;
        }
    }

    // Sortierte Liste der Wörter ausgeben
    printf("Sortierte Liste:\n");
    for (int z = 0; z < 10; z++) {
        printf("%s\n", words[z]);
    }

    return EXIT_SUCCESS;
}
