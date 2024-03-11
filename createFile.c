#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


int mainCreateFile(char *usernameNew){
    FILE *ptr;
    char fileNew[100];
    sprintf(fileNew, "%s.txt", usernameNew);
    ptr = fopen(fileNew, "w");
    return 0;
}
