/* Zweck: u10a - Aufgabe zu verketteten Listen
 * Datum: 26.05.2020
 * Autor: Robin Freund und Luca Chiarelli
 * Hinweis: Wir schreiben hier u.U. *deutlich* ausfuehrlichere/redundantere Kommentare als ihr es muesst/sollt.
 *          Das dient teilweise rein zur Veranschaulichung bei den ersten Uebungen.
 *          Ihr muesst z.B. ueber eine Ausgabe nicht schreiben, dass es eine Schleife ist. Schreibt hier eher,
 *          wie die Schleife funktioniert - wenn es nicht selbstverstaendlich ist. Das selbe Prinzip bei Schleifen, Ausgaben,
 *          Funktionsaufrufen.
 * 
 * Erweiterung: Dem Programm Gespraechsrunden hinzufügen mit der möglichkeit neue Gespraechsrunden zu starten - 
 *              Dabei sollen die Tischnummern der Teilnehmer fuer jeden Durchgang gespeichert werden damit man sie 
 *              später wieder aufrufen kann. Bei der normalen Ausgabe soll die Tischnummer eines jeden Durchgangs 
 *              ausgegeben werden.        
 */

#define NIL (struct node *) 0
#define ANZTISCHE 4

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct teilnehmer {
    char vorname[20];
    char nachname[20];
    char beruf[20];
    int anzGespraeche;                  /* Anzahl durchgeführter Runden */ 
    int tischNr[5];
};

struct node {
    struct teilnehmer teiln;
    struct node * naechstesElement;
};

/* Funktion zum Anlegen eines neuen Elementes
 * Vorgehen:
 * - Definieren des Zeigers, den wir später auf neu, von malloc zurückgegebenen, freien Speicher richten
 * - Mit malloc genau so viel Speicher allokieren, dass der Containerknoten und den kompletten Inhalt in den freigemachten
 *   Speicher passt
 * - Zeichenketten und Tischnummer in die Datenstruktur innerhalb des Containers kopieren
 * - "Naechster-Zeiger" des vorherigen Elementes auf das eben neu erzeugte Element richten
 * - "Naechster-Zeiger" des neuen Elementes auf NIL setzen um zu signalisieren, dass darauf kein Element mehr folgt
 * - Zeiger auf den neuen Containerknoten zurueckgeben
 */
struct node * newElement(char * vorname, char * nachname, char * beruf, int tischNr, struct node * vorherigesElement) {

    struct node * hilfsZeiger;

    /* - Definieren des Zeigers, den wir später auf neu, von malloc zurückgegebenen, freien Speicher richten */
    hilfsZeiger = (struct node *) malloc(sizeof(struct node));

    /* Kopieren der Daten */
    strncpy(hilfsZeiger->teiln.vorname, vorname, sizeof(hilfsZeiger->teiln.vorname));
    strncpy(hilfsZeiger->teiln.nachname, nachname, sizeof(hilfsZeiger->teiln.nachname));
    strncpy(hilfsZeiger->teiln.beruf, beruf, sizeof(hilfsZeiger->teiln.beruf));

    hilfsZeiger->teiln.tischNr[0] = tischNr;
    hilfsZeiger->teiln.anzGespraeche = 1;           /* Initialisiert die erste Runde, 0 für den Index */ 

    /* "Naechster-Zeiger" des vorherigen Elementes auf das eben neu erzeugte Element richten */
    if (vorherigesElement != NIL) {
        vorherigesElement->naechstesElement = hilfsZeiger;
    }
        
    /* "Naechster-Zeiger" des neuen Elementes auf NIL setzen um zu signalisieren, dass darauf kein Element mehr folgt */
    hilfsZeiger->naechstesElement = NIL;

    /* Zeiger auf den neuen Containerknoten zurueckgeben */
    return hilfsZeiger;
}


