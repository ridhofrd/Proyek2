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

void viewDecryptionKeyAndMessage(char nama_pengirimpesan[], MessageNode *head, const char *filename) {
    MessageNode *current = head;

    printf("=======================================================\n");
    printf("                 DAFTAR MENFES MASUK                    \n");
    printf("-------------------------------------------------------\n");
    printf("ID%-4sDate%-21sFrom\n", "", "");
    printf("-------------------------------------------------------\n");

    while (current != NULL) {
        printf("%-5d %-24s %-17s\n", current->id_pesan, current->timestamp, current->nama_pengirimpesan);
        current = current->next;
    }

    int chosenId;
    printf("Mau Lihat Pesan Yang Mana? (Masukkan ID Pesan 1/2/...): ");
    scanf("%d", &chosenId);

    current = head;
    while (current != NULL) {
        if (current->id_pesan == chosenId) {
            // Logika dekripsi seperti sebelumnya
            char decryptedMsg[100];
                        char key_matrix[MAX][MAX];
            int key_matrix_num[MAX][MAX];
            int n, i, j;
            // Proses dekripsi berdasarkan method
            switch (current->type) {
                case RAILFENCE:
                    decryptRailFence(current->ciphertext, current->cipher.railfence.keyangka, decryptedMsg);
                    break;
                case HILL:
                   n = sqrt(strlen(current->cipher.hill.keyhuruf));
                    // Ubah kunci menjadi matriks kunci
                    generateKeyMatrix(n, current->cipher.hill.keyhuruf, key_matrix);

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
                        decryptMessage(key_matrix_num, inverse, current->ciphertext, decryptedMsg, n);
                    }
                    break;
                case VERNAM:
                    decryptVernam(current->ciphertext, current->cipher.vernam.keyhuruf, decryptedMsg);
                    break;
                case VIGENERE:
                    decryptVigenere(current->ciphertext, current->cipher.vigenere.keyhuruf, decryptedMsg);
                    break;
                case RSA:
                    // Logika dekripsi untuk method RSA
                    break;
                default:
                    printf("Invalid decryption method.\n");
                    return;
            }

            displayDecryptedMessage(decryptedMsg);
            current->status = 1; // Tandai pesan sebagai sudah dibaca
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
MessageNode* createMessageNode(int status, int id_pesan, const char *timestamp, const char *nama_target, const char *nama_pengirimpesan, CipherType type, const char *key1, const char *key2, const char *ciphertext) {
    MessageNode *newMessage = (MessageNode *)malloc(sizeof(MessageNode));
    if (newMessage == NULL) {
        return NULL; // Gagal mengalokasikan memori
    }

    newMessage->status = status;
    newMessage->id_pesan = id_pesan;
    strcpy(newMessage->timestamp, timestamp);
    strcpy(newMessage->nama_target, nama_target);
    strcpy(newMessage->nama_pengirimpesan, nama_pengirimpesan);
    strcpy(newMessage->ciphertext, ciphertext);
    newMessage->type = type;

    switch (type) {
        case RAILFENCE:
            newMessage->cipher.railfence.keyangka = atoi(key1);
            break;
        case HILL:
            newMessage->cipher.hill.n2 = atoi(key1);
            strcpy(newMessage->cipher.hill.keyhuruf, key2);
            break;
        case VERNAM:
            strcpy(newMessage->cipher.vernam.keyhuruf, key1);
            break;
        case VIGENERE:
            strcpy(newMessage->cipher.vigenere.keyhuruf, key1);
            break;
        case RSA:
            newMessage->cipher.rsa.p = atoi(key1);
            newMessage->cipher.rsa.q = atoi(key2);
            break;
        default:
            // Penanganan untuk jenis enkripsi lainnya jika diperlukan
            break;
    }

    newMessage->next = NULL;
    return newMessage;
}
MessageNode* loadMessagesFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    MessageNode *head = NULL;
    MessageNode *tail = NULL;

    int id_pesan, type, status;
    char timestamp[50], nama_target[50], nama_pengirimpesan[50], key1[50], key2[50], ciphertext[50];
    char line[500]; // Deklarasi variabel line

	while (fgets(line, sizeof(line), file) != NULL) {
    int num_fields = sscanf(line, "%d, %d, %49[^,], %49[^,], %49[^,], %d, %49[^,], %49[^,], %49[^\n]",
                            &status, &id_pesan, timestamp, nama_target, nama_pengirimpesan, &type, key1, key2, ciphertext);

    if (num_fields == 8) {
        // Jika num_fields adalah 7, salin key2 ke ciphertext dan kosongkan key2
        strcpy(ciphertext, key2);
        key2[0] = '\0'; // Kosongkan key2
    } else if (num_fields != 9) {
        // Jika num_fields bukan 8, lanjutkan ke baris berikutnya
        continue;
    }

    // Pastikan ciphertext berisi data yang benar
    if (strlen(ciphertext) == 0) {
        // Jika ciphertext masih kosong, lanjutkan ke baris berikutnya
        continue;
    }

    // Buat node pesan baru
    MessageNode *newMessage = createMessageNode(status, id_pesan, timestamp, nama_target, nama_pengirimpesan, (CipherType)type, key1, key2, ciphertext);
    if (newMessage == NULL) {
        continue; // Lewati pesan yang tidak valid
    }

    // Tambahkan node pesan baru ke linked list
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

// Fungsi untuk menghitung jumlah pesan yang belum dibaca
int countUnreadMessages(MessageNode *head) {
    int count = 0;
    MessageNode *current = head;

    while (current != NULL) {
        if (current->status == 0) {
            count++;
        }
        current = current->next;
    }

    return count;
}

// Fungsi untuk menandai pesan sebagai sudah dibaca
void markMessageAsRead(MessageNode *head, int messageId) {
    MessageNode *current = head;

    while (current != NULL) {
        if (current->id_pesan == messageId) {
            current->status = 1;
            break;
        }
        current = current->next;
    }
}

void saveMessagesToFile(const char *filename, MessageNode *head) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("File tidak dapat dibuka untuk menulis.\n");
        return;
    }

    MessageNode *current = head;

    while (current != NULL) {
        switch (current->type) {
            case RAILFENCE:
                fprintf(file, "%d, %d, %s, %s, %s, %d, %d, %s",
                        current->status, current->id_pesan, current->timestamp, current->nama_target, current->nama_pengirimpesan,
                        current->type, current->cipher.railfence.keyangka, current->ciphertext);
                break;
            case HILL:
                fprintf(file, "%d, %d, %s, %s, %s, %d, %d, %s, %s",
                        current->status, current->id_pesan, current->timestamp, current->nama_target, current->nama_pengirimpesan,
                        current->type, current->cipher.hill.n2, current->cipher.hill.keyhuruf, current->ciphertext);
                break;
            case VERNAM:
                fprintf(file, "%d, %d, %s, %s, %s, %d, %s, %s",
                        current->status, current->id_pesan, current->timestamp, current->nama_target, current->nama_pengirimpesan,
                        current->type, current->cipher.vernam.keyhuruf, current->ciphertext);
                break;
            case VIGENERE:
                fprintf(file, "%d, %d, %s, %s, %s, %d, %s, %s",
                        current->status, current->id_pesan, current->timestamp, current->nama_target, current->nama_pengirimpesan,
                        current->type, current->cipher.vigenere.keyhuruf, current->ciphertext);
                break;
            case RSA:
                fprintf(file, "%d, %d, %s, %s, %s, %d, %d, %s",
                        current->status, current->id_pesan, current->timestamp, current->nama_target, current->nama_pengirimpesan,
                        current->type, current->cipher.rsa.p, current->cipher.rsa.q, current->ciphertext);
                break;
            default:
                break;
        }
        
        // Cek apakah current adalah node terakhir
        if (current->next != NULL) {
            fprintf(file, "\n");
        }
        
        current = current->next;
    }

    fclose(file);
}




void viewDecryptionKeyAndMessageUnRead(char nama_pengirimpesan[], MessageNode *head, const char *filename) {
    MessageNode *current = head;

    printf("=======================================================\n");
    printf("                 DAFTAR MENFES BELUM DIBACA            \n");
    printf("-------------------------------------------------------\n");
    printf("ID%-4sDate%-21sFrom\n", "", "");
    printf("-------------------------------------------------------\n");

    while (current != NULL) {
        // Hanya menampilkan pesan dengan status 0 (belum dibaca)
        if (current->status == 0) {
            printf("%-5d %-24s %-17s\n", current->id_pesan, current->timestamp, current->nama_pengirimpesan);
        }
        current = current->next;
    }

    int chosenId;
    printf("Mau Lihat Pesan Yang Mana? (Masukkan ID Pesan 1/2/...): ");
    scanf("%d", &chosenId);

    current = head;
    while (current != NULL) {
        if (current->id_pesan == chosenId && current->status == 0) {
            char decryptedMsg[300];
            // Inisialisasi matriks kunci
            char key_matrix[MAX][MAX];
            int key_matrix_num[MAX][MAX];
            int n, i, j;
            // Proses dekripsi berdasarkan method
            switch (current->type) {
                case RAILFENCE:
                    decryptRailFence(current->ciphertext, current->cipher.railfence.keyangka, decryptedMsg);
                    break;
                case HILL:
                    n = sqrt(strlen(current->cipher.hill.keyhuruf));
                    // Ubah kunci menjadi matriks kunci
                    generateKeyMatrix(n, current->cipher.hill.keyhuruf, key_matrix);

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
                        decryptMessage(key_matrix_num, inverse, current->ciphertext, decryptedMsg, n);
                    }
                    break;
                case VERNAM:
                    decryptVernam(current->ciphertext, current->cipher.vernam.keyhuruf, decryptedMsg);
                    break;
                case VIGENERE:
                    decryptVigenere(current->ciphertext, current->cipher.vigenere.keyhuruf, decryptedMsg);
                    break;
                case RSA:
                    // Logika dekripsi untuk method RSA
                    break;
                default:
                    printf("Invalid decryption method.\n");
                    return;
            }

            displayDecryptedMessage(decryptedMsg);
            current->status = 1; // Tandai pesan sebagai sudah dibaca
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


// Function to create a new message node
NodeBinary* createNodeBinary(int status, int id_pesan, const char *timestamp, const char *nama_target,
                             const char *nama_pengirimpesan, CipherType type, const char *key1, const char *key2, const char *ciphertext) {
    NodeBinary *newNode = (NodeBinary*)malloc(sizeof(NodeBinary));
    if (newNode != NULL) {
        newNode->status = status;
        newNode->id_pesan = id_pesan;
        strcpy(newNode->timestamp, timestamp);
        strcpy(newNode->nama_target, nama_target);
        strcpy(newNode->nama_pengirimpesan, nama_pengirimpesan);
        newNode->type = type;
        strcpy(newNode->key1, key1);
        strcpy(newNode->key2, key2);
        strcpy(newNode->ciphertext, ciphertext);
        newNode->left = newNode->right = NULL;
    }
    return newNode;
}

// Function to insert a message node into the binary search tree
NodeBinary* insertNodeBinary(NodeBinary *root, NodeBinary *newNode) {
    if (root == NULL) {
        return newNode;
    }

    if (newNode->id_pesan < root->id_pesan) {
        root->left = insertNodeBinary(root->left, newNode);
    } else if (newNode->id_pesan > root->id_pesan) {
        root->right = insertNodeBinary(root->right, newNode);
    }

    return root;
}

// Function to load messages from a file
NodeBinary* loadBinaryMessagesFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    NodeBinary *root = NULL;
    int id_pesan, type, status;
    char timestamp[50], nama_target[50], nama_pengirimpesan[50], key1[50], key2[50], ciphertext[50];
    char line[500]; // Buffer for reading lines from the file

    while (fgets(line, sizeof(line), file) != NULL) {
        int num_fields = sscanf(line, "%d,%d,%49[^,],%49[^,],%49[^,],%d,%49[^,],%49[^,\n]",
                                &status, &id_pesan, timestamp, nama_target, nama_pengirimpesan, &type, key1, key2, ciphertext);

        if (num_fields == 8) {
            // If num_fields is 8, copy key2 to ciphertext and clear key2
            strcpy(ciphertext, key2);
            key2[0] = '\0'; // Clear key2
        } else if (num_fields != 9) {
            // If num_fields is not 8 or 9, skip to the next line
            continue;
        }

        // Ensure ciphertext contains valid data
        if (strlen(ciphertext) == 0) {
            // If ciphertext is still empty, skip to the next line
            continue;
        }

        // Create a new message node
        NodeBinary *newMessage = createNodeBinary(status, id_pesan, timestamp, nama_target, nama_pengirimpesan, (CipherType)type, key1, key2, ciphertext);
        if (newMessage == NULL) {
            continue; // Skip invalid messages
        }

        // Insert the new message node into the binary search tree
        root = insertNodeBinary(root, newMessage);
    }

    fclose(file);
    return root;
}

// Function to save messages to a file
void saveBinaryMessagesToFile(const char *filename, NodeBinary *root) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    saveBinaryMessagesHelper(file, root);

    fclose(file);
}

// Helper function to recursively save messages to a file
void saveBinaryMessagesHelper(FILE *file, NodeBinary *node) {
    if (node != NULL) {
        if (strlen(node->key2) == 0) {
            fprintf(file, "%d,%d,%s,%s,%s,%d,%s,%s\n",
                    node->status, node->id_pesan, node->timestamp, node->nama_target,
                    node->nama_pengirimpesan, node->type, node->key1, node->ciphertext);
        } else {
            fprintf(file, "%d,%d,%s,%s,%s,%d,%s,%s,%s\n",
                    node->status, node->id_pesan, node->timestamp, node->nama_target,
                    node->nama_pengirimpesan, node->type, node->key1, node->key2, node->ciphertext);
        }
        saveBinaryMessagesHelper(file, node->left);
        saveBinaryMessagesHelper(file, node->right);
    }
}

// Function to print messages in-order (ascending by ID)
void printMessages(NodeBinary *root, const char *filename) {
    if(root != NULL) {
        printMessages(root->left, filename);
        printf("%-5d %-24s %-17s\n", root->id_pesan, root->timestamp, root->nama_target);
        printMessages(root->right, filename);
    }
}

void processMessages(NodeBinary *root, const char *filename) {
    printf("=======================================================\n");
    printf("                 DAFTAR MENFES MASUK                    \n");
    printf("-------------------------------------------------------\n");
    printf("ID%-4sDate%-21sFrom\n", "", "");
    printf("-------------------------------------------------------\n");
    printMessages(root, filename);

    int chosenId;
    printf("Mau Hapus Pesan Yang Mana? (Masukkan ID Pesan 1/2/...): ");
    scanf("%d", &chosenId);
    root = deleteNodeBinary(root, chosenId);

    printf("\nMessages after deletion:\n");
    printf("=======================================================\n");
    printf("                 DAFTAR MENFES MASUK                    \n");
    printf("-------------------------------------------------------\n");
    printf("ID%-4sDate%-21sFrom\n", "", "");
    printf("-------------------------------------------------------\n");
    printMessages(root, filename);

    // Save the updated messages to file
    saveBinaryMessagesToFile(filename, root);
}

// Function to find the node with the minimum value (leftmost) in a subtree
NodeBinary* minValueNode(NodeBinary *node) {
    NodeBinary *current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Function to delete a message node from the binary search tree based on ID
NodeBinary* deleteNodeBinary(NodeBinary *root, int id) {
    if (root == NULL) {
        return root;
    }

    if (id < root->id_pesan) {
        root->left = deleteNodeBinary(root->left, id);
    } else if (id > root->id_pesan) {
        root->right = deleteNodeBinary(root->right, id);
    } else {
        // Node with ID found, delete it
        if (root->left == NULL) {
            NodeBinary *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            NodeBinary *temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        NodeBinary *temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->id_pesan = temp->id_pesan;
        root->status = temp->status;
        strcpy(root->timestamp, temp->timestamp);
        strcpy(root->nama_target, temp->nama_target);
        strcpy(root->nama_pengirimpesan, temp->nama_pengirimpesan);
        root->type = temp->type;
        strcpy(root->key1, temp->key1);
        strcpy(root->key2, temp->key2);
        strcpy(root->ciphertext, temp->ciphertext);

        // Delete the inorder successor
        root->right = deleteNodeBinary(root->right, temp->id_pesan);
    }
    return root;
}
/****** END SESSION METHOD DEKRIPSI ******/
