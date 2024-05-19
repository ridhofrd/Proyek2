/* File		 : method_decrypt.c							*/
/* Deskripsi : Unit untuk keperluan ADT Decrypt_Method	*/

#include "decrypt.h"

/****** START METHOD DEKRIPSI RAIL FENCE ******/
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
/****** END METHOD DEKRIPSI RAIL FENCE ******/

/****** START METHOD DEKRIPSI VIGENERE ******/
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
/****** END METHOD DEKRIPSI VIGENERE ******/

/****** START METHOD DEKRIPSI VERNAM ******/
void decryptVernam(char* cipher_text, char* key, char* decryptedMsg) {
	int i = 0;
    for (i; i < strlen(cipher_text); i++) {
        decryptedMsg[i] = tolower(cipher_text[i]);
    }
    i = 0;
    for (i; i < strlen(key); i++) {
        key[i] = tolower(key[i]);
    }
    char plain_text[strlen(cipher_text)];
    
    i = 0;
    for (i; i < strlen(cipher_text); i++) {
        int k1 = decryptedMsg[i] - 'a';
        int k2 = key[i] - 'a';
        char s = (((k1 - k2) + 26) % 26) + 'a';
        decryptedMsg[i] = s;
    }
    decryptedMsg[strlen(cipher_text) + 1] = '\0';
}
/****** END METHOD DEKRIPSI VERNAM ******/

/****** START METHOD DEKRIPSI HILL CIPHER ******/
void generateKeyMatrix(int n, char *s, char key_matrix[MAX][MAX]) {
    int len = strlen(s);
    int k = 0;
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (isalpha(s[k])) {
                key_matrix[i][j] = tolower(s[k]);
                k++;
            }
        }
    }
}

int determinant(int mat[MAX][MAX], int n) {
    int det = 0;
    if (n == 1)
        return mat[0][0];
    int temp[MAX][MAX];
    int sign = 1;
    int f;
    for (f = 0; f < n; f++) {
        getCofactor(mat, temp, 0, f, n);
        det += sign * mat[0][f] * determinant(temp, n - 1);
        sign = -sign;
    }
    return det;
}

