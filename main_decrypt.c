/* File		 : main_decrypt.c									*/
/* Deskripsi : Driver untuk menggunakan unit ADT method decrypt
			   yang ada di decrypt.h dan method_decrypt.c		*/

#include <stdio.h>
#include <stdlib.h>
#include "decrypt.h"

/****** START ADD ON MENU DEKRIPSI ******/
int mainOpsi3(char *username) {
    system("cls");
    char nama_user[50];
    char filename[100];
    //	  nanti pakai ini untuk mengambil session sesuai dengan nama user
	strcpy(filename, username);
	strcat(filename, ".txt");
    int lineCount = countLinesInFile(filename);
        int keyboard = 1, status = 1, statusExit = 0;
    int selectedOption = 1, submenuOption = 0;

    while(status == 1)
    {
        do {
            gotoxy(30,9);printf("=================Beranda Pengguna=================\n");
            gotoxy(30,10);printf("-------------Terdapat %d Pesan Masuk--------------\n", lineCount);
                // display the main menu
                gotoxy(30,12);printf("[%c]Daftar Pesan Masuk\n", (selectedOption == 1) ? 'x' : ' ');
                gotoxy(30,13);printf("[%c]Keluar dari Beranda Pengguna\n", (selectedOption == 2) ? 'x' : ' ');
                keyboard = getch();
                // Handle arrow key input for the main menu
                switch (keyboard) {
                    case 72:  // Up arrow key
                        selectedOption = (selectedOption > 1) ? selectedOption - 1 : 2;
                        system("cls");
                        break;
                    case 80:  // Down arrow key
                        selectedOption = (selectedOption < 2) ? selectedOption + 1 : 1;
                        system("cls");
                        break;
                    case 13:  // Enter key
                        status = 0;
                        break;
                    default:
                        // Ignore other keys
                        break;
                }
            }while (keyboard != 13);  // 13 is the ASCII code for Enter key
    }

            // Clear the console screen (for Windows) - Moved outside of the submenu loop
        system("cls");

        if (submenuOption == 0) {
            printf("Exiting...\n");
        }

	system("cls");

    while(statusExit == 0){
        switch (selectedOption) {
                case 1:
                    clearScreen();
                    viewDecryptionKeyAndMessage(nama_user, filename);
                    break;
                case 2:
                    clearScreen();
                    printf("Ke Menu Utama.\n");
                    return 1;
                default:
                    printf("Pilihan tidak valid. Silakan coba lagi.\n\n");
            }
        printf("Apakah anda ingin melihat pesan yang lain?(Y\\n)");
        char terminator;
        scanf("%c", &terminator);
        statusExit = checkContinue();
    }
    system("cls");
    return 0;
}
/****** END ADD ON MENU DEKRIPSI ******/
