#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char main_alphabet[] = "abcdefghijklmnopqrstuvwxyz";

// Prototipe fungsi
void generateKeyMatrix(int n, char *s, char key_matrix[MAX][MAX]);
int determinant(int mat[MAX][MAX], int n);
void getCofactor(int mat[MAX][MAX], int temp[MAX][MAX], int p, int q, int n);
void adjoint(int mat[MAX][MAX], int adj[MAX][MAX], int n);
int modInverse(int a, int m);
void multiplyMatrix(int key[MAX][MAX], int message[MAX][1], int res[MAX][1], int n);
void decryptMessage(int key[MAX][MAX], int inverse[MAX][MAX], char cipher_text[], int n);

// Implementasi fungsi
void generateKeyMatrix(int n, char *s, char key_matrix[MAX][MAX]) {
    int len = strlen(s);
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
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
    for (int f = 0; f < n; f++) {
        getCofactor(mat, temp, 0, f, n);
        det += sign * mat[0][f] * determinant(temp, n - 1);
        sign = -sign;
    }
    return det;
}

void getCofactor(int mat[MAX][MAX], int temp[MAX][MAX], int p, int q, int n) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
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
    int sign = 1, temp[MAX][MAX];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            getCofactor(mat, temp, i, j, n);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = (sign) * (determinant(temp, n - 1));
        }
    }
}

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return 1;
}

void multiplyMatrix(int key[MAX][MAX], int message[MAX][1], int res[MAX][1], int n) {
    for (int i = 0; i < n; i++) {
        res[i][0] = 0;
        for (int j = 0; j < 1; j++) {
            for (int k = 0; k < n; k++) {
                res[i][j] += key[i][k] * message[k][j];
            }
        }
    }
}

void decryptMessage(int key[MAX][MAX], int inverse[MAX][MAX], char cipher_text[], int n) {
    int len = strlen(cipher_text);
    int rows = len / n;

    char plain_text[MAX] = "";
    int k = 0;
    for (int r = 0; r < rows; r++) {
        int message[MAX][1], result[MAX][1];
        for (int i = 0; i < n; i++) {
            message[i][0] = cipher_text[k++] - 'a';
        }

        multiplyMatrix(inverse, message, result, n);

        for (int i = 0; i < n; i++) {
            int num = (result[i][0] % 26);
            if (num < 0) num += 26; // Menangani nilai negatif
            plain_text[strlen(plain_text)] = num + 'a';
        }
    }

    plain_text[len] = '\0'; // Mengakhiri string dengan null terminator
    printf("Plain Text: %s\n", plain_text);
}


//void decryptMessage(int key[MAX][MAX], int inverse[MAX][MAX], char cipher_text[], int n) {
//    int len = strlen(cipher_text);
//    int rows = len / n;
//
//    char plain_text[MAX] = "";
//    int k = 0;
//    for (int r = 0; r < rows; r++) {
//        int message[MAX][1], result[MAX][1];
//        for (int i = 0; i < n; i++) {
//            message[i][0] = cipher_text[k++] - 'a';
//        }
//
//        multiplyMatrix(inverse, message, result, n);
//
//        for (int i = 0; i < n; i++) {
//            int num = result[i][0] % 26;
//            if (num < 0) {
//                num += 26; // Jika hasil modulo negatif, tambahkan 26
//            }
//            plain_text[strlen(plain_text)] = num + 'a';
//        }
//    }
//
//    printf("Plain Text: %s\n", plain_text);
//}



void printMatrix(int mat[MAX][MAX], int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}


int main() {
    int n;
    char s[MAX];
    printf("What will be the order of square matrix: ");
    scanf("%d", &n);
    printf("Enter the key: ");
    scanf("%s", s);

    char key_matrix[MAX][MAX] = {0};
    generateKeyMatrix(n, s, key_matrix);

    int key[MAX][MAX];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            key[i][j] = key_matrix[i][j] - 'a';
        }
    }

    int det = determinant(key, n);
    printf("Determinant: %d\n", det);

    if (det != 0) {
        int adj[MAX][MAX];
        adjoint(key, adj, n);

        printf("Adjoint Matrix:\n");
        printMatrix(adj, n, n);

        int det_inv = modInverse(det, 26);
        printf("Inverse of Determinant: %d\n", det_inv);

        int inverse[MAX][MAX];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                inverse[i][j] = ((adj[i][j] % 26) * det_inv) % 26;
                if (inverse[i][j] < 0) {
                    inverse[i][j] += 26;
                }
            }
        }

        printf("Inverse Matrix:\n");
        printMatrix(inverse, n, n);

        char cipher_text[MAX];
        printf("Enter the cipher text: ");
        scanf("%s", cipher_text);

        decryptMessage(key, inverse, cipher_text, n);
    } else {
        printf("Matrix cannot be inverted\n");
    }

    return 0;
}