/* Ausgabefunktion: Iterative Variante + Header
 * Die Ausgabefunktion bekommt hier den Anfang der Liste, gibt den Header aus und
 * geht dann in einer Schleife durch die verkettete Liste.
 * Vorgehen:
 * - Erster Aufruf mit erstem Element (aus der main()-Funktion)
 * - Schleife:
 * --- Prüfung, ob das aktuell betrachtete Element ein "echter" Knotenzeiger und nicht NIL, 
 *     also ein Verweis auf keinen weiteren Knoten ist
 * --- Wenn naechster Knoten existiert, diesen ausgeben und den Hilfszeiger auf das naechste Element setzen
 * --- Wenn naechster Knoten nicht existiert, Schleife ohne weitere Ausgabe abbrechen
 * - Zeilenumbruch ausgeben und Funktion beenden 
 */
void ausgabeIterativ(struct node * element) {

    int runde = element->teiln.anzGespraeche;

    /* Kopf der Liste ausgeben */
    printf("==============================  Runde: %i  ========================================\n", runde);
    printf("%-20s %-20s %-20s %s\n", "Vorname", "Nachname", "Beruf", "TischNr");
    printf("==================================================================================\n");

    /* Ausgabeschleife: Durch die komplette verkettete Liste iterieren und jedes
     * Element ausgeben. */
    while (element != NIL) {
        printf("%-20s %-20s %-20s", 
            element->teiln.vorname, element->teiln.nachname, element->teiln.beruf);

        for(int i = 0; i < runde; i++)
        {
            printf(" %-2d", element->teiln.tischNr[i]);
        }
        printf("\n");
        element = element->naechstesElement;
    } 

    printf("\n");
}



/* Sortiert ausgeben: Nicht die Liste selbst sortieren, sondern nur eine sortierte Ausgabe sortieren! */
void ausgabeSortiert(struct node * startElement) {

    struct node * element;

    int runde = startElement->teiln.anzGespraeche;

    /* Kopf der Liste ausgeben */
    printf("==============================  Runde: %i  ========================================\n", runde);    
    printf("%-20s %-20s %-20s\n", "Vorname", "Nachname", "Beruf");
    printf("==================================================================================\n");

    /* Alle Tischnummern durchgehen .. */
    for (int i = 1; i <= ANZTISCHE; i++) {
        printf("Angezeigte Tischnummer: %d\n================\n", i);

        /* .. fuer jeden Schleifendurchgang den "Arbeitszeiger", also den Zeiger,
         * dessen Element ausgegeben und der danach ein Element weitergeschoben wird,
         * auf den Start zurücksetzen */
        element = startElement;

        while (element != NIL) {
            if (i == element->teiln.tischNr[runde - 1]) {
                printf("%-20s %-20s %-20s\n", 
                    element->teiln.vorname, element->teiln.nachname, element->teiln.beruf);
            }
            element = element->naechstesElement;
        } 
    }
    printf("\n");
}


void newRound(struct node * element)
{    
    int runde = element->teiln.anzGespraeche++;     /* post-inkrement, um anzGepraeche nach der Zuweisung inkrementiert wird */ 

    // printf("Runde: %i\n", runde);  /* Hilfsausgabe um zu gucken ob anzGespraeche inkrementiert wird */ 

    element->teiln.tischNr[runde] = rand() % 4 + 1;     /* Einen neuen zufaelligen Wert erstellen */ 

    if(element->naechstesElement != NIL)
       newRound(element->naechstesElement);             /* Rekursiv die verket.Liste ablaufen */ 
}


