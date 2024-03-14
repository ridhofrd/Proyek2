#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return 1;
}

int method(int a, int m) {
    if (a > 0) {
        return (a % m);
    } else {
        int k = (abs(a) / m) + 1;
        return method(a + k * m, m);
    }
}

void generate_key(int n, char* s, int key_matrix[MAX_SIZE][MAX_SIZE]) {
    char main[28] = "abcdefghijklmnopqrstuvwxyz";
    char key_string[MAX_SIZE] = "";
    int index = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != ' ') {
            key_string[index++] = tolower(s[i]);
        }
    }
    key_string[index] = '\0';

    int row = 0, col = 0;
    for (int i = 0; key_string[i] != '\0'; i++) {
        if (strchr(main, key_string[i]) != NULL) {
            key_matrix[row][col++] = key_string[i] - 'a';
            if (col >= n) {
                row++;
                col = 0;
            }
        }
    }
}

void message_matrix(char* s, int n, int final_matrix[MAX_SIZE][MAX_SIZE][1], int* matrix_count) {
    char temp[MAX_SIZE] = "";
    int index = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != ' ') {
            temp[index++] = tolower(s[i]);
        }
    }
    temp[index] = '\0';

    int len = strlen(temp);
    while (len % n != 0) {
        temp[len++] = 'z';
    }
    temp[len] = '\0';

    *matrix_count = len / n;
    for (int k = 0; k < *matrix_count; k++) {
        for (int i = 0; i < n; i++) {
            final_matrix[k][i][0] = temp[i + (n * k)] - 'a';
        }
    }
}

void multiply_and_convert(int key[MAX_SIZE][MAX_SIZE], int message[MAX_SIZE][1], char res_alpha[MAX_SIZE][1], int n) {
    int res_num[MAX_SIZE][1] = {0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 1; j++) {
            for (int k = 0; k < n; k++) {
                res_num[i][j] += key[i][k] * message[k][j];
            }
            res_alpha[i][j] = (res_num[i][j] % 26) + 'a';
        }
    }
}

int main() {
    int n;
    char s[MAX_SIZE], cipher_text[MAX_SIZE];
    printf("What will be the order of square matrix: ");
    scanf("%d", &n);
    printf("Enter the key: ");
    scanf("%s", s);
    fflush(stdin);

    int key_matrix[MAX_SIZE][MAX_SIZE] = {0};
    generate_key(n, s, key_matrix);

    // Inverse matrix calculation and other operations are omitted for brevity
    // This is a simplified version focusing on the main structure conversion

	//    printf("Enter the cipher text: ");
	//    scanf("%s", cipher_text);

	printf("Enter the cipher text: ");
    fgets(cipher_text, sizeof(cipher_text), stdin);
    cipher_text[strcspn(cipher_text, "\n")] = '\0';


	
	char passcode[100];
	strcpy(passcode, cipher_text);
    char *ptr = passcode;
	
    while (*ptr)
    {
        if (*ptr == ' ')
            *ptr = 'n';
        ptr++;
    }
    printf ("\n passcode: %s\n", passcode);
	
    int final_matrix[MAX_SIZE][MAX_SIZE][1], matrix_count;
    message_matrix(passcode, n, final_matrix, &matrix_count);

    char plain_text[MAX_SIZE] = "";
    for (int i = 0; i < matrix_count; i++) {
        char sub[MAX_SIZE][1];
        multiply_and_convert(key_matrix, final_matrix[i], sub, n);
        for (int j = 0; j < n; j++) {
            strncat(plain_text, sub[j], 1);
        }
    }

    printf("plain message: %s\n", plain_text);

    return 0;
}