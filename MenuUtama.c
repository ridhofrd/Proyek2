#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>


void gotoxy(int x, int y) {
    COORD coord;

    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void loadingMenu(){
	system("cls");
    system("color F1");

		gotoxy(30,9); printf("              =======================");
		gotoxy(30,10);printf("                MEMASUKI MENU UTAMA");
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

int pilihanLogin(){
    int key = 1, status = 1;
    int selectedOption = 1, submenuOption = 0;

    while(status == 1)
    {
        do {
            gotoxy(30,2);printf("=================Menu Utama=================\n");
                // display the main menu
                gotoxy(30,4);printf("[%c]Lihat Global Dashboard\n", (selectedOption == 1) ? 'x' : ' ');
                gotoxy(30,5);printf("[%c]Kirim Menfess\n", (selectedOption == 2) ? 'x' : ' ');
                gotoxy(30,6);printf("[%c]Check Menfess Masuk\n", (selectedOption == 3) ? 'x' : ' ');
                gotoxy(30,7);printf("[%c]Exit\n", (selectedOption == 4) ? 'x' : ' ');

                key = getch();
                // Handle arrow key input for the main menu
                switch (key) {
                    case 72:  // Up arrow key
                        selectedOption = (selectedOption > 1) ? selectedOption - 1 : 4;
                        system("cls");
                        break;
                    case 80:  // Down arrow key
                        selectedOption = (selectedOption < 4) ? selectedOption + 1 : 1;
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

int main(){
    loadingMenu();
    system("cls");
    pilihanLogin();
}
