#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

struct UserStats {
    char username[100];
    int messageCount;
};

int main() {
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
    while (fscanf(file, "%d %s %s %s %s %s %[^\n]", &id, date, from, to, method, key, message) != EOF) {
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

    // Cari pengguna dengan penerima pesan terbanyak
    int maxMessageCount = 0;
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

    // Kembali ke awal file untuk membaca dan menampilkan pesan-pesan
    rewind(file);

    // Tampilkan data dari file
    printf("ID\tDate\t\tFrom\tTo\tMessage\n");
    printf("--------------------------------------------------\n");
    while (fscanf(file, "%d %s %s %s %s %s %[^\n]", &id, date, from, to, method, key, message) != EOF) {
        printf("%d\t%s\t%s\t%s\t%s\n", id, date, from, to, message);
    }

    fclose(file);
    return 0;
}
