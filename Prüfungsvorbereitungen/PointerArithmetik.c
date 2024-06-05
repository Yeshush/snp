// Online C compiler to run C program online
#include <stdio.h>

int main() {
    int array [10]= {0,1,2,3,4,5,6,7,8,9};
    int *ptr;
    //Bezieht sich auf Index: Verschiebt Index
    ptr = &array[1] +2;
    printf("%d", *ptr);
    return 0;
}