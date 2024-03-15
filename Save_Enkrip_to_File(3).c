#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include<math.h>
#include <time.h>

#define MAX_SIZE 100
#define MAX_MEMBERS 100

//variabel ridho
//long int p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], en[100], i;
long int p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], en[100];
char timestamp[20];
//char msg[100];

int prime(long int);
void ce();
long int cd(long int);
void encrypt();
void decrypt();
//end variabel ridho

// Definisikan struktur data untuk menyimpan informasi pengguna
typedef struct {
    int id;
    char username[50];
    char password[50];
    char nim[20];
    char kelas[10];
} Member;

// Fungsi untuk membaca data member dari file
int readMembersFromFile(Member *members) {
    FILE *file = fopen("mahasiswa.txt", "r");
    if (file == NULL) {
        printf("File mahasiswa.txt tidak dapat dibuka.\n");
        return 0;
    }

    int numMembers = 0;
    // Baca data pengguna dari file dan simpan dalam variabel members
//    while (fscanf(file, "%[^,],%[^,],%[^\n]\n", members[numMembers].nama, members[numMembers].username, members[numMembers].password) == 3 && numMembers < MAX_MEMBERS) {
//        numMembers++;
//    }
	while (numMembers < MAX_MEMBERS && fscanf(file, "%d %s %s %s %s\n", &members[numMembers].id, members[numMembers].username, members[numMembers].password, members[numMembers].nim, members[numMembers].kelas) == 5) {
        numMembers++;
    }


    if (numMembers == 0) {
        // Jika tidak berhasil membaca file, keluar dari program
        return 1;
    }

    // Tutup file setelah selesai membaca
    fclose(file);
    return numMembers;
}

void printMenu() {
    printf("Mau kirim menfess ke siapa?\n");
}

void printOptions() {
    printf("\nPilihan opsi:\n");
    printf("1. Pilih tujuan kirim menfess\n");
    printf("2. Kembali ke menu utama\n");
}

int processOption() {
    int option = 0;
    printf("\nPilihan opsi: ");
    scanf("%d", &option);
    if (option == 1) {
        // Handle option 1: Kirim pesan
        int targetID;
        printf("\nMasukkan nomor id tujuan yang ingin anda buatkan menfess : ");
        scanf("%d", &targetID);
        printf("Mengirim pesan ke ID %d...\n", targetID);
        return targetID;
    } else if (option == 2) {
        // Handle option 2: Kembali ke menu utama
        printf("Kembali ke menu utama...\n");
    } else {
        printf("Pilihan tidak valid.\n");
    }
}

char *getUsernameFromID(int targetID, Member *members, int numMembers) {
    for (int i = 0; i < numMembers; i++) {
        if (members[i].id == targetID) {
            return members[i].username;
        }
    }
    return NULL; // ID tidak ditemukan
}

void printMembers(Member *members, int numMembers, char *loggedInUsername) {
    int i;
    for (i = 0; i < numMembers; i++) {
        // Cek apakah username dalam data member sama dengan username yang sedang login
        if (strcmp(members[i].username, loggedInUsername) == 0) {
            // Jika sama, lanjut ke pengguna berikutnya
            continue;
        }
        // Jika tidak sama, cetak nomor indeks dan nama
        printf("%d. %s\n", members[i].id, members[i].username);
    }
}

void selectMetode(int *selectedOption, char *msg) {
	printf("Enter the message : ");
	scanf(" %[^\n]s", msg);
	printf("ini pesan: %s\n", msg);
	
    printf("\n====================\n");
    printf("1. Railfence Encryption\n");
    printf("2. Hill Encryption\n");
    printf("3. Vernam Encryption\n");
    printf("4. Vigenere Encryption\n");
    printf("5. RSA\n");
    printf("====================\n");

    printf("Pilihan metode enkripsi yang ingin digunakan : ");
    scanf("%d", selectedOption);
    printf("====================\n");
}

