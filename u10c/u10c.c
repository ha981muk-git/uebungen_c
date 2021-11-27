/*
 * Zweck: u10a - Hausaufgabe: Verkettete Liste Stau (NSA)
 * Autor: Robin Freund (dok. David Lüdtke)
 * Datum: 27.11.2019, gekuerzt am 02.06.2020
 */

#include <stdio.h>	//Für I/O
#include <stdlib.h>	//Für malloc()
#include <string.h>	//Für string-Funktionen

//Define für einen Null-Container Element (für das Ende der verketteten Liste)
#define NIL (struct Container *)0

//Struktur für ein Fahrzeug
struct Fahrzeug {
    char hersteller[30];
    char modell[30];
    char kennzeichen[30];
    int anzPersonen;
};

//Verkettete Liste. Container ist jeweils ein Element der verketteten Liste.
//Es beinhaltet den "Payload" der Liste (ein Fahrzeug) und einen Zeiger auf das nächste Listenelement
//Falls das aktuelle Element das letzte Element der Liste ist, soll dieser Zeiger auf NIL zeigen (siehe oben)
struct Container {
    struct Fahrzeug fz;
    struct Container *next;
};

//Eine Funktion zum Anhängen von Container-ELementen an die verkettete Liste
//Die Funktion erhält als Parameter einen Zeiger auf einen Zeiger auf das Erste Element
//Dieser wird benötigt, damit der Zeiger in der main auf ein neues Element gelenkt werden kann
void anhaengen(struct Container ** first_ptr) {

    //Zuerst wird der first_ptr auf das next des letzten vorhandenen Elements der Liste gezeigt
    while ((*first_ptr) != NIL) {
        first_ptr = &((*first_ptr)->next);
    }
    
    //Das aktuell ausgewählte Element zeigt noch auf NIL. Es muss ein neuer Speicherbereich für
    //Die Strukur reserviert werden (mit malloc). Als Parameter erhält malloc die Größe der Container-
    //Struktur, damit mindestens dieser Speicher auch für dieses Element reserviert werden kann.
    *first_ptr = (struct Container *)malloc(sizeof(struct Container));

    //Das next-Element soll auf NIL zeigen, um das neue Ende der Liste anzuzeigen
    (*first_ptr)->next =NIL;
    
    //Die neuen Werte für die Fahrzeugstruktur werden eingelesen
    printf("> Fahrzeughersteller: ");
    scanf(" %s", (*first_ptr)->fz.hersteller);
    
    //Statt %s wird hier [^\n] verwendet, welches verhindert, dass scanf bei einem Leerzeichen abbricht
    printf("> Fahrzeugmodell: ");
    scanf(" %[^\n]", (*first_ptr)->fz.modell);
    
    printf("> Kennzeichen: ");
    scanf(" %[^\n]", (*first_ptr)->fz.kennzeichen);
    
    printf("> Personenzahl: ");
    scanf("%i", &((*first_ptr)->fz.anzPersonen));
}

//Eine Funktion zum anzeigen der verketteten Liste
//Der übergebene Parameter ist ein Zeiger auf das erste Element der verketteten Liste
void anzeigen(struct Container * con) {

    //Wenn der Zeiger auf NIL zeigt gibt es keine Elemente
    if (con == NIL) {
        printf("> Es gibt keinen Stau hier.\n");
        return;
    }
    
    //Bis zum Ender der Liste (con == NIL) wird jedes Fahrzeug ausgegeben
    do {
        printf("> Modell %s von %s mit Kennzeichen %s und %d Personen\n",
                con->fz.modell, con->fz.hersteller,
                con->fz.kennzeichen, con->fz.anzPersonen);
                
	//Das aktuelle Element wird für den nächsten Schritt auf den Nachfolger gesetzt
        con = con->next;
    } while (con != NIL);
}

//Eine Funktion zum ausklinken eines Elementes aus der verketteten Liste
//Das auszuklinkende Element wird mittels Kennzeichen bestimmt und, sofern vorhanden,
//zurückgegeben (damit es in der main() gespeichert werden kann um es wieder einzuklinken.
//Übergeben wird ein Zeiger auf einen Zeiger auf das erste Element der Liste
struct Container * ausklinken(struct Container ** con) {
	
    //Das Element, welches in der Liste vor dem aktuellen Element liegt
    struct Container * vorher = NIL;

    //Einlesen eines Kennzeichens zur Identifikation des korrekten Fahrzeugs
    char kennzeichen[30];
    printf("Kennzeichen: ");
    scanf(" %[^\n]", kennzeichen);
    
