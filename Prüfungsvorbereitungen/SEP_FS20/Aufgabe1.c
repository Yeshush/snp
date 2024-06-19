#include <stdio.h>
#include <stdlib.h>

void inverse(char * const);

int main(void){
    char c[] = "SEPFS16";
    char *p = c;
    (void) printf("\n%lu", sizeof(c)); 
    (void) printf("\n%c", p[0]);
    (void) printf("\n%d", p[0] - p[2]); 
    (void) printf("\n%s", p + p[0] - p[2]); inverse(p);
    (void) printf("\n%s", p);
return EXIT_SUCCESS;
}