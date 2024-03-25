
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HayaQonita.h"

#define MAX_USERS 100

void viewAllMenfess(FILE *file);
void searchRecipient(FILE *file);
void viewStatistics(struct UserStats userStats[], int numUsers);

int mainDataMenfess() {
	FILE *file = fopen("DataMenfess.txt", "r");
    if (file == NULL) {
        printf("File tidak dapat dibuka.\n");
        return 1;
    }

    struct UserStats userStats[MAX_USERS];
    int i, numUsers = 0;

    // Inisialisasi userStats
    for (i = 0; i < MAX_USERS; i++) {
        userStats[i].username[0] = '\0';
        userStats[i].messageCount = 0;
    }

    int id;
    char date[100], from[100], to[100], message[100], method[100], key[100];

    // Hitung statistik untuk setiap pengguna
    while (fscanf(file, "%d, %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]", &id, date, to, from, method, key, message) != EOF) {
        // Hitung statistik untuk pengguna
        int userIndex = -1;
        for (i = 0; i < numUsers; i++) {
            if (strcmp(userStats[i].username, to) == 0) {
                userIndex = i;
                break;
            }
        }
        if (userIndex == -1) {
            // Pengguna baru, tambahkan ke statistik
            strncpy(userStats[numUsers].username, to, sizeof(userStats[numUsers].username) - 1);
            userStats[numUsers].messageCount = 1;
            numUsers++;
        } else {
            // Pengguna sudah ada, tingkatkan jumlah pesannya
            userStats[userIndex].messageCount++;
        }
    }

    int keyboard = 1, status = 1;
    int selectedOption = 1, submenuOption = 0;

    while(status == 1)
    {
        do {
            gotoxy(30,9);printf("=================Beranda Keseluruhan=================\n");
                // display the main menu
                gotoxy(30,11);printf("[%c]Lihat Seluruh Menfess\n", (selectedOption == 1) ? 'x' : ' ');
                gotoxy(30,12);printf("[%c]Cari Berdasarkan Penerima Pesan\n", (selectedOption == 2) ? 'x' : ' ');
                gotoxy(30,13);printf("[%c]Lihat Statistik\n", (selectedOption == 3) ? 'x' : ' ');
                gotoxy(30,14);printf("[%c]Keluar Dari Beranda Keseluruhan\n", (selectedOption == 4) ? 'x' : ' ');

                keyboard = getch();
                // Handle arrow key input for the main menu
                switch (keyboard) {
                    case 72:  // Up arrow key
                        selectedOption = (selectedOption > 1) ? selectedOption - 1 : 4;
                        system("cls");
                        break;
                    case 80:  // Down arrow key
                        selectedOption = (selectedOption < 4) ? selectedOption + 1 : 1;
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


        switch (selectedOption) {
            case 1:
                viewAllMenfess(file);
                break;
            case 2:
                searchRecipient(file);
                break;
            case 3:
                viewStatistics(userStats, numUsers);
                break;
            case 4:
                printf("Terima kasih!\n");
                return 1;
                break;
            default:
                printf("Opsi tidak valid. Silakan pilih opsi lain.\n");
        }

    fclose(file);
    return 0;
};

void viewAllMenfess(FILE *file) {
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("                                       DAFTAR SELURUH MENFESS                                         \n");
    printf("------------------------------------------------------------------------------------------------------\n");
	rewind(file);

    int id;
    char date[100], from[100], to[100], message[100], method[100], key[100];


	printf("-------------------------------------------------------------------------------------------------------\n");
	printf("|ID |            Waktu Kirim        |     Untuk      |      Dari      |      Pesan Ter-Enkripsi       |\n");
	printf("|---|-------------------------------|----------------|----------------|-------------------------------|\n");



    while (fscanf(file, "%d, %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]", &id, date, to, from, method, key, message) != EOF) {
        if (strcmp(method, "2") == 0 || strcmp(method, "5") == 0) {
            // Cek jika metode adalah 2 atau 5, maka tampilkan pesan setelah koma
            char *comma_position = strchr(message, ',');
            if (comma_position != NULL) {
                printf("|%-2d |%-30s |%-15s |%-15s |%-30s |\n",id, date, to, from, comma_position + 2);
            } else {
                printf("|%-2d |%-30s |%-15s |%-15s |%-30s |\n",id, date, to, from, message);
            }
        } else {
                printf("|%-2d |%-30s |%-15s |%-15s |%-30s |\n",id, date, to, from, message);
        }
    }
	printf("-------------------------------------------------------------------------------------------------------\n");


    system("pause");
};

void searchRecipient(FILE *file) {
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("                                    CARI BERDASARKAN PENERIMA                                       \n");
    printf("----------------------------------------------------------------------------------------------------\n");
	char recipient[100];
    printf("Masukkan nama penerima yang ingin Anda cari: ");
    scanf("%s", recipient);

    rewind(file);

    int id;
    char date[100], from[100], to[100], message[100], method[100], key[100];
    int found = 0;

	printf("-------------------------------------------------------------------------------------------------------\n");
	printf("|ID |            Waktu Kirim        |     Untuk      |      Dari      |       Pesan Ter-enkripsi      |\n");
	printf("|---|-------------------------------|----------------|----------------|-------------------------------|\n");

    while (fscanf(file, "%d, %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]", &id, date, to, from, method, key, message) != EOF) {
        if (strcmp(to, recipient) == 0) {
            if (strcmp(method, "2") == 0 || strcmp(method, "5") == 0) {
                // Cek jika metode adalah 2 atau 5, maka tampilkan pesan setelah koma
                char *comma_position = strchr(message, ',');
                if (comma_position != NULL) {
                    printf("|%-2d |%-30s |%-15s |%-15s |%-30s |\n",id, date, to, from, comma_position + 2);
                } else {
                    printf("|%-2d |%-30s |%-15s |%-15s |%-30s |\n",id, date, to, from, message);
                }
            } else {
                    printf("|%-2d |%-30s |%-15s |%-15s |%-30s |\n",id, date, to, from, message);
            }
            found = 1;
        }
    }

    if (!found) {
        printf("Tidak ada pesan yang ditemukan untuk penerima tersebut.\n");
    }
	printf("-------------------------------------------------------------------------------------------------------\n");

    system("pause");
}

void viewStatistics(struct UserStats userStats[], int numUsers) {
    gotoxy(0, 8);
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("                                          STATISTIK                                                 \n");
    printf("----------------------------------------------------------------------------------------------------\n");
	int i, maxMessageCount = 0;
    char maxUser[100];
    for (i = 0; i < numUsers; i++) {
        if (userStats[i].messageCount > maxMessageCount) {
            maxMessageCount = userStats[i].messageCount;
            strcpy(maxUser, userStats[i].username);
        }
    }

    printf("\t\t\tPengguna dengan penerima pesan terbanyak:\n");
    printf("\t\t\tUsername: %s\n", maxUser);
    printf("\t\t\tJumlah Pesan: %d\n\n", maxMessageCount);
    system("pause");
}