    //Solange nicht das Ende der Liste erreicht ist (*con == NIL) wird überprüft, ob das
    //Element mit dem angegebenen Kennzeichen gleich dem aktuellen Element ist
    while (*con != NIL) {
		//gesuchtes Kennzeichen == Kennzeichen vom aktuellen Element
        if (!strcmp((*con)->fz.kennzeichen, kennzeichen))
        {
	    //1. Fall: Es soll das 1. Element der Liste ausgeklinkt werden (kein Vorgänger)
            if (vorher == NIL) {
		
		//Das Element wird ausgeklinkt: Das aktuelle Element wird auf das 2. Element
		//gesetzt und das 1. Element wird returnt
                struct Container * first = *con;
                *con = (*con)->next;
                return first;                
            } else {
		//Das Element wird ausgeklinkt: Das vorherige Element wird auf das nächste Element
		//(aus Sicht des aktuellen Elements) gesetzt und das aktuelle Element wird returnt
                struct Container * first = *con;
                (*vorher).next = (*con)->next;
                return first;
            }
        }

	//aktuelles Element (con) ist nicht unser gesuchtetes auszuklinkendes Element:
	//1. Das aktuelles Element wird als neues vorheriges Element gesetzt
	//2. Das neue aktuelle Element ist der Nachfolger (next) vom aktuellen Element
        vorher = *con;
        con = &((*con)->next);
    }    
        
    //Falls das Element (mit dem gesuchten Kennzeichen) nicht gefunden werden kann wird NIL returnt 
    return NIL;
}

//Eine Funktion zum wieder-einklinken eines Elements in die verkettete Liste
//Übergeben wird ein Zeiger auf einen Zeiger auf das Startelement der Liste und
//das vorher ausgeklinkte Element, welches eingeklinkt werden soll
void einklinken(struct Container ** con, struct Container * ausgeklinkt) {

    //Einlesen eines Kennzeichens zur Identifikation des korrekten Fahrzeugs
    //nach dem eingefügt werden soll
    char kennzeichen[30];
    printf("Kennzeichen: ");
    scanf(" %[^\n]", kennzeichen);
    
    //Schleife, die durch alle Listenelemente durchgeht und nach dem gesuchten
    //Kennzeichen das vorher ausgeklinkte Element wieder einfügt
    while (*con != NIL) {
        if (!strcmp((*con)->fz.kennzeichen, kennzeichen))
        {
	    //Die Variable Con wird mit einem Zeiger auf einen Zeiger auf das nächste Element überschrieben
            con = &((*con)->next);
            break;
        }
    }
	
    //Das vorherige Element, welches aktuell in con gespeichert ist wird nun in vorher gespeichert
    //Das aktuelle Element zeigt nun auf ausgeklinkt und der next-Zeiger des Elements auf das vorherige
    //Element
    struct Container * vorher = *con;
    *con = ausgeklinkt;
    ausgeklinkt->next = vorher;
}

int main() {
    
    //Zeiger auf die verkettete Liste (bzw. das erste Element der verketteten Liste): Zeigt beim Start
    //zuerst auf NIL
    struct Container * first = NIL;
    
    //Speicher für das zuletzt ausgeklinkte Element, um es wieder einzuklinken
    struct Container * ausgeklinkt = NIL;
    
    //Menüausgaben, die für eine gute Usability sorgen
    printf("=== Es herrscht Stau. Du kannst jetzt wählen .. ===\n");
    printf("A(n)haengen: Fuege dem Stau ein Auto hinzu\n");
    printf("An(z)eigen: Zeige alle Autos im Stau an\n");
    printf("Ein(k)linken: Klinke ein ausgeklinktes Auto wieder ein\n");
    printf("A(u)sklinken: Klinke ein Auto aus der Liste aus\n");
    
    char auswahl = '\0';
    
    //Bei der Eingabe 'x' oder EOF wird das Programm beendet, andernfalls kommt der Benutzer wieder
    //in die Menüauswahl. Je nach Menüpunkt wird die entsprechende Funktion aufgerufen
    while (auswahl != EOF && auswahl != 'x') {
        printf("Aktion waehlen: ");
        scanf(" %c", &auswahl);
        
        if (auswahl == 'n') {
            anhaengen(&first);            
        } else if (auswahl == 'z') {
            anzeigen(first);
        } else if (auswahl == 'k') {
            einklinken(&first, ausgeklinkt);
        } else if (auswahl == 'u') {
	    //Der ausgeklinkte Eintrag wird in der Variable ausgeklinkt gespeichert, um wieder
	    //eingeklinkt zu werden
            ausgeklinkt = ausklinken(&first);
        }
    }
}
