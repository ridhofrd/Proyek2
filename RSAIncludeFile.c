#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

long int p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], en[100], i;
char msg[100];

int prime(long int);
void ce();
long int cd(long int);
void encrypt();
void saveEncryptedMessageToFile(char encryptedMsg[], char filename[]);
void decryptFromFile();
void saveDecryptedMessageToFile(char decryptedMsg[], char filename[]);
char* decrypt(long int p, long int q, char encryptedMsg[]);

int prime(long int pr)
{
    int i;
    if (pr == 1)
        return 0;

    for (i = 2; i <= sqrt(pr); i++)
    {
        if (pr % i == 0)
            return 0;
    }
    return 1;
}

void ce()
{
    int k;
    k = 0;
    for (i = 2; i < t; i++)
    {
        if (t % i == 0)
            continue;
        flag = prime(i);
        if (flag == 1 && i != p && i != q)
        {
            e[k] = i;
            flag = cd(e[k]);
            if (flag > 0)
            {
                d[k] = flag;
                k++;
            }
            if (k == 99)
                break;
        }
    }
}

long int cd(long int x)
{
    long int k = 1;
    while (1)
    {
        k = k + t;
        if (k % x == 0)
            return (k / x);
    }
}
long int gcd(long int a, long int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}


long int findE(long int t) {
    long int e;
    for (e = 2; e < t; e++) {
        if (gcd(e, t) == 1) {
            return e;
        }
    }
    return -1; // Menandakan kesalahan jika tidak menemukan nilai e yang sesuai
}



void encrypt()
{
    long int pt, ct, key = e[0], k, len;
    i = 0;
    len = strlen(msg);
    while (i < len)
    {
        pt = m[i];
        pt = pt - 96;
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * pt;
            k = k % n;
        }
        temp[i] = k;
        ct = k + 96;
        en[i] = ct;
        i++;
    }
    en[i] = -1;
    printf("\nTHE ENCRYPTED MESSAGE IS:\n");
    for (i = 0; en[i] != -1; i++)
        printf("%c", (char)en[i]);
}

//void decrypt()
//{
//    long int pt, ct, key = d[0], k;
//    i = 0;
//    while (en[i] != -1)
//    {
//        ct = temp[i];
//        k = 1;
//        for (j = 0; j < key; j++)
//        {
//            k = k * ct;
//            k = k % n;
//        }
//        pt = k + 96;
//        m[i] = pt;
//        i++;
//    }
//    m[i] = -1;
//    printf("\nTHE DECRYPTED MESSAGE IS:\n");
//    for (i = 0; m[i] != -1; i++)
//        printf("%c", (char)m[i]);
//}

char* decrypt(long int p, long int q, char encryptedMsg[])
{
    long int n = p * q;
    long int t = (p - 1) * (q - 1);
    long int key = d[0];

    long int pt, ct, k;
    i = 0;
    char* decryptedMsg = (char*)malloc(100 * sizeof(char));

    while (encryptedMsg[i] != -1)
    {
        ct = encryptedMsg[i];
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * ct;
            k = k % n;
        }
        pt = k + 96;
        decryptedMsg[i] = (char)pt;
        i++;
    }
    decryptedMsg[i] = '\0';

    return decryptedMsg;
}

int main()
{
    char filename[100];

    // Input prime numbers and message
    printf("ENTER FIRST PRIME NUMBER: ");
    scanf("%ld", &p);
    flag = prime(p);
    if (flag == 0 || p == 1)
    {
        printf("WRONG INPUT\n");
        exit(1);
    }

    printf("ENTER ANOTHER PRIME NUMBER: ");
    scanf("%ld", &q);
    flag = prime(q);
    if (flag == 0 || q == 1 || p == q)
    {
        printf("WRONG INPUT\n");
        exit(1);
    }

    printf("ENTER MESSAGE: ");
    scanf(" %[^\n]s", msg);
    for (i = 0; i < strlen(msg); i++)
        m[i] = msg[i];

    n = p * q;
    t = (p - 1) * (q - 1);

    ce();

    printf("\nPOSSIBLE VALUES OF e AND d ARE:\n");
    for (i = 0; i < j - 1; i++)
        printf("%ld\t%ld\n", e[i], d[i]);

    encrypt();

    // Save encrypted message to file
    FILE *file;
    printf("\nEnter the filename to save the encrypted message and keys: ");
    scanf("%s", filename);

    file = fopen(filename, "w");
    if (file != NULL)
    {
        fprintf(file, "%ld, %ld, ", p, q);
        for (i = 0; en[i] != -1; i++)
            fprintf(file, "%c", (char)en[i]);
        fclose(file);

        printf("\nEncrypted message and keys saved to file: %s\n", filename);
    }
    else
    {
        printf("\nError saving encrypted message to file.\n");
    }

    // Decrypt from file
    decryptFromFile();

    return 0;
}

void decryptFromFile()
{
    char filename[100];
    FILE* file;
    char encryptedMsg[100]; // Sesuaikan ukuran dengan kebutuhan

    printf("\nEnter the filename containing the encrypted message and keys: ");
    scanf("%s", filename);

    file = fopen(filename, "r");

    if (file != NULL)
    {
        // Read the encrypted message and keys from the file
        long int p, q;
        fscanf(file, "%ld, %ld, %s", &p, &q, encryptedMsg);
		printf("THE enkrip MESSAGE from file : %s\n", encryptedMsg);
        printf("THE DECRYPTED MESSAGE IS: %s\n", decrypt(p, q, encryptedMsg));

        fclose(file);
    }
    else
    {
        printf("\nError opening file.\n");
    }
}

