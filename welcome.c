#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>


/**void gotoxy(int x, int y) {
    COORD coord;

    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}**/

void loading(){
	system("cls");
    system("color F1");

		gotoxy(30,9); printf("              =======================");
		gotoxy(30,10);printf("               MOHON TUNGGU SEBENTAR");
		gotoxy(30,12);printf("              =======================");

		Sleep(500);
		gotoxy(30,11);printf("                     . ");
		Sleep(500);
		printf(". ");
		Sleep(500);
		printf(". ");
		Sleep(500);
		printf(". ");
		Sleep(500);
		printf(". ");
}

int pilihanLoginWelcome(){
    int key = 1, status = 1;
    int selectedOption = 1, submenuOption = 0;

    while(status == 1)
    {
        do {
            gotoxy(30,2);printf("=================SELAMAT DATANG DI CRYPTFESS=================\n");
                // display the main menu
                gotoxy(30,4);printf("[%c]Login\n", (selectedOption == 1) ? 'x' : ' ');
                gotoxy(30,5);printf("[%c]Registrasi\n", (selectedOption == 2) ? 'x' : ' ');
                gotoxy(30,6);printf("[%c]Exit\n", (selectedOption == 3) ? 'x' : ' ');

                key = getch();
                // Handle arrow key input for the main menu
                switch (key) {
                    case 72:  // Up arrow key
                        selectedOption = (selectedOption > 1) ? selectedOption - 1 : 3;
                        system("cls");
                        break;
                    case 80:  // Down arrow key
                        selectedOption = (selectedOption < 3) ? selectedOption + 1 : 1;
                        system("cls");
                        break;
                    case 13:  // Enter key
                        return selectedOption;
                        break;
                    default:
                        // Ignore other keys
                        break;
                }
            }while (key != 13);  // 13 is the ASCII code for Enter key
    }

            // Clear the console screen (for Windows) - Moved outside of the submenu loop
            // system("cls");

        if (submenuOption == 0) {
            printf("Exiting...\n");
        }
    return 0;
}