int main() {

    /* Zeiger, der ueber den gesamten Programmverlauf auf den Anfang unserer verketteten Liste zeigt */
    struct node * anfangsZeiger;

    /* Zeiger, der ueber den gesamten Verlauf auf das jeweils letzte (neu erstellte) Element zeigt */
    struct node * aktuellerZeiger;

    /* Speicher für Benutzereingabe im Auswahlmenue */
    char eingabe = '\0';

    printf("> Hallo sehr geehrter Benutzer!\n");
    printf("> Dieses Programm dient der Teilnehmerverwaltung eines Speed-Networking-Events.\n");
    printf("> Genauer gesagt: Der Teilnehmerliste _des_ Event des Jahres!\n");

    /* Initialisierung des Zufallszahlengenerators */
    srand(time(NULL));

    /* Erzeugung des Anfangs der verketteten Liste - gleichzeitig hier noch unser letztes Element */
    /* Der letzte Parameter gibt hier an, an welches vorherige Element das neue Element angehaengt werden soll.
     * newElement() gibt hierbei immer einen Zeiger auf das neue Element der Liste zurueck */
    anfangsZeiger = aktuellerZeiger = newElement("Heinz", "Hose", "Schneidermeister", (rand() % ANZTISCHE) + 1, NIL);

    /* Erzeugung der weiteren Listenelemente */
    aktuellerZeiger = newElement("Rudi", "Rohrfrei", "Wasserinstallateur", (rand() % ANZTISCHE) + 1, aktuellerZeiger);    
    aktuellerZeiger = newElement("Petra", "Planlos", "Architektin", (rand() % ANZTISCHE) + 1, aktuellerZeiger);    
    aktuellerZeiger = newElement("Armin", "Gips", "Stuntman", (rand() % ANZTISCHE) + 1, aktuellerZeiger);    
    aktuellerZeiger = newElement("Nora", "Notfall", "Nachtschwester", (rand() % ANZTISCHE) + 1, aktuellerZeiger);
    aktuellerZeiger = newElement("Stella", "Standup", "Fitnesstrainerin", (rand() % ANZTISCHE) + 1, aktuellerZeiger);

    /* Menueschleife */
    do {
        printf("==== Menueauswahl ====\n");
        printf("> Teilnehmerliste (a)nzeigen\n");
        printf("> Teilnehmerliste nach Tischen (s)ortiert anzeigen\n");
        printf("> Eine (n)eue Gespraechsrunde anfangen\n");
        printf("> Programm b(e)enden\n");

        printf("> Ihre Option: ");
        scanf(" %c", &eingabe);

        switch (eingabe) {
            case 'a':
            case 'A':
                ausgabeIterativ(anfangsZeiger);
                break;
            case 's':
            case 'S':
                ausgabeSortiert(anfangsZeiger);
                break;
            case 'n':
            case 'N':
                if(anfangsZeiger->teiln.anzGespraeche > 4)
                {
                    printf("\n\n\nKeine weiteren Runden mehr möglich!\n\n\n");
                    break;
                }
                newRound(anfangsZeiger);
                break;
            case 'e':
            case 'E':
                printf("Danke fuers Mitmachen!\n");
                break;
        }

    } while (eingabe != 'e' && eingabe != 'E');

    return 0;
}


/* Codecontainer */ 
#ifdef codeconatiner
/* Ausgabefunktion: Rekursive Variante
 * Die Ausgabefunktion kuemmert sich hierbei immer um _ein_ Element zur selben Zeit.
 * Vorgehen:
 * - Erster Aufruf mit erstem Element (aus der main()-Funktion)
 * - Ausgabe dieses Elementes
 * - Aufruf der Ausgabefunktion mit Nachfolger (element->naechstesElement)
 * - Wenn naechstes Element NIL, also nicht vorhanden: Abbrechen
 */
void ausgabe(struct node * element) {

    /* Abbruchbedingung: Wenn aktueller Knotenzeiger der "Nicht vorhanden"-Zeiger ist, Rekursion abbrechen*/
    if (element == NIL)
        return;
    
    printf("Vorname: %s, Nachname: %s, Beruf: %s, Tischnr: %d\n", 
            element->teiln.vorname, element->teiln.nachname, element->teiln.beruf, element->teiln.tischNr);

    /* Ausgabe des naechsten Elementes anstossen */
    ausgabe(element->naechstesElement);
}
#endif