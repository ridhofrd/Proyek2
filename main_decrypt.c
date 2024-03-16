/* File		 : main_decrypt.c									*/
/* Deskripsi : Driver untuk menggunakan unit ADT method decrypt
			   yang ada di decrypt.h dan method_decrypt.c		*/

#include <stdio.h>
#include <stdlib.h>
#include "decrypt.h"

/****** START ADD ON MENU DEKRIPSI ******/
int main() {
    char nama_user[50];
    const char *filename = "Nematoda-Nematoda.txt";
    //	  nanti pakai ini untuk mengambil session sesuai dengan nama user
	//    strcat(filename, username);
	//    strcat(filename, ".txt"); 
    int lineCount = countLinesInFile(filename);
    int choice;
    while (1) {
        printf("========== ADA %d JUMLAH PESAN MENFESS MASUK ===========\n", lineCount);
        printf("=======================================================\n");
        printf("1. Daftar Pesan Masuk\n");
        printf("2. Kembali Ke Menu Utama\n");
        printf("=======================================================\n");
        printf("PILIHAN OPSI : ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
            	clearScreen();
                viewDecryptionKeyAndMessage(nama_user);
                break;
            case 2:
            	clearScreen();
                printf("Ke Menu Utama.\n");
                return 0;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n\n");
        }
    }
    return 0;
}
/****** END ADD ON MENU DEKRIPSI ******/