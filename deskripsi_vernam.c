#include <stdio.h>
#include <string.h>

void dekripsiVernam(char* cipher_text, char* key) {
	int i = 0;
    for (i; i < strlen(cipher_text); i++) {
        cipher_text[i] = tolower(cipher_text[i]);
    }
    i = 0;
    for (i; i < strlen(key); i++) {
        key[i] = tolower(key[i]);
    }
    char plain_text[strlen(cipher_text)];

    i = 0;
    for (i; i < strlen(cipher_text); i++) {
        int k1 = cipher_text[i] - 'a';
        int k2 = key[i] - 'a';
        char s = (((k1 - k2) + 26) % 26) + 'a';
        plain_text[i] = s;
    }
    plain_text[strlen(cipher_text)] = '\0';
    printf("Hasil dekripsi pesan adalah: %s\n", plain_text);
}

int mainDeskripsiVernam() {
    char plain_text[100];
    char key[100];
    printf("Masukkan pesan untuk didekripsi: ");
    fgets(plain_text, sizeof(plain_text), stdin);
    printf("Masukkan kunci one time pad: ");
    fgets(key, sizeof(key), stdin);
    dekripsiVernam(plain_text, key);
    return 0;
}

