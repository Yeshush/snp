#include <stdio.h>
#include <stdlib.h>

int main(void){
    int *pi1, *pi2, i;
    printf("\nAdresse pi1 =>%p", pi1);
    printf("\nAdresse pi2 =>%p", pi2);
    i= 2;
    pi1 = pi2 + i;
    pi1 = i + pi2;
    printf("\nAufgabe a =>%p", pi1);
    i = pi1 - pi2;
    printf("\nAufgabe d =>%d", i);




    /*pi1 = i + pi2;
    printf("\nAufgabe b =>%d", pi1);
    //i = pi1 * pi2;
    i = pi1 - pi2;
    printf("\nAufgabe d =>%d", i);*/
}