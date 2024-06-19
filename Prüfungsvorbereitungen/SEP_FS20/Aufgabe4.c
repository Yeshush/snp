#include <stdio.h>
#include <stdlib.h>

int main(void){
int *pi1, *pi2, i;

i= 2;
pi1 = pi2 + i;
pi1 = i + pi2;
printf("\n%d", pi1);
//i = pi1 * pi2;
i = pi1 - pi2;
printf("\n%d", i);
}