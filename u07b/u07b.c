/*
 * Author:          Robin Eschbach
 * Datum:           09.06.2020
 * Beschreibung:    überprüfen, ob ein Programmargument ein Palindrom ist
 */

#include <stdio.h>      // Für printf
#include <errno.h>      // Für EINVAL
#include <stdbool.h>    // Für die Verwendung von booleschen Werten
#include <string.h>     // Für strlen
#include <ctype.h>      // Für tolower

// Überprüfung mit Arrays
bool isPali(char* wort, int first, int last) {
    // Wenn die Indizes sich überschneiden wurde alles Abgeprüft
    // Ergo: Es ist ein Palindrom
    if(first >= last) {
        return true;
    }

    // Ist der Buchstabe an der Stelle first nicht gleich dem an der Stelle last,
    // so ist es kein Palindrom
    if(wort[first] != wort[last]) {
        return false;
    }

    // Ansonsten werden die Indezies um einen nach innen gezogen.
    return isPali(wort, first + 1, last - 1);
}

// Überprüfung mit Arrays. Dabei wird Case-Insensitive geprüft.
bool isPaliCaseInsensitive(char* wort, int first, int last) {
    if(first >= last) {
        return true;
    }

    // tolower ermöglicht das Ignorieren der Groß- und Kleinschreibung
    if(tolower(wort[first]) != tolower(wort[last])) {
        return false;
    }
    return isPaliCaseInsensitive(wort, first + 1, last - 1);
}

// Überprüfung mit Zeigern
bool isPaliPointer(char* first, char* last) {
    // Arrays sind im Speicher hintereinander weg geschrieben
    // D.h. Das Selbe Prinzip wie oben gilt also auch hier
    if(first >= last) {
        return true;
    }

    // Sind die Werte unter first und last nicht gleich ist es kein Palindrom
    if(*first != *last) {
        return false;
    }

    // Ansonsten werden die Zeiger einen nach innen gezogen
    return isPaliPointer(first + 1, last - 1);
}

int main(int argc, char* argv[]) {
    // Wenn mehr oder weniger als ein Argument übergeben wird,
    // wird ein Fehler ausgegeben
    if(argc != 2) {
        printf("Uebergeben Sie bitte genau ein Wort!");
        return EINVAL;
    }

    // Die if-Überprüfungen für die andren Funktionen
    // if(isPaliPointer(argv[1], argv[1] + strlen(argv[1]) - 1)) {
    // if(isPaliCaseInsensitive(argv[1], 0, strlen(argv[1]) - 1)) {
    if(isPali(argv[1], 0, strlen(argv[1]) - 1)) {
        printf("%s ist ein Palindrom!\n", argv[1]);
    } else {
        printf("%s ist kein Palindrom!\n", argv[1]);
    }

    return 0;
}