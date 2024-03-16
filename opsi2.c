
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define MAX_SIZE 100
#define MAX_MEMBERS 100

// Definisikan struktur data untuk menyimpan informasi pengguna
typedef struct {
    int id;
    char username[50];
    char password[50];
    char nim[20];
    char kelas[10];
} Member;

// Fungsi untuk membaca data member dari file
int readMembersFromFile(Member *members) {
    FILE *file = fopen("mahasiswa.txt", "r");
    if (file == NULL) {
        printf("File mahasiswa.txt tidak dapat dibuka.\n");
        return 0;
    }

    int numMembers = 0;
    // Baca data pengguna dari file dan simpan dalam variabel members
//    while (fscanf(file, "%[^,],%[^,],%[^\n]\n", members[numMembers].nama, members[numMembers].username, members[numMembers].password) == 3 && numMembers < MAX_MEMBERS) {
//        numMembers++;
//    }
	while (numMembers < MAX_MEMBERS && fscanf(file, "%d %s %s %s %s\n", &members[numMembers].id, members[numMembers].username, members[numMembers].password, members[numMembers].nim, members[numMembers].kelas) == 5) {
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

int processOption() {
    int option = 0;
    printf("\nPilihan opsi: ");
    scanf("%d", &option);
    if (option == 1) {
        // Handle option 1: Kirim pesan
        int targetID;
        printf("\nMasukkan nomor id tujuan yang ingin anda buatkan menfess : ");
        scanf("%d", &targetID);
        printf("Mengirim pesan ke ID %d...\n", targetID);
        return targetID;
    } else if (option == 2) {
        // Handle option 2: Kembali ke menu utama
        printf("Kembali ke menu utama...\n");
    } else {
        printf("Pilihan tidak valid.\n");
    }
}

char *getUsernameFromID(int targetID, Member *members, int numMembers) {
    for (int i = 0; i < numMembers; i++) {
        if (members[i].id == targetID) {
            return members[i].username;
        }
    }
    return NULL; // ID tidak ditemukan
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
        printf("%d. %s\n", members[i].id, members[i].username);
    }
}

void selectMetode(int *selectedOption, char *msg) {
	printf("Enter the message : ");
	scanf(" %[^\n]s", msg);
	printf("ini pesan: %s\n", msg);

    printf("\n====================\n");
    printf("1. Railfence Encryption\n");
    printf("2. Hill Encryption\n");
    printf("3. Vernam Encryption\n");
    printf("4. Vigenere Encryption\n");
    printf("5. RSA\n");
    printf("====================\n");

    printf("Pilihan metode enkripsi yang ingin digunakan : ");
    scanf("%d", selectedOption);
    printf("====================\n");
}

// Function to save encrypted message to file
void saveEncryptedMessageToFile(char nama_target[], char nama_pengirimpesan[], char msg[], int encryptionMethod) {
	printf("%s \n", nama_target);
	printf("%s \n",nama_pengirimpesan);
	printf("%s \n",msg);
	printf("%d \n",encryptionMethod);

    // File handling
    FILE *file;
    char filename[100];

	char encryptedMsg[100]; // Adjust the size as needed
    int msgLen = strlen(msg); // Added to get the length of the message
    char keyhuruf[100]; // var vigenere
    int keyangka; // var railfence
    long int p, q, flag ; // var RSA
    // Call the appropriate encryption function based on the selected method
    switch (encryptionMethod) {
        case 1:  //railfence
	        printf("Enter the encryption key (berupa angka): ");
	        scanf("%d", &keyangka);

            // Implement Rainfence Encryption logic
            encryptMsg(msg, keyangka, encryptedMsg);

            sprintf(filename, "%s.txt", nama_target);
            int id_pesan = generateUniqueId(filename);

            // Check if the file already exists
            if ((file = fopen(filename, "a")) != NULL) {
                fprintf(file, "%d, %s, %s, 1, %d, ", id_pesan, nama_target, nama_pengirimpesan, keyangka);

                // Use fwrite to write encryptedMsg as binary data
                fwrite(encryptedMsg, sizeof(char), msgLen, file);
                fprintf(file, "\n");

                fclose(file);
            } else {
                printf("Error creating or opening file.\n");
                return;
            }

            printf("Message successfully encrypted and saved to file.\n");
            break;
        case 2:  //hill cipher
			//imple
        case 3:  //vernam cipher
            // Implement Vernam Encryption logic
            break;
        case 4:  //vigenere
            printf("Enter the encryption key (berupa huruf): ");
	        scanf("%s", &keyhuruf);

            // Implement Vigenere Encryption logic
            vigenere_encrypt(msg, keyhuruf, encryptedMsg);

            sprintf(filename, "%s.txt", nama_target);
            int id_pesann = generateUniqueId(filename);

            // Check if the file already exists
            if ((file = fopen(filename, "a")) != NULL) {
                fprintf(file, "%d, %s, %s, 4, %s, ", id_pesann, nama_target, nama_pengirimpesan, keyhuruf);

                // Use fwrite to write encryptedMsg as binary data
                fwrite(encryptedMsg, sizeof(char), msgLen, file);
                fprintf(file, "\n");

                fclose(file);
            } else {
                printf("Error creating or opening file.\n");
                return;
            }
            printf("Message successfully encrypted and saved to file.\n");
            break;
        case 5:  //RSA
            break;
        default:
            printf("Pilihan tidak valid\n");
            return;
    }
}

int opsi2Harris(char *username) {
    Member members[MAX_MEMBERS];
    char *usernameArray[MAX_MEMBERS];
    int numMembers = readMembersFromFile(members);
    int targetID;
    int selectedOption;
    char msg[100];

	printf("nama yang login : %s \n", username);
    printf("ini numnumber = %d \n", numMembers);

    // Menampilkan menu dan daftar pengguna ke layar
    printMenu();
    printMembers(members, numMembers, username);
    printOptions();
    targetID = processOption();
//    printf("ini id tujuan : %d \n", targetID);

	char *targetUsername = getUsernameFromID(targetID, members, numMembers);
//    printf("Username dari targetID %d adalah: %s\n", targetID, targetUsername);

	selectMetode(&selectedOption, msg);

//    printf("ini selected opsi : %d\n", selectedOption);
//    printf("ini pesan: %s\n", msg);

    saveEncryptedMessageToFile(targetUsername, username, msg, selectedOption);

	char selesai[50];
	printf("klik enter untuk lanjut");
	scanf("%s", selesai);

    return 0;
}
