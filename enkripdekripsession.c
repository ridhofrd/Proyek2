#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h> // punya ridho
#include <ctype.h> // punya haya
// Function to read the last used message ID from file
int getLastMessageId(char filename[]) {
    FILE *file = fopen(filename, "r");
    int lastId = 0;

    if (file != NULL) {
        int id;
        char line[100];  // Assuming a reasonable maximum line length

        while (fgets(line, sizeof(line), file) != NULL) {
            sscanf(line, "%d", &id);
            lastId = id; // Update lastId for each line until the end of the file
        }

        fclose(file);
    }

    return lastId;
}

<<<<<<< HEAD


=======
>>>>>>> origin/dayen
// Function to generate a unique ID for each message
int generateUniqueId(char filename[]) {
    int lastMessageId = getLastMessageId(filename);
    return ++lastMessageId;
}

void encryptMsg(char msg[], int key, char encryptedMsg[]) {
    int msgLen = strlen(msg), i, j, k = -1, row = 0, col = 0;
    char railMatrix[key][msgLen];

    // Inisialisasi matriks dengan karakter newline
    for (i = 0; i < key; ++i)
        for (j = 0; j < msgLen; ++j)
            railMatrix[i][j] = '\n';

    // Mengisi matriks sesuai dengan pola railfence
    for (i = 0; i < msgLen; ++i) {
        railMatrix[row][col++] = msg[i];

        if (row == 0 || row == key - 1)
            k = k * (-1);

        row = row + k;
    }

    // Menyalin pesan terenkripsi dari seluruh matriks
    int index = 0; // Added index variable to keep track of the position in encryptedMsg
    for (i = 0; i < key; ++i) {
        for (j = 0; j < msgLen; ++j) {
            if (railMatrix[i][j] != '\n') {
                encryptedMsg[index++] = railMatrix[i][j];
            }
        }
    }

    encryptedMsg[msgLen] = '\0';  // Null-terminate the string

    // Menampilkan pesan terenkripsi ke layar
    printf("Encrypted Message: %s\n", encryptedMsg);
}

void decryptRailFence(char encryptedMsg[], int key, char decryptedMsg[]) {
    int len = strlen(encryptedMsg), i, j;
    char railMatrix[key][len];

    // Initialize the matrix with null characters
    for (i = 0; i < key; ++i)
        for (j = 0; j < len; ++j)
            railMatrix[i][j] = '\0';

    // Determine the rail positions based on the key
    int railPos[len];
    int currentRail = 0;
    int changeDirection = 0;
    for (i = 0; i < len; ++i) {
        railPos[i] = currentRail;
        if (currentRail == 0 || currentRail == key - 1) {
            changeDirection = !changeDirection;
        }
        currentRail += (changeDirection ? 1 : -1);
    }

    // Fill the matrix with the encrypted message
    int k = 0;
    for (i = 0; i < key; ++i) {
        for (j = 0; j < len; ++j) {
            if (railPos[j] == i) {
                railMatrix[i][j] = encryptedMsg[k++];
            }
        }
    }

    // Read the decrypted message from the matrix
    k = 0;
    for (j = 0; j < len; ++j) {
        for (i = 0; i < key; ++i) {
            if (railPos[j] == i) {
                decryptedMsg[k++] = railMatrix[i][j];
            }
        }
    }

    decryptedMsg[len] = '\0';  // Null-terminate the string
}
// AKHIR YANG ENKRIPSI DEKRIPSI RAILFENCE

// AWAL YANG ENKRIPSI DEKRIPSI RSA
//long int cd(long int);
//long int findE(long int);
//void encryptRSA(char msg[], long int p, long int q, char encryptedMsg[]);
//
//int prime(long int pr) {
//    int i;
//    if (pr == 1)
//        return 0;
//
//    for (i = 2; i <= sqrt(pr); i++) {
//        if (pr % i == 0)
//            return 0;
//    }
//    return 1;
//}
//
//long int ce(long int x, long int t) {
//    long int k = 1;
//    while (1) {
//        k = k + t;
//        if (k % x == 0)
//            return (k / x);
//    }
//}
//
//void encryptRSA(char msg[], long int p, long int q, char encryptedMsg[]) {
//    long int n, t, e[100], d[100], temp[100], j, m[100], en[100], i;
//
//    long int key = findE(p, q);
//
//    int len = strlen(msg);
//    i = 0;
//    while (i < len) {
//        long int pt = msg[i] - 96;
//        long int k = 1;
//
//        for (j = 0; j < key; j++) {
//            k = k * pt;
//            k = k % n;
//        }
//
//        temp[i] = k;
//        long int ct = k + 96;
//        en[i] = ct;
//        i++;
//    }
//
//    en[i] = -1;
//    printf("\nTHE ENCRYPTED MESSAGE IS:\n");
//    for (i = 0; en[i] != -1; i++) {
//        printf("%c", (char)en[i]);
//        encryptedMsg[i] = (char)en[i];
//    }
//
//    encryptedMsg[i] = '\0';  // Null-terminate the string
//}
//


