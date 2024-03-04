#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

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

// Function to decrypt message using Hill Cipher
void hillCipher(int key[MAX_SIZE][MAX_SIZE], char *text, int n) {
    int len = strlen(text);
    int padded_len = len % n == 0 ? len : len + (n - len % n);

    char cipher_text[padded_len];
    strcpy(cipher_text, text);
    for (int i = len; i < padded_len; i++)
        cipher_text[i] = 'z';
    cipher_text[padded_len] = '\0';

    int message[MAX_SIZE][1];
    for (int i = 0; i < padded_len; i += n) {
        int col = 0;
        for (int j = i; j < i + n; j++) {
            message[col++][0] = tolower(cipher_text[j]) - 'a';
        }
        int res[MAX_SIZE][1] = {0};
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                res[j][0] += key[j][k] * message[k][0];
            }
            res[j][0] %= 26;
        }
        for (int j = 0; j < n; j++) {
            cipher_text[i + j] = 'a' + method(res[j][0], 26);
        }
    }
    printf("Decrypted message: %s\n", cipher_text);
}

int main() {
    int n;
    printf("Enter the order of square matrix: ");
    scanf("%d", &n);
    int key[MAX_SIZE][MAX_SIZE] = {0};

    char s[MAX_SIZE];
    printf("Enter the key: ");
    scanf("%s", s);
    int len = strlen(s);
    int det = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(s[i])) {
            key[i / n][i % n] = tolower(s[i]) - 'a';
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", key[i][j]);
        }
        printf("\n");
    }
    det = key[0][0] * key[1][1] * key[2][2] + key[0][1] * key[1][2] * key[2][0] + key[0][2] * key[1][0] * key[2][1] -
          (key[0][2] * key[1][1] * key[2][0] + key[0][0] * key[1][2] * key[2][1] + key[0][1] * key[1][0] * key[2][2]);
    det = method(det, 26);
    int det_inv = modInverse(det, 26);

    int inverse[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inverse[i][j] = (key[(j + 1) % n][(i + 1) % n] * key[(j + 2) % n][(i + 2) % n] -
                             key[(j + 1) % n][(i + 2) % n] * key[(j + 2) % n][(i + 1) % n]) *
                            det_inv;
            inverse[i][j] = method(inverse[i][j], 26);
        }
    }

    char text[MAX_SIZE];
    printf("Enter the text: ");
    scanf("%s", text);

    hillCipher(inverse, text, n);
    return 0;
}
