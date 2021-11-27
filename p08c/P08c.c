/* Name: Übung p08c - Zeigerarithmetik und Zufallszahlen
 * Autor: Marc Pekoua
 * Datum: 12.05.2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ANZ 1000

void init(int * int_array, int anzahl_elemente){
	int i = 0;
	for(i = 0; i<anzahl_elemente; i++){
		*(int_array + i) = (rand()%9999) + 1;		//Initialierung mit rand, Zahl zwischen 1 und 9999
	}
}

void ausgabe(int * int_array, int anzahl_elemente){
	int i = 0;
	for(i = 0; i<anzahl_elemente; i++){
		if(i !=0 && i%10 == 0)				//Generieren von 10 Spalten
			printf("\n");
		printf("%5i", *(int_array + i));	//Ausgabe mit 5 Stellen
	}
	printf("\n");
}

//tausche nimmt 2 Zeiger entgegen und vertauscht die Werte, die drin sind
void tausche(int * zahl1, int * zahl2){
	int help = *zahl1;
	*zahl1 = *zahl2;
	*zahl2 = help;
}

//Einsatz des Bubblesort-Algorithmus 
void sortiere(int * int_array, int anzahl_elemente){
	for(int n = anzahl_elemente; n>1; n--){
		for(int i = 0; i<n-1; i++){
			if(*(int_array+i) > *(int_array+i+1))
				tausche(int_array+i,int_array+i+1);
		}	
	}
}

int * mini(int * int_array, int anzahl_elemente){
	int i = 0;
	int * position = int_array;				// Hilfsvariable zur Bestimmung des kleinsten Wertes
	for (i = 0; i < anzahl_elemente; i++){
		if (*position > *(int_array+i)){	
			position = (int_array+i);	// Kleinster Wert und die Stelle wird in temporärer Variablen gespeichert
		}
	}

	return position;	// Die gefundene Stelle in dem Array wird zurueckgegeben
}

int * maxi(int * int_array, int anzahl_elemente){
	int i = 0;
	int * position = int_array;	
	for (i = 0; i < anzahl_elemente; i++){
		if (*position < *(int_array+i)) {	// großter Wert und die Stelle wird in temporärer Variablen gespeichert
			position = (int_array+i);
		}
	}

	return position;		// Die gefundene Stelle in dem Array wird zurueckgegeben
}

int median(int * int_array, int anzahl_elemente){
	int median = 0;
	sortiere(int_array, anzahl_elemente);
	if (anzahl_elemente % 2 == 0) { 	// wenn die Anzahl an Elementen eine gerade Zahl ist, ist der Median die Summe der Werte in der Mitte durch 2
		median = (*(int_array + (anzahl_elemente/2)-1) + *(int_array + (anzahl_elemente/2)))/2;
	}
	else {								// wenn die Anzahl an Elementen eine ungerade Zahl ist, ist der Median der Wert in der Mitte
		median = *(int_array + (anzahl_elemente/2));
	}

	return median;
}

//Hauptprogramm und Funktionaufrufe
int main(){

	int myarray[ANZ];

	srand(time(NULL));
	init(myarray, ANZ);
	printf("Ausgabe vor der Sortierung\n");
	ausgabe(myarray, ANZ);
	sortiere(myarray, ANZ);
	printf("Ausgabe nach der Sortierung\n");
	ausgabe(myarray, ANZ);

	printf("\n Min : %i\n", *(mini(myarray, ANZ)));
	printf("\n Max : %i\n", *(maxi(myarray, ANZ)));
	printf("\n Median : %i\n", median(myarray, ANZ));

	return 0;
}