// AWAL METHOD HAYA VIGENERE
void removeSpaces(char *str) {
    int i, count = 0;
    for (i = 0; str[i]; i++) {
        if (str[i] != ' ')
            str[count++] = str[i];
    }
    str[count] = '\0';
}

void vigenere_encrypt(const char *plaintext, const char *keyhuruf, char *encrypted) {
    int i, j;
    int plaintext_length = strlen(plaintext);
    int key_length = strlen(keyhuruf);

    for (i = 0, j = 0; i < plaintext_length; i++, j++) {
        if (j == key_length)
            j = 0;

        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            encrypted[i] = 'a' + (plaintext[i] - 'a' + keyhuruf[j] - 'a') % 26;
        } else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            encrypted[i] = 'A' + (plaintext[i] - 'A' + keyhuruf[j] - 'a') % 26;
        } else {
            encrypted[i] = plaintext[i];
            j--;
        }
    }
    encrypted[i] = '\0';
}

void decryptVigenere(const char *encryptedMsg, const char *key, char *decryptedMsg) {
    int encryptedMsgLength = strlen(encryptedMsg);
    int keyLength = strlen(key);
    int i, j;

    for (i = 0, j = 0; i < encryptedMsgLength; ++i) {
        // Periksa apakah karakter adalah huruf
        if (isalpha(encryptedMsg[i])) {
            char base = isupper(encryptedMsg[i]) ? 'A' : 'a';
            char keyChar = tolower(key[j % keyLength]);
            // Dekripsi karakter
            decryptedMsg[i] = (encryptedMsg[i] - base - (keyChar - 'a') + 26) % 26 + base;
            ++j;
        } else {
            // Jika karakter bukan huruf, langsung disalin ke pesan terdekripsi
            decryptedMsg[i] = encryptedMsg[i];
        }
    }
    decryptedMsg[i] = '\0';  // Null-terminate the string
}

// AKHIR HAYA VIGENERE

