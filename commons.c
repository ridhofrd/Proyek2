#include <stdio.h>
#include <stdlib.h>

//#include "modul.h"

#define TEXT_MAX 100

void printDivider(){
	printf("\n=======================================================================\n");
}

void printSeparator(char title[TEXT_MAX]){
	printDivider();
	printf("\t%s", title);
	printDivider();
}