void getCofactor(int mat[MAX][MAX], int temp[MAX][MAX], int p, int q, int n) {
    int i = 0, j = 0;
    int row, col;
    for (row = 0; row < n; row++) {
        for (col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = mat[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

void adjoint(int mat[MAX][MAX], int adj[MAX][MAX], int n) {
    if (n == 1) {
        adj[0][0] = 1;
        return;
    }
    int i, j;
    int sign = 1, temp[MAX][MAX];
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            getCofactor(mat, temp, i, j, n);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = (sign) * (determinant(temp, n - 1));
        }
    }
}

int modInverse(int a, int m) {
    a = a % m;
    int  x;
    for (x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return 1;
}

void multiplyMatrix(int key[MAX][MAX], int message[MAX][1], int res[MAX][1], int n) {
    int i, j, k;
	for (i = 0; i < n; i++) {
        res[i][0] = 0;
        for (j = 0; j < 1; j++) {
            for (k = 0; k < n; k++) {
                res[i][j] += key[i][k] * message[k][j];
            }
        }
    }
}
// test isi key Matrix
void printKeyMatrix(int key_matrix_num[MAX][MAX], int n) {
    printf("Key Matrix:\n");
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", key_matrix_num[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// test size matrix
void printN(int n) {
    printf("Size of Matrix (n): %d\n\n", n);
}

void printMatrix(int mat[MAX][MAX], int row, int col) {
    int i, j;
	for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

void decryptMessage(int key[MAX][MAX], int inverse[MAX][MAX], char cipher_text[], char decryptedMsg[], int n) {
    int len = strlen(cipher_text);
    int rows = len / n;
    int r, i;
    int k = 0;
    for (r = 0; r < rows; r++) {
        int message[MAX][1], result[MAX][1];
        for (i = 0; i < n; i++) {
            message[i][0] = cipher_text[k++] - 'a';
        }

        multiplyMatrix(inverse, message, result, n);

        for (i = 0; i < n; i++) {
            int num = (result[i][0] % 26);
            if (num < 0) num += 26; // Menangani nilai negatif
            decryptedMsg[strlen(decryptedMsg)] = num + 'a';
        }
    }

    decryptedMsg[len] = '\0'; // Mengakhiri string dengan null terminator
}
/****** END METHOD DEKRIPSI HILL CIPHER ******/

/****** START SESSION METHOD DEKRIPSI ******/
void displayDecryptedMessage(const char *decryptedMsg) {
    printf("\nINI ISI DEKRIPSI PESAN MENFES ANDA\n");
    printf("=======================================================\n");
    printf("%s\n", decryptedMsg);
    printf("=======================================================\n\n");
}

void viewDecryptionKeyAndMessage(char nama_pengirimpesan[], Message *head, const char *filename) {
    Message *current = head;

    printf("=======================================================\n");
    printf("                 DAFTAR MENFES MASUK                    \n");
    printf("-------------------------------------------------------\n");
    printf("ID%-4sDate%-21sFrom\n", "", "");
    printf("-------------------------------------------------------\n");

    while (current != NULL) {
        printf("%-5d %-24s %-17s\n", current->id, current->timestamp, current->nama_pengirim);
        current = current->next;
    }

    int chosenId;
    printf("Mau Lihat Pesan Yang Mana? (Masukkan ID Pesan 1/2/...): ");
    scanf("%d", &chosenId);

    current = head;
    while (current != NULL) {
        if (current->id == chosenId) {
            // Logika dekripsi seperti sebelumnya
            char decryptedMsg[100];
                    int n = sqrt(strlen(current->key)); // Asumsikan kunci adalah matriks persegi
                    char key_matrix[MAX][MAX];
                    int key_matrix_num[MAX][MAX];
                    int i, j;
            // Proses dekripsi berdasarkan method
            switch (current->method) {
                case 1:
                    decryptRailFence(current->encryptedMsg, atoi(current->key), decryptedMsg);
                    break;
                case 2:
                    // Generate key matrix
                    generateKeyMatrix(n, current->key, key_matrix);

                    // Konversi matriks kunci menjadi angka (0-25)
                    for (i = 0; i < n; i++) {
                        for (j = 0; j < n; j++) {
                            key_matrix_num[i][j] = key_matrix[i][j] - 'a';
                        }
                    }

                    // Hitung determinan matriks kunci
                    int det = determinant(key_matrix_num, n);

                    // Jika determinan tidak nol, lanjutkan proses dekripsi
                    if (det != 0) {
                        int adj[MAX][MAX];
                        adjoint(key_matrix_num, adj, n);

                        // Hitung invers determinan
                        int det_inv = modInverse(det, 26);

                        // Hitung matriks invers
                        int inverse[MAX][MAX];
                        for (i = 0; i < n; i++) {
                            for (j = 0; j < n; j++) {
                                inverse[i][j] = ((adj[i][j] % 26) * det_inv) % 26;
                                if (inverse[i][j] < 0) {
                                    inverse[i][j] += 26;
                                }
                            }
                        }

                        // Lakukan dekripsi menggunakan matriks kunci dan matriks invers
                        decryptMessage(key_matrix_num, inverse, current->encryptedMsg, decryptedMsg, n);
                    } else {
                        printf("Matrix cannot be inverted\n");
                    }
                    break;
                case 3:
                    decryptVernam(current->encryptedMsg, current->key, decryptedMsg);
                    break;
                case 4:
                    decryptVigenere(current->encryptedMsg, current->key, decryptedMsg);
                    break;
                default:
                    printf("Invalid decryption method.\n");
                    return;
            }

            displayDecryptedMessage(decryptedMsg);
            markMessageAsRead(head, chosenId); // Tandai pesan sebagai sudah dibaca
            saveMessagesToFile(filename, head); // Simpan status baru ke file
            break;
        }
        current = current->next;
    }

    if (current == NULL) {
        printf("Pesan dengan ID %d tidak ditemukan.\n\n", chosenId);
    }
}


// Fungsi untuk membuat node baru
Message* createMessage(int status, int id, const char *timestamp, const char *nama_target, const char *nama_pengirim, int method, const char *key, int n, const char *encryptedMsg) {
    Message *newMessage = (Message *)malloc(sizeof(Message));
    newMessage->status = status;
    newMessage->id = id;
    strcpy(newMessage->timestamp, timestamp);
    strcpy(newMessage->nama_target, nama_target);
    strcpy(newMessage->nama_pengirim, nama_pengirim);
    newMessage->method = method;
    strcpy(newMessage->key, key);
    newMessage->n = n;
    strcpy(newMessage->encryptedMsg, encryptedMsg);
    newMessage->next = NULL;
    return newMessage;
}

Message* loadMessagesFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    Message *head = NULL;
    Message *tail = NULL;

    int status, id, method, n;
    char timestamp[100], nama_target[50], nama_pengirim[100], key[100], encryptedMsg[100];

    while (fscanf(file, "%d, %d, %[^,], %[^,], %[^,], %d, %d, %[^,], %[^\n]",
            &status, &id, timestamp, nama_target, nama_pengirim, &method, &n, key, encryptedMsg) == 9) {
        Message *newMessage = createMessage(status, id, timestamp, nama_target, nama_pengirim, method, key, n, encryptedMsg);

        if (head == NULL) {
            head = newMessage;
            tail = newMessage;
        } else {
            tail->next = newMessage;
            tail = newMessage;
        }
    }

    fclose(file);
    return head;
}

int countUnreadMessages(Message *head) {
    int count = 0;
    Message *current = head;

    while (current != NULL) {
        if (current->status == 0) {
            count++;
        }
        current = current->next;
    }

    return count;
}
void markMessageAsRead(Message *head, int messageId) {
    Message *current = head;

    while (current != NULL) {
        if (current->id == messageId) {
            current->status = 1;
            break;
        }
        current = current->next;
    }
}

void saveMessagesToFile(const char *filename, Message *head) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("File tidak dapat dibuka untuk menulis.\n");
        return;
    }

    Message *current = head;

    while (current != NULL) {
        fprintf(file, "%d, %d, %s, %s, %s, %d, %d, %s, %s\n",
                current->status, current->id, current->timestamp, current->nama_target, current->nama_pengirim, current->method, current->n, current->key, current->encryptedMsg);
        current = current->next;
    }

    fclose(file);
}

void viewDecryptionKeyAndMessageUnRead(char nama_pengirimpesan[], Message *head, const char *filename) {
    Message *current = head;

    printf("=======================================================\n");
    printf("                 DAFTAR MENFES BELUM DIBACA            \n");
    printf("-------------------------------------------------------\n");
    printf("ID%-4sDate%-21sFrom\n", "", "");
    printf("-------------------------------------------------------\n");

    while (current != NULL) {
        // Hanya menampilkan pesan dengan status 0 (belum dibaca)
        if (current->status == 0) {
            printf("%-5d %-24s %-17s\n", current->id, current->timestamp, current->nama_pengirim);
        }
        current = current->next;
    }

    int chosenId;
    printf("Mau Lihat Pesan Yang Mana? (Masukkan ID Pesan 1/2/...): ");
    scanf("%d", &chosenId);

    current = head;
    while (current != NULL) {
        if (current->id == chosenId && current->status == 0) {
            char decryptedMsg[100];
            // Proses dekripsi berdasarkan method
            switch (current->method) {
                case 1:
                    decryptRailFence(current->encryptedMsg, atoi(current->key), decryptedMsg);
                    break;
                case 2:
                    // Logika dekripsi untuk method 2
                    break;
                case 3:
                    decryptVernam(current->encryptedMsg, current->key, decryptedMsg);
                    break;
                case 4:
                    decryptVigenere(current->encryptedMsg, current->key, decryptedMsg);
                    break;
                default:
                    printf("Invalid decryption method.\n");
                    return;
            }

            displayDecryptedMessage(decryptedMsg);
            markMessageAsRead(head, chosenId); // Tandai pesan sebagai sudah dibaca
            saveMessagesToFile(filename, head); // Simpan status baru ke file
            break;
        }
        current = current->next;
    }

    if (current == NULL) {
        printf("Pesan dengan ID %d tidak ditemukan atau sudah dibaca.\n\n", chosenId);
    }
}


void clearScreen() {
    system("cls"); // Bersihkan layar konsol
}

int countLinesInFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File tidak dapat dibuka.\n");
        return -1; // Mengembalikan -1 jika gagal membuka file
    }

    int count = 0;
    char buffer[1000]; // Buffer untuk menyimpan setiap baris file

    // Membaca file baris per baris
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++; // Menginkrementasi hitungan setiap kali membaca baris baru
    }

    fclose(file);
    return count;
}
/****** END SESSION METHOD DEKRIPSI ******/
