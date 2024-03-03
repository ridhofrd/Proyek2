#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_MEMBERS 100

// Definisikan struktur data untuk menyimpan informasi pengguna
typedef struct {
    char nama[50];
    char username[50];
    char password[50];
} Member;

// Fungsi untuk membaca data member dari file
int readMembersFromFile(Member *members) {
    FILE *file = fopen("DataMember.txt", "r");
    if (file == NULL) {
        printf("File DataMember.txt tidak dapat dibuka.\n");
        return 0;
    }

    int numMembers = 0;
    // Baca data pengguna dari file dan simpan dalam variabel members
    while (fscanf(file, "%[^,],%[^,],%[^\n]\n", members[numMembers].nama, members[numMembers].username, members[numMembers].password) == 3 && numMembers < MAX_MEMBERS) {
        numMembers++;
    }
	
    if (numMembers == 0) {
        // Jika tidak berhasil membaca file, keluar dari program
        return 1;
    }
	
    // Tutup file setelah selesai membaca
    fclose(file);
    return numMembers;
}

void printMenu() {
    printf("Mau kirim menfess ke siapa?\n");
}

void printOptions() {
    printf("\nPilihan opsi:\n");
    printf("1. Pilih tujuan kirim menfess\n");
    printf("2. Kembali ke menu utama\n");
}

void processOption() {
    int option = 0;
    printf("\nPilihan opsi: ");
    scanf("%d", &option);
    if (option == 1) {
        // Handle option 1: Kirim pesan
        int targetID;
        printf("\nMasukkan nomor id tujuan yang ingin anda buatkan menfess : ");
        scanf("%d", &targetID);
        printf("Mengirim pesan ke ID %d...\n", targetID);
    } else if (option == 2) {
        // Handle option 2: Kembali ke menu utama
        printf("Kembali ke menu utama...\n");
    } else {
        printf("Pilihan tidak valid.\n");
    }
}

void printMembers(Member *members, int numMembers, char *loggedInUsername) {
    int i;
    for (i = 0; i < numMembers; i++) {
        // Cek apakah username dalam data member sama dengan username yang sedang login
        if (strcmp(members[i].username, loggedInUsername) == 0) {
            // Jika sama, lanjut ke pengguna berikutnya
            continue;
        }
        // Jika tidak sama, cetak nomor indeks dan nama
        printf("%d. %s\n", i + 1, members[i].nama);
    }
}

void selectMetode() {
    printf("\n====================\n");
    printf("1. Rainfence Encryption\n");
    printf("2. Caesar Encryption\n");
    printf("3. Vernam Encryption\n");
    printf("4. Vigenere Encryption\n");
    printf("5. Simple Text Steganography\n");
    printf("====================\n");

    int selectedOption;
    printf("Pilihan metode enkripsi yang ingin digunakan : ");
    scanf("%d", &selectedOption);

    switch(selectedOption) {
        case 1:
            printf("Anda memilih Rainfence Encryption\n");
            break;
        case 2:
            printf("Anda memilih Caesar Encryption\n");
            break;
        case 3:
            printf("Anda memilih Vernam Encryption\n");
            break;
        case 4:
            printf("Anda memilih Vigenere Encryption\n");
            break;
        case 5:
            printf("Anda memilih Simple Text Steganography\n");
            break;
        default:
            printf("Pilihan tidak valid\n");
    }
}

int main() {
    Member members[MAX_MEMBERS];
    int numMembers = readMembersFromFile(members);

    // Simulasikan username yang sedang login
    char loggedInUsername[50] = "john_sue"; // Misalkan username yang sedang login adalah "alice_smith456"

    // Menampilkan menu dan daftar pengguna ke layar
    printMenu();
    printMembers(members, numMembers, loggedInUsername);
    printOptions();
    processOption();
    selectMetode();

    return 0;
}
