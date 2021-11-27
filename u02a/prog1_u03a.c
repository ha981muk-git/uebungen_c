#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void spiel()
{  
   srand(time(NULL));
   for(int i=0;i<=1;i++)
   {
       spieler[i] = rand() % 5;
       return spieler[i];
   }

    for(int i=0;i<=1;i++){
    printf("Spieler%i : ",(i+1));
    switch (Spieler[i])
      {
    case 0 : printf("Stein");
            break;
    case 1 : printf("Schere");
            break;
    case 2 : printf("Papier");
            break;
    case 3 : printf("Echse");
            break;
    case 4 : printf("Spock");
             break;
   default:
       break;
     }
   printf("\n");
   }
   

   
   
}
int entscheid(int spieler[0],int spieler[1])
{

}
/*
int zaehlmit()
{

}

int auswert( int spieler[0],int spieler[1])
{

}


*/

int spieler[0];
int spieler[1];
int main()
{   
enum Spiel {Stein,Schere,Papier,Echse,Spock};  
spiel();
    return 0;
}