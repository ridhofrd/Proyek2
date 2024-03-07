#include <stdio.h>
#include <string.h>
#include <ctype.h>

void removeSpaces(char *str) {
    int i, count = 0;
    for (i = 0; str[i]; i++) {
        if (str[i] != ' ')
            str[count++] = str[i];
    }
    str[count] = '\0';
}

void vigenere_encrypt(const char *plaintext, const char *key, char *encrypted) {
    int i, j;
    int plaintext_length = strlen(plaintext);
    int key_length = strlen(key);

    for (i = 0, j = 0; i < plaintext_length; i++, j++) {
        if (j == key_length)
            j = 0;

        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            encrypted[i] = 'a' + (plaintext[i] - 'a' + key[j] - 'a') % 26;
        } else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            encrypted[i] = 'A' + (plaintext[i] - 'A' + key[j] - 'a') % 26;
        } else {
            encrypted[i] = plaintext[i];
            j--;
        }
    }
    encrypted[i] = '\0';
}

int main() {
    char plaintext[100];
    char key[100];
    char encrypted[100];

    printf("Enter plain text: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0; // Removing newline character from fgets input

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0; // Removing newline character from fgets input

    removeSpaces(key); // Menghapus spasi dan mengubah ke huruf kecil

    vigenere_encrypt(plaintext, key, encrypted);

    printf("Plain text: %s\n", plaintext);
    printf("Key: %s\n", key);
    printf("Encrypted text: %s\n", encrypted);

    return 0;
}
