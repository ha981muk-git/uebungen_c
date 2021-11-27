/*
 * Author:          Robin Eschbach
 * Datum:           16.06.2020
 * Beschreibung:    Erstellen und Lesen von squentiellen Dateien
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {
    // Platzhalter für den Dateinamen
    char name[128];
    // Puffer für das read/write der Datei
    char buffer[128];
    // Zeiger auf die zu behandelnde Datei
    FILE* file;

    // Einlesen eines Dateinamen mit höchstens 128 Zeichen
    printf("Geben Sie bitte den Namen der Datei ein: ");
    scanf("%128s", name);

    // Setzt den Lesezeiger von stdin ans Ende
    // Entfernt die leere Zeile am Anfange der Datei
    fseek(stdin, 0, SEEK_END);

    // Öffnet die Datei mit den Read Flag
    if((file = fopen(name, "r")) != NULL) {
        // Lesen der Datei in 128er Schritten bis nichts mehr gelesen werden kann
        while(fgets(buffer, 128, file) != NULL) {
            // Ausgabe der momentanen Zeichen
            printf("%s", buffer);
        }
    }
    // Öffnet die Datei mit dem Write Flag, falls sie nicht gelesen werden kann
    else if((file = fopen(name, "w")) != NULL) {
        // Lesen des Input-Streams in 128er Schritten bis nichts mehr gelsen werden kann
        while(fgets(buffer, 128, stdin) != NULL) {
            // Falls am Anfang *fin* steht => Ende
            if(strncmp(buffer, "*fin*", 5) == 0) {
                break;
            }
            // Schreiben der momentanen Zeichen in die Datei
            fputs(buffer, file);
        }
    } else {
        // Ausgabe bei einem Fehler
        printf("Es trat ein Fehler mit der Verarbeitung der Datei auf!\n");
        int err = errno;
        perror("[FOPEN]");
        return err;
    }

    // Schließen der offenen Datei
    fclose(file);

    return 0;
}