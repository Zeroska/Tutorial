#include <stdio.h>


void some_function(int number){
    printf("Is this your number: %d\n",number);
}



int main(){
    //this is working dude 
    void (*foo)(int) = &some_function;
    foo(100);
    (*foo)(200);
    return 1;
}