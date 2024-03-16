#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// ...

void processUserMessage(char nama_user[]) {
    char msg[100];
    char nama_pengirimpesan[50];

    while (1) {
        printf("Enter the message (or type 'exit' to go back to the main menu): ");
        scanf(" %[^\n]s", msg);

        // Check if the user wants to exit
        if (strcmp(msg, "exit") == 0) {
            break;
        }

        printf("Enter the sender's username: ");
        scanf("%s", nama_pengirimpesan);

        int key;
        printf("Enter the encryption key: ");
        scanf("%d", &key);


        char encryptedMsg[100]; // Adjust the size as needed
        encryptMsg(msg, key, encryptedMsg);

        // File handling
        FILE *file;
        char filename[100];
        sprintf(filename, "%s.txt", nama_user);
       // Generate a unique id_pesan
        int id_pesan = generateUniqueId(filename);

        int msgLen = strlen(msg); // Added to get the length of the message

        // Check if the file already exists
        if ((file = fopen(filename, "a")) != NULL) {
            fprintf(file, "%d, %s, %s, 1, %d, ", id_pesan, nama_user, nama_pengirimpesan, key);

            // Use fwrite to write encryptedMsg as binary data
            fwrite(encryptedMsg, sizeof(char), msgLen, file);
            fprintf(file, "\n");

            fclose(file);
        } else {
            printf("Error creating or opening file.\n");
            return;
        }

        printf("Message successfully encrypted and saved to file.\n");
    }
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


void viewDecryptionKeyAndMessage(char nama_user[]) {
    FILE *file;
    char filename[100];
    sprintf(filename, "%s.txt", nama_user);

    if ((file = fopen(filename, "r")) != NULL) {
        int id_pesan, key, method;
        char pengirim[50], encryptedMsg[100];

        printf("List of Messages:\n");

        while (fscanf(file, "%d, %*[^,], %[^,], %d, %d, %[^\n]", &id_pesan, pengirim, &method, &key, encryptedMsg) == 5) {
            printf("ID: %d, Sender: %s\n", id_pesan, pengirim);
        }

        fclose(file);

        int chosenId;
        printf("Mau Lihat Pesan Yang Mana? (Masukkan ID Pesan 1/2/3/...): ");
        scanf("%d", &chosenId);

        if ((file = fopen(filename, "r")) != NULL) {
            while (fscanf(file, "%d, %*[^,], %[^,], %d, %d, %[^\n]", &id_pesan, pengirim, &method, &key, encryptedMsg) == 5) {
                if (id_pesan == chosenId) {
                    // Perform decryption based on the chosen method
                    char decryptedMsg[100];
                    switch (method) {
                        case 1:
                            decryptRailFence(encryptedMsg, key, decryptedMsg);
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
            printf("Invalid ID pesan.\n");
        } else {
            printf("Error opening file.\n");
        }
    } else {
        printf("Error opening file.\n");
    }
}

int mainGetdecrypt() {
    char nama_user[50];

    printf("Enter your username (or type 'exit' to quit): ");
    scanf("%s", nama_user);

    // Check if the user wants to exit
    if (strcmp(nama_user, "exit") == 0) {
        return 0;
    }

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