//fungsi tambahan dian
// Function to read the last used message ID from file
int getLastMessageId(char filename[]) {
    FILE *file = fopen(filename, "r");
    int lastId = 0;

    if (file != NULL) {
        int id;
        char line[100];  // Assuming a reasonable maximum line length

        while (fgets(line, sizeof(line), file) != NULL) {
            sscanf(line, "%d", &id);
            lastId = id; // Update lastId for each line until the end of the file
        }

        fclose(file);
    }

    return lastId;
}

// Function to generate a unique ID for each message
int generateUniqueId(char filename[]) {
    int lastMessageId = getLastMessageId(filename);
    return ++lastMessageId;
}

//end dian

//ini enkrip hill

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

//end enkrip hill

//vernam - rafka

void enkripsiVernam(char* plain_text, char* key, char *cipher_text) {
    int len = strlen(plain_text);
//    char cipher_text[len];
//    memset(cipher_text, '\0', sizeof(cipher_text));
    
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
        
    }
}
//end rafka


//RSA - sepuh ketua ridho

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
    int i, t;
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

void encrypt(char *msg)
{
    long int pt, ct, key = e[0], k, len;
    printf("ini pesannnn : %s \n",msg);
    int i = 0;
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


void decrypt()
{
    long int pt, ct, key = d[0], k;
        int i;
		i = 0;
    while (en[i] != -1)
    {
        ct = temp[i];
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * ct;
            k = k % n;
        }
        pt = k + 96;
        m[i] = pt;
        i++;
    }
    m[i] = -1;
    printf("\nTHE DECRYPTED MESSAGE IS:\n");
    for (i = 0; m[i] != -1; i++)
        printf("%c", (char)m[i]);
}

//end ridho

//timestamp
// Function to get the current timestamp with minute and second
void getCurrentTimestamp(char timestamp[]) {
    time_t rawtime;
    struct tm *info;

    time(&rawtime);
    info = localtime(&rawtime);

    strftime(timestamp, 20, "%d/%m/%Y %H:%M:%S", info);
}