void processUserMessage(char nama_user[]) {
    char nama_pengirimpesan[50];
    char msg[100];
    int selectedOption;

    printf("Enter the user's username: ");
    scanf("%s", nama_user);

    while (1) {
        printf("Enter the message (or type 'exit' to go back to the main menu): ");
        scanf(" %[^\n]s", msg);

        // Check if the user wants to exit
        if (strcmp(msg, "exit") == 0) {
            break;
        }

        printf("Enter the sender's username: ");
        scanf("%s", nama_pengirimpesan);

        // Display the encryption method options
        printf("\n====================\n");
        printf("1. Rainfence Encryption\n");
        printf("2. Caesar Encryption\n");
        printf("3. Vernam Encryption\n");
        printf("4. Vigenere Encryption\n");
        printf("5. Simple Text Steganography\n");
        printf("====================\n");

        printf("Pilihan metode enkripsi yang ingin digunakan : ");
        scanf("%d", &selectedOption);

        saveEncryptedMessageToFile(nama_user, nama_pengirimpesan, msg, selectedOption);

        printf("Message successfully encrypted and saved to file.\n");
    }
}
// Function to save encrypted message to file
void saveEncryptedMessageToFile(char nama_user[], char nama_pengirimpesan[], char msg[], int encryptionMethod) {
    char encryptedMsg[100]; // Adjust the size as needed
    // File handling
    FILE *file;
    char filename[100];

    int msgLen = strlen(msg); // Added to get the length of the message
<<<<<<< HEAD
    char keyhuruf[100]; // var vigenere
=======
    char keyhuruf[100]; // var vigenere        
>>>>>>> origin/dayen
    int keyangka; // var railfence
    long int p, q, flag ; // var RSA
    // Call the appropriate encryption function based on the selected method
    switch (encryptionMethod) {
        case 1:
	        printf("Enter the encryption key (berupa angka): ");
	        scanf("%d", &keyangka);
<<<<<<< HEAD

=======
	
>>>>>>> origin/dayen
            // Implement Rainfence Encryption logic
            encryptMsg(msg, keyangka, encryptedMsg);

            sprintf(filename, "%s.txt", nama_user);
            int id_pesan = generateUniqueId(filename);

            // Check if the file already exists
            if ((file = fopen(filename, "a")) != NULL) {
                fprintf(file, "%d, %s, %s, 1, %d, ", id_pesan, nama_user, nama_pengirimpesan, keyangka);

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
        case 2:
            // Implement Caesar Encryption logic
            break;
        case 3:
            // Implement Vernam Encryption logic
            break;
        case 4:
            printf("Enter the encryption key (berupa huruf): ");
	        scanf("%s", &keyhuruf);
<<<<<<< HEAD

=======
	
>>>>>>> origin/dayen
            // Implement Vigenere Encryption logic
            vigenere_encrypt(msg, keyhuruf, encryptedMsg);

            sprintf(filename, "%s.txt", nama_user);
            int id_pesann = generateUniqueId(filename);

            // Check if the file already exists
            if ((file = fopen(filename, "a")) != NULL) {
                fprintf(file, "%d, %s, %s, 4, %s, ", id_pesann, nama_user, nama_pengirimpesan, keyhuruf);

                // Use fwrite to write encryptedMsg as binary data
                fwrite(encryptedMsg, sizeof(char), msgLen, file);
                fprintf(file, "\n");

                fclose(file);
            } else {
                printf("Error creating or opening file.\n");
                return;
            }
            break;
        case 5:
            break;
        default:
            printf("Pilihan tidak valid\n");
            return;
    }
}



void viewDecryptionKeyAndMessage(char nama_user[]) {
    FILE *file;
    char filename[100];
    sprintf(filename, "%s.txt", nama_user);

    if ((file = fopen(filename, "r")) != NULL) {
        int id_pesan, keyangka, method;
        char pengirim[50], encryptedMsg[100], key[100];

        printf("List of Messages:\n");

		while (fscanf(file, "%d, %*[^,], %[^,], %d, %[^,], %[^\n]", &id_pesan, pengirim, &method, key, encryptedMsg) == 5) {
		    printf("ID: %d, Sender: %s\n", id_pesan, pengirim);
		}


        fclose(file);

        int chosenId;
        printf("Mau Lihat Pesan Yang Mana? (Masukkan ID Pesan 1/2/3/...): ");
        scanf("%d", &chosenId);
        char *endptr;
        long int convertedValue = strtol(key, &endptr, 10);

        if ((file = fopen(filename, "r")) != NULL) {
        	int found = 0;
			while (fscanf(file, "%d, %*[^,], %[^,], %d, %[^,], %[^\n]", &id_pesan, pengirim, &method, key, encryptedMsg) == 5) {
                if (id_pesan == chosenId) {
                	found = 1;
                    // Perform decryption based on the chosen method
                    char decryptedMsg[100];
                    switch (method) {
                        case 1:
        			if (*endptr == '\0' || *endptr == '\n') {
            			keyangka = convertedValue;
        			}
                            decryptRailFence(encryptedMsg, keyangka, decryptedMsg);
                            break;
                        case 4:
                        	printf("Encrypted Message: %s\nKey: %s\n", encryptedMsg, key);

                        	decryptVigenere(encryptedMsg, key, decryptedMsg);
                        	break;
                        // Add other decryption methods as needed
                        // ...

                        default:
                            printf("Invalid decryption method.\n");
                            fclose(file);
                            return;
                    }

                    // Display the decrypted message
                    printf("Decrypted Message: %s\n", decryptedMsg);

                    // Ask the user for the next action
                    int option;
                    printf("Pilih tindakan selanjutnya:\n");
                    printf("1. Pergi ke menu pesan\n");
                    printf("2. Kembali ke menu utama\n");
                    printf("Pilihan: ");
                    scanf("%d", &option);

                    switch (option) {
                        case 1:
                            // TODO: Add code to go to the message menu
                            // ...
                            break;
                        case 2:
                            // TODO: Add code to go back to the main menu
                            // ...
                            break;
                        default:
                            printf("Pilihan tidak valid.\n");
                            break;
                    }
                    fclose(file);
                    return;
                }
            }
            fclose(file);
		    // Check if the chosenId is not found
		    if (!found) {
		        printf("Invalid ID pesan.\n");
		    }
        } else {
            printf("Error opening file.\n");
        }
    } else {
        printf("Error opening file.\n");
<<<<<<< HEAD
        printf("Ini sudah menu dashboard user\n");
        char terminator;
        scanf("%c", terminator);
    }
}

int mainEnkripDekripSession(char *user) {

    // Check if the user wants to exit
    char nama_user[50];
    strcpy(nama_user, user);
=======
    }
}

int main() {
    char nama_user[50];

    printf("Enter your username (or type 'exit' to quit): ");
    scanf("%s", nama_user);

    // Check if the user wants to exit
    if (strcmp(nama_user, "exit") == 0) {
        return 0;
    }

>>>>>>> origin/dayen
    int choice;
    while (1) {
        printf("\nMain Menu:\n");
        printf("1. View Decryption Key\n");
        printf("2. Send Railfence Encrypted Message\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewDecryptionKeyAndMessage(nama_user);
                break;
            case 2:
                processUserMessage(nama_user);
                break;
            case 3:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
