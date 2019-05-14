#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./lib/controller/config.h"
#include "./lib/controller/state.h"
#include "./lib/view/printScreen.h"
#include "./lib/model/snake.h"
 

int main(){
    system("clear"); 
    system("stty -echo");
    gotoxy(5, 5);
    printf("A");
    sleep(1);
    gotoxy(5, 5);
    printf(" ");
    sleep(1);
     printf("B");
    

}