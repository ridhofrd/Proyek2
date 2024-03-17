/* File		 : method_decrypt.c							*/
/* Deskripsi : Unit untuk keperluan ADT Decrypt_Method	*/

#include "decrypt.h"

/****** START METHOD DEKRIPSI RAIL FENCE ******/
// Procedure untuk mendekripsi pesan menggunakan metode Rail Fence
// encryptedMsg : parameter input bertype array of char, pesan yang telah dienkripsi
// key : parameter input bertipe integer, kunci untuk dekripsi Rail Fence
// decryptedMsg : parameter output bertype array of char, pesan yang telah didekripsi
void decryptRailFence(char encryptedMsg[], int key, char decryptedMsg[]) {
    int len = strlen(encryptedMsg), i, j; // mendapatkan panjang pesan terenkripsi
    char railMatrix[key][len]; // Matriks untuk menyimpan pesan terdekripsi dalam pola Rail Fence.

    // Initialize the matrix with null characters
    for (i = 0; i < key; ++i)
        for (j = 0; j < len; ++j)
            railMatrix[i][j] = '\0';

    // Tentukan posisi rel pada rail berdasarkan kunci
    int railPos[len];
    int currentRail = 0;
    int changeDirection = 0;
    for (i = 0; i < len; ++i) {
        railPos[i] = currentRail;
        if (currentRail == 0 || currentRail == key - 1) { //  Memeriksa apakah perlu mengubah arah rail.
            changeDirection = !changeDirection;
        }
        currentRail += (changeDirection ? 1 : -1); // Mengubah posisi rail berdasarkan arah yang ditentukan.
    }

    // Fill the matrix with the encrypted message
    int k = 0;
    for (i = 0; i < key; ++i) {
        for (j = 0; j < len; ++j) {
            if (railPos[j] == i) { // Memeriksa apakah pesan terenkripsi harus dimasukkan ke dalam matriks pada posisi ini.
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
// Procedure untuk mendekripsi pesan menggunakan metode Vigenere
// encryptedMsg : parameter input bertipe pointer to const char, pesan yang telah dienkripsi
// key : parameter input bertipe pointer to const char, kunci untuk dekripsi Vigenere
// decryptedMsg : parameter output bertipe pointer to char, pesan yang telah didekripsi
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
// Procedure untuk mendekripsi pesan menggunakan metode Vernam
// cipher_text : parameter input bertipe pointer to char, pesan yang telah dienkripsi
// key : parameter input bertipe pointer to char, kunci untuk dekripsi Vernam
// decryptedMsg : parameter output bertipe pointer to char, pesan yang telah didekripsi
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
// Procedure untuk menampilkan pesan yang telah didekripsi
// decryptedMsg : parameter input bertipe pointer to char, pesan yang telah didekripsi
void displayDecryptedMessage(const char *decryptedMsg) {
    printf("\nINI ISI DEKRIPSI PESAN MENFES ANDA\n");
    printf("=======================================================\n");
    printf("%s\n", decryptedMsg);
    printf("=======================================================\n\n");
}

// Procedure untuk menampilkan daftar menfess dan mendekripsi sesuai dengan methodnya 
void viewDecryptionKeyAndMessage(char nama_pengirimpesan[]) {
    FILE *file;
    char filename[100];
    char timestamp[100];
    char key_matrix[MAX][MAX] = {0};
    sprintf(filename, "Nematoda-Nematoda.txt");
    if ((file = fopen(filename, "r")) != NULL) {
        int id_pesan, method, n, i, j;
        char nama_target[50], nama_pengirimpesan[100], encryptedMsg[100], key[100];

        printf("=======================================================\n");
        printf("                 DAFTAR MENFES MASUK                    \n");
        printf("-------------------------------------------------------\n");
		//        printf("ID\tDate\t\t\tFrom\n");
		printf("ID%-4sDate%-21sFrom\n", "", "");
        printf("-------------------------------------------------------\n");
        int totalMessages = 0; // Menyimpan total pesan yang dibaca
	// Membaca dan menampilkan daftar pesan yang masuk
        while (fscanf(file, "%d, %[^,], %[^,], %[^,], %d, %[^,], %[^\n]", &id_pesan, timestamp, nama_target, nama_pengirimpesan, &method, key, encryptedMsg) == 7) {
            totalMessages++;
          	printf("%-5d %-24s %-17s\n", id_pesan, timestamp, nama_pengirimpesan);
        }

        fclose(file);

        int chosenId;
        printf("Mau Lihat Pesan Yang Mana? (Masukkan ID Pesan 1/2/...): ");
        scanf("%d", &chosenId);
	// Membuka kembali file untuk membaca pesan yang dipilih untuk didekripsi
        if ((file = fopen(filename, "r")) != NULL) {
    		int found = 0;
    		char keyForSearch[100]; // Variabel untuk menyimpan key yang akan dikonversi
    		char *endptr;
    		long int keyangka; // Variabel untuk menyimpan hasil konversi key
    		int n = 0; // Variabel untuk menyimpan ukuran matriks
		// Membaca file untuk mencari pesan yang sesuai dengan ID yang dipilih
    		while (fscanf(file, "%d, %[^,], %[^,], %[^,], %d", &id_pesan, timestamp, nama_target, nama_pengirimpesan, &method) == 5) {
        		// Jika metode adalah 2 (Hill Cipher) yang memiliki dua kunci
			if (method == 2) {
		            // Jika metode adalah 2, maka baca nilai n dan matriks kunci
		            fscanf(file, ", %d", &n);
					//	printf("Matrix Size (n): %d\n", n);
		            // Baca parameter tambahan
		            fscanf(file, ", %[^,], %[^\n]", keyForSearch, encryptedMsg);
        		} else {
		            // Jika metode selain 2, baca parameter lainnya
		            fscanf(file, ", %[^,], %[^\n]", keyForSearch, encryptedMsg);
        		}
			// Jika ID pesan sesuai dengan yang dipilih
        		if (id_pesan == chosenId) {
            		found = 1;
		            // Melakukan konversi key menjadi angka untuk kebutuhan dekripsi
		            long int convertedValue = strtol(keyForSearch, &endptr, 10);
		            // Memeriksa apakah konversi berhasil
		            if (*endptr == '\0' || *endptr == '\n') {
		                keyangka = convertedValue;
		            }
		            // Perform decryption based on the chosen method
		            char decryptedMsg[100];
		            int key_matrix_num[MAX][MAX];
		            switch (method) {
                	case 1: // Rail Fence Cipher
	                    decryptRailFence(encryptedMsg, keyangka, decryptedMsg);
	                    break;
                	case 2: // Hill Cipher
				// Inisialisasi matriks kunci dengan nol
						memset(decryptedMsg, 0, sizeof(decryptedMsg));
				// Menghasilkan matriks kunci
				    	generateKeyMatrix(n, keyForSearch, key_matrix);
					    // Mengkonversi matriks kunci menjadi angka (0-25)
					    for (i = 0; i < n; i++) {
					        for (j = 0; j < n; j++) {
					            key_matrix_num[i][j] = key_matrix[i][j] - 'a';
					        }
					    }
						//	printKeyMatrix(key_matrix_num, n);
						//  printN(n);				
					    // Hitung determinan matriks kunci
					    int det = determinant(key_matrix_num, n);
						//	printf("Determinant: %d\n", det);	
	                    // Jika determinan tidak nol, lanjutkan proses dekripsi
	                    if (det != 0) {
	                        int adj[MAX][MAX];
	                        adjoint(key_matrix_num, adj, n);
	
							//	printf("Adjoint Matrix:\n");
							//	printMatrix(adj, n, n);
	
	                        // Hitung invers determinan
	                        int det_inv = modInverse(det, 26);
							//	printf("Inverse of Determinant: %d\n", det_inv);
	
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
							//	printf("Inverse Matrix:\n");
							//	printMatrix(inverse, n, n);	
	                        // Lakukan dekripsi menggunakan matriks kunci dan matriks invers
							decryptMessage(key_matrix_num, inverse, encryptedMsg, decryptedMsg, n); // Panggil fungsi decryptMessage
	                    } else {
	                        printf("Matrix cannot be inverted\n");
	                    }
	                    break;
	                case 3: // Vernam Cipher
	                    decryptVernam(encryptedMsg, keyForSearch, decryptedMsg);
	                    break;
	                case 4: // Vigenere Cipher
	                    decryptVigenere(encryptedMsg, keyForSearch, decryptedMsg);
	                    break;
	                default:
	                    printf("Invalid decryption method.\n");
	                    fclose(file);
	                    return;
            		}

		            // Display the decrypted message
					displayDecryptedMessage(decryptedMsg);
		
		            fclose(file);
		            return;
        		}
    		}
		    if (!found) {
		        printf("Pesan dengan ID %d tidak ditemukan.\n\n", chosenId);
		    }
		    fclose(file);
		} else {
    		printf("File tidak dapat dibuka.\n");
		}
    } else {
        printf("File tidak ditemukan.\n");
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
