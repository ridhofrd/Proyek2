#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERS 100
#define MAX_QUEUE_SIZE 100

// Struktur data untuk menyimpan pesan
struct Message {
    int id;
    char date[100];
    char from[100];
    char to[100];
    char method[100]; 
    char message[100];
};

// Struktur data untuk menyimpan statistik pengguna
struct UserStats {
    char username[100];
    int messageCount;
};

// Struktur data untuk queue
struct Queue {
    struct Message messages[MAX_QUEUE_SIZE];
    int front, rear;
};

// Fungsi untuk inisialisasi queue
void initializeQueue(struct Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Fungsi untuk menambahkan pesan ke dalam queue
void enqueue(struct Queue *q, struct Message msg) {
    if ((q->rear + 1) % MAX_QUEUE_SIZE == q->front) {
        printf("Queue is full\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    }
    q->messages[q->rear] = msg;
}

// Fungsi untuk menghapus pesan dari queue
void dequeue(struct Queue *q) {
    if (q->front == -1) {
        printf("Queue is empty\n");
        return;
    }
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    }
}

// Fungsi untuk menampilkan pesan terakhir dari hari terakhir
void viewLastDayMessages(struct Queue *q) {
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("                                       DAFTAR MENFESS HARI INI                                       \n");
    printf("------------------------------------------------------------------------------------------------------\n");
    time_t now;
    time(&now);
    struct tm *local_time = localtime(&now);
    char today[100];
    strftime(today, sizeof(today), "%d/%m/%Y", local_time);

    int i, found = 0;
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("|ID |            Waktu Kirim        |     Untuk      |      Dari      |      Pesan Ter-Enkripsi       |\n");
    printf("|---|-------------------------------|----------------|----------------|-------------------------------|\n");

    for (i = q->front; i != (q->rear + 1) % MAX_QUEUE_SIZE; i = (i + 1) % MAX_QUEUE_SIZE) {
        struct Message msg = q->messages[i];
        if (strcmp(msg.date, today) == 0) {
            if (strcmp(msg.method, "2") == 0 || strcmp(msg.method, "5") == 0) {
                // Jika metodenya adalah 2 atau 5, langsung tampilkan pesan terenkripsi
                printf("|%-2d |%-30s |%-15s |%-15s |%-30s |\n", msg.id, msg.date, msg.to, msg.from, msg.message);
            } else {
                // Jika bukan metode 2 atau 5, cek koma dan tampilkan pesan setelah koma sebagai pesan terenkripsi
                char *comma_position = strchr(msg.message, ',');
                if (comma_position != NULL) {
                    printf("|%-2d |%-30s |%-15s |%-15s |%-30s |\n", msg.id, msg.date, msg.to, msg.from, comma_position + 2); // Tampilkan pesan setelah koma
                } else {
                    printf("|%-2d |%-30s |%-15s |%-15s |%-30s |\n", msg.id, msg.date, msg.to, msg.from, msg.message);
                }
            }
            found = 1;
        }
    }

    if (!found) {
        printf("Tidak ada pesan yang ditemukan untuk hari ini.\n");
    }
}

void viewAllMenfess(FILE *file) {
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("                                       DAFTAR SELURUH MENFESS                                         \n");
    printf("------------------------------------------------------------------------------------------------------\n");
    rewind(file);

    int dummy, id;
    char date[100], from[100], to[100], message[100], method[100], key[100];

    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("|ID |            Waktu Kirim        |     Untuk      |      Dari      |      Pesan Ter-Enkripsi       |\n");
    printf("|---|-------------------------------|----------------|----------------|-------------------------------|\n");

    while (fscanf(file, "%d, %d, %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]", &dummy, &id, date, to, from, method, key, message) != EOF) {
        if (strcmp(method, "2") == 0 || strcmp(method, "5") == 0) {
            // Cek jika metode adalah 2 atau 5, maka tampilkan pesan setelah koma
            char *comma_position = strchr(message, ',');
            if (comma_position != NULL) {
                printf("|%-2d |%-30s |%-15s |%-15s |%-30s |\n", id, date, to, from, comma_position + 2); // Tampilkan pesan setelah koma
            } else {
                printf("|%-2d |%-30s |%-15s |%-15s |%-30s |\n", id, date, to, from, message);
            }
        } else {
            printf("|%-2d |%-30s |%-15s |%-15s |%-30s |\n", id, date, to, from, message);
        }
    }
}

void searchRecipient(FILE *file) {
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("                                    CARI BERDASARKAN PENERIMA                                       \n");
    printf("----------------------------------------------------------------------------------------------------\n");
    char recipient[100];
    printf("Masukkan nama penerima yang ingin Anda cari: ");
    scanf("%s", recipient);

    rewind(file);

    int dummy, id;
    char date[100], from[100], to[100], message[100], method[100], key[100];
    int found = 0;

    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("|ID |            Waktu Kirim        |     Untuk      |      Dari      |       Pesan Ter-enkripsi      |\n");
    printf("|---|-------------------------------|----------------|----------------|-------------------------------|\n");

    while (fscanf(file, "%d, %d, %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]", &dummy, &id, date, to, from, method, key, message) != EOF) {
        if (strcmp(to, recipient) == 0) {
            if (strcmp(method, "2") == 0 || strcmp(method, "5") == 0) {
                // Cek jika metode adalah 2 atau 5, maka tampilkan pesan setelah koma
                char *comma_position = strchr(message, ',');
                if (comma_position != NULL) {
                    printf("|%-2d |%-30s |%-15s |%-15s |%-30s |\n", id, date, to, from, comma_position + 2); // Tampilkan pesan setelah koma
                } else {
                    printf("|%-2d |%-30s |%-15s |%-15s |%-30s |\n", id, date, to, from, message);
                }
            } else {
                printf("|%-2d |%-30s |%-15s |%-15s |%-30s |\n", id, date, to, from, message);
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
    printf("                                          STATISTIK                                                \n");
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

    struct Queue messageQueue;
    initializeQueue(&messageQueue);

    int dummy, id;
    char date[100], from[100], to[100], message[100], method[100], key[100];

    // Hitung statistik untuk setiap pengguna dan tambahkan pesan ke dalam queue
    while (fscanf(file, "%d, %d, %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]", &dummy, &id, date, to, from, method, key, message) != EOF) {
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

        // Tambahkan pesan ke dalam queue
        struct Message msg;
        msg.id = id;
        strcpy(msg.date, date);
        strcpy(msg.from, from);
        strcpy(msg.to, to);
        strcpy(msg.message, message);
        enqueue(&messageQueue, msg);
    }

    int choice;
    do {
        printf("Menu:\n");
        printf("1. View All Menfess\n");
        printf("2. Search by Recipient Name\n");
        printf("3. View Statistics\n");
        printf("4. View Last Day Messages\n");
        printf("5. Exit\n");
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
                viewLastDayMessages(&messageQueue);
                break;
            case 5:
                printf("Terima kasih!\n");
                break;
            default:
                printf("Opsi tidak valid. Silakan pilih opsi lain.\n");
        }
    } while (choice != 5);

    fclose(file);
    return 0;
}
