
#include <stdio.h>

char solmi(char num){  

    

     switch (num)
     {
     case '1': printf(" doe ==> do \n");
         break;        
     case '2':printf(" re ==> re \n");
         break;
     case '3':printf(" mi ==> mi \n");
         break;
     case '4':printf(" fa ==> fa \n");
         break;
     case '5':printf(" sol ==> sol \n");
         break;    
     case '6':printf(" la ==> la \n");
         break;    
     case '7':printf(" si ==> si \n");
         break; 
     default:
         break;
     }

     return num;

}
enum zeichenList { doe = 1, re, mi, fa, sol, la, si };

int main() {

    

    char zeichen;
    do
    {
        
        zeichen = getchar();

        zeichen = solmi(zeichen);
       
        putchar(zeichen);


    }while(zeichen != EOF);


    return 0;
}