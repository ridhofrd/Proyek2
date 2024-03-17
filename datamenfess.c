
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

struct UserStats {
    char username[100];
    int messageCount;
};

void viewAllMenfess(FILE *file);
void searchRecipient(FILE *file);
void viewStatistics(struct UserStats userStats[], int numUsers);

int mainDataMenfess() {
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("                                               HOME                                                 \n");
    printf("----------------------------------------------------------------------------------------------------\n");
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

    int choice;
    do {
        printf("Menu:\n");
        printf("1. View All Menfess\n");
        printf("2. Search by Recipient Name\n");
        printf("3. View Statistics\n");
        printf("4. Exit\n");
        printf("Pilih opsi: ");
        scanf("%d", &choice);
		system("cls");
        switch (choice) {
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
                break;
            default:
                printf("Opsi tidak valid. Silakan pilih opsi lain.\n");
        }
    } while (choice != 4);

    fclose(file);
    return 0;
}

void viewAllMenfess(FILE *file) {
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("                                         ALL MENFESS                                                \n");
    printf("----------------------------------------------------------------------------------------------------\n");
	rewind(file);

    int id;
    char date[100], from[100], to[100], message[100], method[100], key[100];

    printf("ID\tDate\t\t\tTo\t\t\tFrom\t\tMessage\n");
    printf("----------------------------------------------------------------------------------------------------\n");

    while (fscanf(file, "%d, %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]", &id, date, to, from, method, key, message) != EOF) {
        if (strcmp(method, "2") == 0 || strcmp(method, "5") == 0) {
            // Cek jika metode adalah 2 atau 5, maka tampilkan pesan setelah koma
            char *comma_position = strchr(message, ',');
            if (comma_position != NULL) {
                printf("%d\t%s\t%s\t%s\t%s\n", id, date, to, from, comma_position + 2); // Tampilkan pesan setelah koma
            } else {
                printf("%d\t%s\t%s\t%s\t%s\n", id, date, to, from, message);
            }
        } else {
            printf("%d\t%s\t%s\t%s\t%s\n", id, date, to, from, message);
        }
    }
}

void searchRecipient(FILE *file) {
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("                                    SEARCH RECEPIENT                                                \n");
    printf("----------------------------------------------------------------------------------------------------\n");
	char recipient[100];
    printf("Masukkan nama penerima yang ingin Anda cari: ");
    scanf("%s", recipient);

    rewind(file);

    int id;
    char date[100], from[100], to[100], message[100], method[100], key[100];
    int found = 0;

    printf("ID\tDate\t\t\tTo\t\t\tFrom\t\tMessage\n");
    printf("----------------------------------------------------------------------------------------------------\n");

    while (fscanf(file, "%d, %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]", &id, date, to, from, method, key, message) != EOF) {
        if (strcmp(to, recipient) == 0) {
            if (strcmp(method, "2") == 0 || strcmp(method, "5") == 0) {
                // Cek jika metode adalah 2 atau 5, maka tampilkan pesan setelah koma
                char *comma_position = strchr(message, ',');
                if (comma_position != NULL) {
                    printf("%d\t%s\t%s\t%s\t%s\n", id, date, to, from, comma_position + 2); // Tampilkan pesan setelah koma
                } else {
                    printf("%d\t%s\t%s\t%s\t%s\n", id, date, to, from, message);
                }
            } else {
                printf("%d\t%s\t%s\t%s\t%s\n", id, date, to, from, message);
            }
            found = 1;
        }
    }

    if (!found) {
        printf("Tidak ada pesan yang ditemukan untuk penerima tersebut.\n");
    }
}

void viewStatistics(struct UserStats userStats[], int numUsers) {
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("                                          STATISTICS                                                \n");
    printf("----------------------------------------------------------------------------------------------------\n");
	int i, maxMessageCount = 0;
    char maxUser[100];
    for (i = 0; i < numUsers; i++) {
        if (userStats[i].messageCount > maxMessageCount) {
            maxMessageCount = userStats[i].messageCount;
            strcpy(maxUser, userStats[i].username);
        }
    }

    printf("Pengguna dengan penerima pesan terbanyak:\n");
    printf("Username: %s\n", maxUser);
    printf("Jumlah Pesan: %d\n\n", maxMessageCount);
}
