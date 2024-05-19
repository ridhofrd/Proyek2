/* File		 : main_decrypt.c									*/
/* Deskripsi : Driver untuk menggunakan unit ADT method decrypt
			   yang ada di decrypt.h dan method_decrypt.c		*/

#include <stdio.h>
#include <stdlib.h>
#include "decrypt.h"

/****** START ADD ON MENU DEKRIPSI ******/
int main(char *username[]) {
    char nama_user[50];
    username = "Nematoda-Nematoda";
    char filename[100];
    sprintf(filename, "%s.txt", username);
    NodeBinary *root = loadBinaryMessagesFromFile(filename);
    if (root == NULL) {
        printf("Failed to load messages from file.\n");
        return 1;
    }

    MessageNode *messageList = loadMessagesFromFile(filename);
    if (messageList == NULL) {
        printf("Tidak ada pesan yang dapat dimuat.\n");
        return 1;
    }

    int lineCount = countLinesInFile(filename); // Jika masih menggunakan fungsi ini
    int unreadCount = countUnreadMessages(messageList);
    int choice;

    while (1) {
        printf("============= ADA %d JUMLAH PESAN MENFESS ==============\n", lineCount);
        printf("=======================================================\n");
        printf("1. Daftar Pesan Masuk\n");
        printf("2. Kembali Ke Menu Utama\n");
        printf("3. %d Pesan Belum Dibaca\n", unreadCount);
        printf("4. Hapus Pesan\n");
        printf("=======================================================\n");
        printf("PILIHAN OPSI : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                clearScreen();
                    messageList = loadMessagesFromFile(filename);
                viewDecryptionKeyAndMessage(nama_user, messageList, filename); // Modifikasi untuk menerima linked list
                break;
            case 2:
                clearScreen();
                printf("Ke Menu Utama.\n");
                return 0;
            case 3:
                clearScreen();
                    messageList = loadMessagesFromFile(filename);
                viewDecryptionKeyAndMessageUnRead(nama_user, messageList, filename);
                break;
            case 4:
                clearScreen();
				processMessages(root, filename);
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n\n");
        }

        unreadCount = countUnreadMessages(messageList);
    }

    return 0;
}
/****** END ADD ON MENU DEKRIPSI ******/
