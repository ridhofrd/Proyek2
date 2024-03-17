#include <stdio.h>
#include <stdlib.h>


int checkContinue(){
    char terminator, status;
    scanf("%c", &terminator);
    scanf("%c", &status);
    scanf("%c", &terminator);


    if(status == 'Y' || status == 'y')
        return 0;
    else
        return 1;

}
