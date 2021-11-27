/* Zweck: p11a - Übung zu main()-Aufrufparametern
 * Datum: 09.06.2020
 * Autor: Robin Freund
 */

#include <libgen.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

/* Funktion zur Erkennung ob ein String eine Zahl ist.
 * Der String darf '.', '+' und '-' enthalten.
 * Was noch geprueft werden koennte: Ob nur ein Punkt oder +/- vorhanden ist
 */
bool istZahl(char str[])
{
    /* Schaue durch jedes Zeichen, ob es keine Zahl und kein Minus, Plus oder Punkt ist - wenn doch: Keine Zahl*/
    for (int i = 0; i < strlen(str); i++)
    {
        if ((str[i] < '0' || str[i] > '9') && str[i] != '-' && str[i] != '+' && str[i] != '.')
            return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    int anzahl = 0;
    double summe = 0, mittelwert = 0, minimum = 0, maximum = 0;

    /* "Flag", steht auf false, solange die Minimal-/Maximalwerte noch nicht auf einen im Array bereits vorhandenen Wert
     * initialisiert sind
     **/
    bool minmaxInitialisiert = false;
    char prognam[256];

    /* Kopiere maximal 255 Zeichen in strncpy - nur fuer den Fall, dass der Programmname doch laenger als 255 Zeichen ist*/
    strncpy(prognam, basename(argv[0]), sizeof(prognam) - 1);

    /* Teile dem Benutzer mit, wenn er keine Argumente beim Programmaufruf angegeben hat */
    if (argc <= 1) {
        printf("Du musst mindestens eine Zahl uebergeben!\n");

        return EINVAL;
    }

    /* Laufe durch jedes Element nach dem Programmnamen */
    for (int i = 1; i < argc; i++)
    {
        /* Wenn das Element keine Zahl ist .. */
        if (!istZahl(argv[i]))
        {
            /* .. ueberspringe das Element und springe zur naechsten Schleifeniteration. */
            continue;
        }

        /* Wandle Zeichenkette in Zahl um */
        double zahl = atof(argv[i]);

        /* Wenn noch nicht passiert, initialisiere Minimum-/Maximumzahl, weil man einen Referenz-/Vergleichswert braucht */
        if (!minmaxInitialisiert)
        {
            minimum = zahl;
            maximum = zahl;

            minmaxInitialisiert = true;
        }

        anzahl++;
        summe += zahl;

        if (zahl < minimum) minimum = zahl;        
        if (zahl > maximum) maximum = zahl;
    }

    mittelwert = summe / anzahl;

    if (!strcmp(prognam, "summe")) {
        printf("Anzahl: %d\n", anzahl);
        printf("Summe: %g\n", summe);
    }

    if (!strcmp(prognam, "mittel")) {    
        printf("Anzahl: %d\n", anzahl);
        printf("Summe: %g\n", summe);

        printf("Mittelwert: %g\n", mittelwert);    
        printf("Minimumwert: %g\n", minimum);
        printf("Maximumwert: %g\n", maximum);
    }

    return 0;
}