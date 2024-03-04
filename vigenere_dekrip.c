#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Fungsi untuk menghapus spasi dari string
void removeSpaces(char *str) {
    int i, count = 0;
    for (i = 0; str[i]; i++) {
        if (str[i] != ' ')
            str[count++] = str[i];
    }
    str[count] = '\0';
}

// Fungsi untuk melakukan dekripsi teks menggunakan Vigenere Cipher
void decryptVigenere(char *text, const char *key) {
    int textLength = strlen(text);
    int keyLength = strlen(key);
    int i, j;

    for (i = 0, j = 0; i < textLength; ++i) {
        // Periksa apakah karakter adalah huruf
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char keyChar = tolower(key[j % keyLength]);
            // Dekripsi karakter
            text[i] = (text[i] - base - (keyChar - 'a') + 26) % 26 + base;
            ++j;
        }
    }
}

int mainVigenere_dekrip() {
    char text[100]; // Asumsikan teks yang dienkripsi tidak lebih dari 100 karakter
    char key[100]; // Asumsikan kunci tidak lebih dari 100 karakter

    // Input teks yang dienkripsi dari pengguna
    printf("Masukkan teks yang dienkripsi: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Menghapus karakter newline dari input teks

    // Input kunci dari pengguna dan menghapus spasi
    printf("Masukkan kunci: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Menghapus karakter newline dari input kunci
    removeSpaces(key);

    printf("Teks sebelum didekripsi: %s\n", text);

    decrypt(text, key);

    printf("Teks setelah didekripsi: %s\n", text);

    return 0;
}

