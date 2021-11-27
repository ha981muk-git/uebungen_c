/* Zweck:	p04c - Bewertungsaufgabe zu Funktionen und Rekursion
*  Autor:	Robin Freund & Marcel Transier (dok. David Lüdtke)
*  Datum:	06.11.2019 (zul. 07.11.2019)
*  Hinweis:	Wir schreiben u.U. ausfuehrlichere/redundantere Kommentare als ihr es muesst/sollt.
*		Das dient teilweise rein zur Veranschaulichung, ihr muesst z.B. ueber eine
*		Addition nicht schreiben, dass es eine Addition ist. Schreibt hier eher,
*		warum ihr addiert - wenn es nicht selbstverstaendlich ist.
*/

#include <stdbool.h>	//Damit bool benutzt werden kann
#include <stdio.h>

/* Funktion zur Überprüfung, ob es sich bei der übergebenen Zahl um eine Primzahl handelt */
bool isPrim(int zahl) {
	
	// Der Aktuelle Teiler mit dem überprüft wird, ob eine
	// restlose Division möglich ist
    static int teiler = 2;

	// Rekursion-Abbruch, ab diesem Punkt gibt es keine sinnvollen Teiler mehr
    if (teiler > zahl/2) {
        teiler = 2; 			// Da der Teiler static ist muss er hier, für den nächsten
								// Funktionsaufruf, auf 2 zurückgesetzt werden
        return zahl > 1; 		// 1 ist keine Primzahl, alles andere was bis hier kommt schon
    }

	//Test, ob die übergebene Zahl mit dem aktuellen Teiler restlos teilbar ist
    if (zahl % teiler == 0) {
        teiler = 2;				// Da der Teiler static ist muss er hier, für den nächsten
								// Funktionsaufruf, auf 2 zurückgesetzt werden
        return false;			// Da die übergebene Zahl restlos teilbar ist wird
								// false zurückgegeben -> Keine Primzahl
    } else {
        teiler++;				// Der Teiler wird erhöht und die Funktion ruft sich
								// erneut mit der gleichen Zahl auf da der Teiler
								// static ist, ist dieser trotzdem im nächsten Durchlauf erhöht
        return isPrim(zahl);
    }
}

/* 	Funktion zur Zerlegung einer Zahl in ihre Primfaktoren.
	Die Primfaktoren werden auf der Konsole ausgegeben.
	Übergeben wird die Zahl, sowie der aktuelle Teiler, welcher
	initial 2 betragen soll. */
void doPFZ(int zahl, int teiler) {
	
	// Wenn die übergebene Zahl bereits eine Primzahl ist, wird diese einfach ausgegeben
    if (isPrim(zahl)) {
        printf("%d\n", zahl);
        return;
    }
	
	// Wenn die aktuelle Zahl restlos durch den aktuellen Teiler teilbar ist und der aktuelle
	// Teiler eine Primzahl ist wurde eine neuer Primfaktor gefunden. Die Funktion ruft sich
	// danach selbst auf, mit der, durch den Teiler geteilten, Zahl und dem gleichen Teiler.
    if (isPrim(teiler) && zahl % teiler == 0) {
        printf("%d, ", teiler);
        return doPFZ(zahl/teiler, teiler);	// Integer Division ist hier nicht relevant, da vorher
											// überprüft wurde, ob die Zahl restlos teilbar ist
    }
	
    return doPFZ(zahl, teiler+1);			// Es konnte nicht restlos geteilt werden oder der Teiler
											// ist keine Primzahl -> Teiler wird um 1 erhöht
}

int main() {

    int max = 0, i = 0, pfz = 0;
    
	// Obergrenze wird eingelesen
    printf("Geben Sie bitte eine Obergrenze an: ");
    scanf("%d", &max);    

    // Aufgabe a) - Primzahlenpaare werden ausgegeben
    for (i = 2; i < max; i++) {
        if (isPrim(i) && isPrim(i + 2)) {	// Nur wenn die aktuelle Zahl und (aktuelle Zahl + 2)
            printf("(%d %d) ", i, i + 2);	// Primzahlen sind, werden diese ausgegeben
        }
    }
        
    printf("\n");
    
    printf("Ab hier kommen Sophie-Germain-Primzahlen:\n");
    
	// Aufgabe b) - Sophie-Germain-Primzahlen ausgeben von 2 bis max
    for (i = 2; i < max; i++) {
        if (isPrim(i) && isPrim((2 * i) + 1)) {	// Nur wenn die aktuelle Zahl und (2 * aktuelleZahl + 1)
            printf("%d ", i);					// Primzahlen sind, wird die aktuelle Zahl ausgegeben
        }
    }
    
    printf("\n");
    
	// Aufgabe c) - Primfaktorzerlegung
	
	// Zahl für die Primfaktorzerlegung wird eingelesen
    printf("Bitte geben Sie eine Zahl für die Primfaktorzerlegung ein: ");
    scanf("%d", &pfz);
    
	// Die Funktion doPFZ() schreibt die zugehörigen Primfaktoren direkt in den stdout
    printf("Die Faktoren sind: ");
    doPFZ(pfz, 2);

    return 0;
}
