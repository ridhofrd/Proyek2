#include<stdio.h>
#include<stdlib.h>
#include"modul.h"

int mhsMenu(){
	/** kamus data **/
	int key = 1, status = 1;
    int selectedOption = 1, submenuOption = 0;

    while(status == 1)
    {
        do {
            gotoxy(30,2);printf("=================Menu Utama Pengguna=================\n");
                // display the main menu
                gotoxy(30,4);printf("[%c]Lihat Beranda Keseluruhan\n", (selectedOption == 1) ? 'x' : ' ');
                gotoxy(30,5);printf("[%c]Kirim Menfess\n", (selectedOption == 2) ? 'x' : ' ');
                gotoxy(30,6);printf("[%c]Lihat Beranda Pengguna\n", (selectedOption == 3) ? 'x' : ' ');
                gotoxy(30,7);printf("[%c]Logout\n", (selectedOption == 4) ? 'x' : ' ');

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

	/** proses **/
    return selectedOption;
}

/**void redirectMhsMenu(int pilihanMenu){
	 kamus data
	int isAdmin = 0;

	proses
	switch (pilihanMenu){
		case 1: {
			system("cls");
			printf("Data Menfess Tersedia\n");
			break;
		}
		case 2:{
			system("cls");
			printf("Menu Kirim Menfess\n");
			break;
		}
		case 3:{
			system("cls");
			printf("Menu Cek Menfess\n");
			break;
		}
		case 4:{
			system("cls");
			break;
		}
		default:{
			printSeparator("Input tidak tepat, mohon diulang.");
			system("pause");
			system("cls");
			mhsDashboard();
			break;
		}
	}
}**/


