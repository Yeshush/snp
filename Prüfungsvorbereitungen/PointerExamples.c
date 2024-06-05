// Online C compiler to run C program online
#include <stdio.h>

void printSpace(){
     printf("--------------------\n");
}

int main() {
    printSpace();
    int num = 5;
    char string[]="Hello World!";
    
    typedef struct {
        char name[20];
        int age;
    } Person;
    
    Person person = {"Jean Pierre", 300};
    
    printf("num = %d\n", num); 
    printf("string = %s\n", string);

    printSpace();
    int *pointerNum = &num;
    
    //Address Examples for Int:
    printf("pointerNum Address Values = %p\n", pointerNum); 
    //Value Examples for Int: 
    printf("pointerNum int Values = %d\n", *pointerNum);
    
    printSpace();
    char (*pointerString)[]=&string;
    
    //Address Examples for String: 
    printf("pointerString Address Values = %p\n", pointerString);
    //Value Examples for String:
    printf("pointerString String Values = %s\n", *pointerString);
    
    
    printSpace();
    Person *pointerStruct = &person;
    
    //Address Examples for Struct: 
    printf("pointerStruct Address Values = %p\n", pointerStruct);
    //Value Examples for Struct: 
    printf("pointerStruct Struct Values = (%s;%d)\n", pointerStruct->name, pointerStruct->age);
    
    
    printSpace();
    void *genericPointerStruct = &person;
    //Address Examples for Generic Struct: 
     printf("genericPointerStruct Address Values = %p\n", genericPointerStruct);

    //Generic Value Example for Struct:
     printf("genericPointerStruct Struct Values = (%s;%d)\n", ((Person*)genericPointerStruct)->name, ((Person *)genericPointerStruct)->age);

    printSpace();
    return 0;
}