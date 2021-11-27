/* Zweck: Hausaufgabe u11b - Aufrufargumente
 * Autor: Robin Freund
 * Datum: 02.06.2020
 * 
 * Hinweis: Programm kompilieren (gcc -Wall -o programm u11b.c) und 
 * dann symbolische Links auf das Programm erstellen (ln -s programm upper, ln -s programm lower, ..)
 * Auf diese Weise wird immer das selbe Programm aufgerufen, aber mit unterschiedlichem
 * Aufrufnamen.
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
/* #include <libgen.h> fuer basename */

/* Funktion zur Erkennung, ob die Zeichenkette Ziffern enthaelt */
bool hatZahl(char str[], int len) {

    /* Gehe durch jedes Zeichen in der Zeichenkette.. */
    for (int i = 0; i < len; i++) {

        /*.. und brich die Schleife ab, wenn eine Ziffer gefunden wurde */
        if (str[i] >= '0' && str[i] <= '9')
            return true;
    }

	/* Wenn der String zuende ist und keine Ziffer gefunden wurde,
       das entsprechend zurueckgeben. */
    return false;
}

/* Main-Funktion: 
 * argc enthaelt Anzahl aller Aufrufargumente (auch dem Programmnamen)
 * argv[] enthaelt alle Argumente als Zeichenketten
 * Beispiel: ./upper abc def ghi
 * wird zu: argc = 4, argcv = { "./upper", "abc" "def" "ghi" }
 */
int main(int argc, char *argv[]) {

    /* Alternative: char * progname = basename(argv[0]); */

	char progname[1024];

    /* Mehr dazu auf Moodle: https://moodle.hs-worms.de/moodle/mod/forum/discuss.php?d=29841#p37500 
     * Wenn Programmname ein Slash (/) enthaelt.. (z.B. ./upper)       
     */
    if (strrchr(argv[0], '/')) {
        /*.. kopiere alles hinter dem Slash in progname */
		strncpy(progname, strrchr(argv[0],'/') + 1, sizeof(progname));
	} else {
        /* Bei keinem Slash: Direkt das erste Argument als Programmnamen nutzen */
		strncpy(progname, argv[0], sizeof(progname));
	}

    /* Wenn Programmname "upper" ist .. */
    if (strcmp(progname, "upper") == 0) {

        /* .. laufe durch alle Argumente .. */
        for (int i = 1; i < argc; i++) {
            /* .. und gib jedes Zeichen in Grossbuchstaben */
            for (int pos = 0; pos < strlen(argv[i]); pos++) {
                printf("%c", toupper(argv[i][pos]));
            }

            printf(" ");
        }

    /* Wenn Programmname "lower" ist .. */
    } else if (strcmp(progname, "lower") == 0) {

        /* .. laufe durch alle Argumente .. */
        for (int i = 1; i < argc; i++) {

            /* .. und gib jedes Zeichen in Kleinbuchstaben */
            for (int pos = 0; pos < strlen(argv[i]); pos++) {
                printf("%c", tolower(argv[i][pos]));
            }

            printf(" ");
        }

    /* Wenn Programmname "generatePass" ist .. */
    } else if (strcmp(progname, "generatePass") == 0) {

        /* .. nimm von jedem Argument das erste Zeichen */
        for (int i = 1; i < argc; i++) {            
            printf("%c", argv[i][0]);
        }

    /* Wenn Programmname "number" ist .. */
    } else if (strcmp(progname, "number") == 0) {

        /* .. laufe durch alle Argumente .. */
        for (int i = 1; i < argc; i++) {

			/* .. pruefe, ob das aktuelle Argument irgendwo eine Zahl enthaelt .. */
            if (hatZahl(argv[i], strlen(argv[i])))
                printf("%d ", atoi(argv[i])); /* .. und wandle die Zeichenkette in eine Zahl um. */
        }

    }

    printf("\n");

    return 0;
}