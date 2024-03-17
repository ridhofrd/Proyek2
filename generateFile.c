#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void mainCreateFile(char *username){
    strcat(username,".txt");
    FILE *newFile = fopen(username, "w");
}