// Function to save encrypted message to file
void saveEncryptedMessageToFile(char nama_target[], char nama_pengirimpesan[], char msg[], int encryptionMethod) {
	printf("%s \n", nama_target);
	printf("%s \n",nama_pengirimpesan);
	printf("%s \n",msg);
	printf("%d \n",encryptionMethod);
	
    // File handling
    FILE *file;
    char filename[100];

	char encryptedMsg[100]; // Adjust the size as needed
    int msgLen = strlen(msg); // Added to get the length of the message
    char keyhuruf[100]; // var vigenere
    int keyangka; // var railfence
    
    // Call the appropriate encryption function based on the selected method
    switch (encryptionMethod) {
        case 1:  //railfence
	        //ada di file project proyek2.dev
        case 2:  //hill cipher
			;
			int n2;
//		    char s[MAX_SIZE], cipher_text[MAX_SIZE];  cipher_text (pesan) : msg || s (key) : keyhuruf  || pesan enkripsi : encryptedMsg
		    printf("What will be the order of square matrix: ");
		    scanf("%d", &n2);
		    printf("Enter the key: ");
		    scanf("%s", keyhuruf);
		    fflush(stdin);
		
		    int key_matrix[MAX_SIZE][MAX_SIZE] = {0};
		    generate_key(n2, keyhuruf, key_matrix);
		
			char passcode[100];
			strcpy(passcode, msg);
		    char *ptr = passcode;
			
		    while (*ptr)
		    {
		        if (*ptr == ' ')
		            *ptr = 'n';
		        ptr++;
		    }
		    printf ("\n passcode: %s\n", passcode);
			
		    int final_matrix[MAX_SIZE][MAX_SIZE][1], matrix_count;
		    message_matrix(passcode, n2, final_matrix, &matrix_count);
		
		    char encryptedMsg[MAX_SIZE] = "";
		    for (int i = 0; i < matrix_count; i++) {
		        char sub[MAX_SIZE][1];
		        multiply_and_convert(key_matrix, final_matrix[i], sub, n2);
		        for (int j = 0; j < n2; j++) {
		            strncat(encryptedMsg, sub[j], 1);
		        }
		    }
		
		    printf("cipher message: %s\n", encryptedMsg);
		    
			
			//simpan ke file
			sprintf(filename, "%s.txt", nama_target);
            int id_pesan = generateUniqueId(filename);

            // Check if the file already exists
            if ((file = fopen(filename, "a")) != NULL) {
		    	getCurrentTimestamp(timestamp);
                fprintf(file, "%d, %s, %s, %s, 2, %s, ", id_pesan, timestamp, nama_target, nama_pengirimpesan, keyhuruf);

                // Use fwrite to write encryptedMsg as binary data
                fwrite(encryptedMsg, sizeof(char), msgLen, file);
                fprintf(file, "\n");

                fclose(file);
            } else {
                printf("Error creating or opening file.\n");
                return;
            }

            printf("Message successfully encrypted and saved to file.\n");
			
            break;
        case 3:  //vernam cipher
        	;
        	//plain_text (pesan) : msg || key : keyhuruf  || pesan enkripsi : encryptedMsg
            
		    int c;
			while ((c = getchar()) != '\n' && c != EOF); 
		    printf("Masukkan kunci one time pad: ");
		    fgets(keyhuruf, sizeof(keyhuruf), stdin);
		    keyhuruf[strcspn(keyhuruf, "\n")] = '\0';
			
		    enkripsiVernam(msg, keyhuruf,encryptedMsg);
		    printf("Hasil enkripsi pesan adalah: %s\n", encryptedMsg);
		    
		    //simpan ke file
			sprintf(filename, "%s.txt", nama_target);
            id_pesan = generateUniqueId(filename);

            // Check if the file already exists
            if ((file = fopen(filename, "a")) != NULL) {
            	getCurrentTimestamp(timestamp);
                fprintf(file, "%d, %s, %s, %s, 3, %s, ", id_pesan, timestamp, nama_target, nama_pengirimpesan, keyhuruf);

                // Use fwrite to write encryptedMsg as binary data
                fwrite(encryptedMsg, sizeof(char), msgLen, file);
                fprintf(file, "\n");

                fclose(file);
            } else {
                printf("Error creating or opening file.\n");
                return;
            }

            printf("Message successfully encrypted and saved to file.\n");
		    
            break;
        case 4:  //vigenere
            //ada di file project proyek2.dev
        case 5:  //RSA
        	;
			printf("ENTER FIRST PRIME NUMBER: ");
		    scanf("%ld", &p);
		    flag = prime(p);
		    int i;
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
		
//		    printf("ENTER MESSAGE: ");
//		    scanf(" %[^\n]s", msg);
		    for (i = 0; i < strlen(msg); i++)
		        m[i] = msg[i];
		
		    n = p * q;
		    t = (p - 1) * (q - 1);
		
		    ce();
		
		    printf("\nPOSSIBLE VALUES OF e AND d ARE:\n");
		    for (i = 0; i < j - 1; i++)
		        printf("%ld\t%ld\n", e[i], d[i]);
		        
		    encrypt(msg);
		    decrypt(msg);
		    
			break;
        default:
            printf("Pilihan tidak valid\n");
            return;
    }
}


int main() {
    char username[100] = "Harish99";
	Member members[MAX_MEMBERS];
    char *usernameArray[MAX_MEMBERS];
    int numMembers = readMembersFromFile(members);
    int targetID;
    int selectedOption;
    char msg[100];
    
	printf("nama yang login : %s \n", username);
    printf("ini numnumber = %d \n", numMembers);
    
    // Menampilkan menu dan daftar pengguna ke layar
    printMenu();
    printMembers(members, numMembers, username);
    printOptions();
    targetID = processOption();
//    printf("ini id tujuan : %d \n", targetID);
    
	char *targetUsername = getUsernameFromID(targetID, members, numMembers);
//    printf("Username dari targetID %d adalah: %s\n", targetID, targetUsername);
    
	selectMetode(&selectedOption, msg);
	
//    printf("ini selected opsi : %d\n", selectedOption);
//    printf("ini pesan: %s\n", msg);
    
    saveEncryptedMessageToFile(targetUsername, username, msg, selectedOption);
	
	char selesai[50];
	printf("klik enter untuk lanjut");
	scanf("%s", selesai);

    return 0;
}
