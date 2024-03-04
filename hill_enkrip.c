#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Function to calculate determinant of matrix
int determinantOfMatrix(int mat[MAX_SIZE][MAX_SIZE], int n) {
    int D = 0;
    if (n == 1)
        return mat[0][0];

    int temp[MAX_SIZE][MAX_SIZE];
    int sign = 1;
    for (int f = 0; f < n; f++) {
        int i = 0, j = 0;
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                if (row != 0 && col != f) {
                    temp[i][j++] = mat[row][col];
                    if (j == n - 1) {
                        j = 0;
                        i++;
                    }
                }
            }
        }
        D += sign * mat[0][f] * determinantOfMatrix(temp, n - 1);
        sign = -sign;
    }
    return D;
}

// Function to calculate modulo inverse of a number
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return 1;
}

// Function to calculate modulo operation considering negative numbers
int method(int a, int m) {
    if (a > 0)
        return (a % m);
    else {
        int k = (abs(a) / m) + 1;
        return method(a + k * m, m);
    }
}

// Function to generate key matrix
void generateKey(int key[MAX_SIZE][MAX_SIZE], char *s, int n) {
    int len = strlen(s);
    int row = 0, col = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(s[i])) {
            key[row][col++] = tolower(s[i]) - 'a';
            if (col == n) {
                col = 0;
                row++;
            }
        }
    }
}

// Function to encrypt message using Hill Cipher
void hillEncrypt(int key[MAX_SIZE][MAX_SIZE], char *text, int n) {
    int len = strlen(text);
    int padded_len = len % n == 0 ? len : len + (n - len % n);

    char plain_text[padded_len];
    strcpy(plain_text, text);
    for (int i = len; i < padded_len; i++)
        plain_text[i] = 'z';
    plain_text[padded_len] = '\0';

    int message[MAX_SIZE][1];
    for (int i = 0; i < padded_len; i += n) {
        int col = 0;
        for (int j = i; j < i + n; j++) {
            message[col++][0] = tolower(plain_text[j]) - 'a';
        }
        int res[MAX_SIZE][1] = {0};
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                res[j][0] += key[j][k] * message[k][0];
            }
            res[j][0] %= 26;
        }
        for (int j = 0; j < n; j++) {
            plain_text[i + j] = 'a' + res[j][0];
        }
    }
    printf("Encrypted message: %s\n", plain_text);
}

int main() {
    int n;
    printf("Enter the order of square matrix: ");
    scanf("%d", &n);
    int key[MAX_SIZE][MAX_SIZE] = {0};

    char s[MAX_SIZE];
    printf("Enter the key: ");
    scanf("%s", s);
    generateKey(key, s, n);

    char text[MAX_SIZE];
    printf("Enter the text: ");
    scanf("%s", text);

    hillEncrypt(key, text, n);
    return 0;
}
