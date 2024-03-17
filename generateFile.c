#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void mainCreateFile(char username[]){
    char usernameCF[100];
    strcpy(usernameCF, username);
    strcat(usernameCF,".txt");
    FILE *newFile = fopen(usernameCF, "w");
}
