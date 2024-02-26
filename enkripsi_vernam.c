#include <stdio.h>
#include <string.h>

void enkripsiVernam(char* plain_text, char* key) {
    int len = strlen(plain_text);
    char cipher_text[len];
    memset(cipher_text, '\0', sizeof(cipher_text));
    
    int i = 0;

    for (i; i < len; i++) {
        plain_text[i] = tolower(plain_text[i]);
        key[i] = tolower(key[i]);
    }

    if (strlen(plain_text) != strlen(key)) {
        printf("Panjang plain text dan chiper text harus sama\n");
    } else {
        int i = 0;
        for (i; i < len; i++) {
            int k1 = plain_text[i] - 'a';
            int k2 = key[i] - 'a';
            char s = ((k1 + k2) % 26) + 'a';
            cipher_text[i] = s;
        }
        printf("Hasil enkripsi pesan adalah: %s\n", cipher_text);
    }
}

int main() {
    char plain_text[100];
    char key[100];

    printf("Masukkan pesan yang akan dienkripsi: ");
    fgets(plain_text, sizeof(plain_text), stdin);
    plain_text[strcspn(plain_text, "\n")] = '\0';

    printf("Masukkan kunci one time pad: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    enkripsiVernam(plain_text, key);

    return 0;
}
