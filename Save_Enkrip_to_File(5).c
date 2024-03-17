#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>	//haya
#include<math.h>	//ridho
#include <time.h>

#define MAX_SIZE 100
#define MAX_MEMBERS 100

//variabel ridho
//long int p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], en[100], i;
long int p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], en[100];
//char msg[100];
char timestamp[20];

int prime(long int);
void ce();
long int cd(long int);
char *encrypt();
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
    printf("Daftar Menfess\n\n");
}

void printOptions() {
    printf("\nPilihan opsi:\n");
    printf("1. Pilih tujuan kirim menfess\n");
    printf("2. Kembali ke menu utama\n");
}

int processOption(int jumlahMember) {
    int option = 0;
	printf("\nPilihan opsi: ");
    while (1) {
        if (scanf("%d", &option) != 1) {
            printf("Input harus berupa angka!\n");
            while (getchar() != '\n');		// Membersihkan stdin dari karakter yang tidak valid
            printf("\nPilihan opsi: ");
        } else if (option == 1 || option == 2) {
            break; // Keluar dari loop jika input valid
        } else {
            printf("Pilihan tidak valid.\n");
            printf("\nPilihan opsi: ");
        }
    }
    if (option == 1) {
        // Handle option 1: Kirim pesan
		int targetID;
        printf("\nMasukkan nomor id tujuan yang ingin anda buatkan menfess : ");
		while(1) {
        	if(scanf("%d", &targetID)!=1){
        		printf("Input harus berupa angka\n");
        		while (getchar() != '\n');		// Membersihkan stdin dari karakter yang tidak valid
        		printf("\nMasukkan nomor id tujuan yang ingin anda buatkan menfess : ");
			} else if (targetID > jumlahMember-1) {		//validasi id target
            	printf("ID tujuan tidak valid. Masukkan nomor ID yang lebih kecil atau sama dengan %d.\n", jumlahMember-1);
        		printf("\nMasukkan nomor id tujuan yang ingin anda buatkan menfess : ");
        	} else {
        		break;
			}
		}
        return targetID;
    } else {
        // Handle option 2: Keluar dari program
        printf("Keluar dari program...\n");
        return 0;
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
	printf("\n\n --------------- DAFTAR Nama ---------------\n");

	printf("\t----------------------------\n");
	printf("\t| ID |         Nama        |\n");
	printf("\t|----|---------------------|\n");

    for (i = 0; i < numMembers; i++) {
        // Cek apakah username dalam data member sama dengan username yang sedang login
        if (strcmp(members[i].username, loggedInUsername) == 0) {
            // Jika sama, lanjut ke pengguna berikutnya
            continue;
        }
        // Jika tidak sama, cetak nomor indeks dan nama

        printf("\t|%-3d |%-20s |\n", members[i].id, members[i].username);
    }
	printf("\t----------------------------\n");
}

void selectMetode(int *selectedOption, char *msg) {
	printf("\nMasukkan pesan yang ingin disampaikan : ");
	scanf(" %[^\n]s", msg);

    printf("\n========================\n");
    printf("1. Railfence Encryption\n");
    printf("2. Hill Encryption\n");
    printf("3. Vernam Encryption\n");
    printf("4. Vigenere Encryption\n");
    printf("5. RSA\n");
    printf("========================\n");

	do {
	    printf("Pilihan metode enkripsi yang ingin digunakan : ");
	    scanf("%d", selectedOption);

	    if (*selectedOption < 1 || *selectedOption > 5) {
            printf("Pilih tidak valid. Silakan masukkan nomor metode enkripsi yang valid.\n");
        }
    } while (*selectedOption < 1 || *selectedOption > 5);

    printf("\n\n");
}

//fungsi enkripsi railfence dan tambahan dian
int getLastMessageId(char filename[]) {	// Function to read the last used message ID from file
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

int generateUniqueId(char filename[]) {	// Function to generate a unique ID for each message
    int lastMessageId = getLastMessageId(filename);
    return ++lastMessageId;
}

void encryptMsg(char msg[], int key, char encryptedMsg[]) {
    int msgLen = strlen(msg), i, j, k = -1, row = 0, col = 0;
    char railMatrix[key][msgLen];

    // Inisialisasi matriks dengan karakter newline
    for (i = 0; i < key; ++i)
        for (j = 0; j < msgLen; ++j)
            railMatrix[i][j] = '\n';

    // Mengisi matriks sesuai dengan pola railfence
    for (i = 0; i < msgLen; ++i) {
        railMatrix[row][col++] = msg[i];

        if (row == 0 || row == key - 1)
            k = k * (-1);

        row = row + k;
    }

    // Menyalin pesan terenkripsi dari seluruh matriks
    int index = 0; // Added index variable to keep track of the position in encryptedMsg
    for (i = 0; i < key; ++i) {
        for (j = 0; j < msgLen; ++j) {
            if (railMatrix[i][j] != '\n') {
                encryptedMsg[index++] = railMatrix[i][j];
            }
        }
    }

    encryptedMsg[msgLen] = '\0';  // Null-terminate the string

    // Menampilkan pesan terenkripsi ke layar
    printf("Encrypted Message: %s\n", encryptedMsg);
}
//enkrip railfence


//enkrip vigenere
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
//end vigenere

//ini enkrip hill
int modInverseEnkrip(int a, int m) {
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

int is_valid_key(const char *key, int n) {
    int len = strlen(key);

    // Memeriksa panjang key yang sesuai dengan n
    if (n == 2 && len != 4) {
        return 0;
    } else if (n == 3 && len != 9) {
        return 0;
    }

    // Memeriksa setiap karakter apakah merupakan huruf kecil
    for (int i = 0; i < len; i++) {
        if (!isalpha(key[i]) || !islower(key[i])) {
            return 0;
        }
    }

    return 1; // Key valid
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
//end vernam


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

void ce(){
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

long int cd(long int x){
    long int k = 1;
    while (1)
    {
        k = k + t;
        if (k % x == 0)
            return (k / x);
    }
}

void decrypt(){
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
void getCurrentTimestamp(char timestamp[]) {
    time_t rawtime;
    struct tm *info;

    time(&rawtime);
    info = localtime(&rawtime);

    strftime(timestamp, 20, "%d/%m/%Y %H:%M:%S", info);
}

// Function to save encrypted message to file
void saveEncryptedMessageToFile(char nama_target[], char nama_pengirimpesan[], char msg[], int encryptionMethod) {
    // File handling
    FILE *file;
    char filename[100];

	char encryptedMsg[100]; // Adjust the size as needed
    int msgLen = strlen(msg); // Added to get the length of the message
    char keyhuruf[100]; // var vigenere
    int keyangka; // var railfence

    // Call the appropriate encryption function based on the selected method
    switch (encryptionMethod) {
        case 1:
            ;  //railfence
	        int statusInput = 0;
	        /**
	        while(statusInput == 0){
	        	if (scanf("%d", &keyangka)!=1 &&  keyangka < msgLen){
                    printf("Input harus berupa angka\n");
                while (getchar() != '\n');		// Membersihkan stdin dari karakter yang tidak valid
                    printf("\nEnter the encryption key (berupa angka): ");
				}else {
					break;
				}
			}
			**/

            while(statusInput == 0){
                printf("Enter the encryption key (berupa angka) 1 < key <= %d: ", msgLen/2);

                int charValid = scanf("%d", &keyangka);
                statusInput = 1;
                if(charValid != 1 || keyangka > (msgLen/2)){
                    printf("Input harus berupa angka dan 1 < input <= %d\n", msgLen/2);
                    while (getchar() != '\n');		// Membersihkan stdin dari karakter yang tidak valid
                    statusInput = 0;
                }
                while (getchar() != '\n');		// Membersihkan stdin dari karakter yang tidak valid
            }

            // Implement Rainfence Encryption logic
            encryptMsg(msg, keyangka, encryptedMsg);

            sprintf(filename, "%s.txt", nama_target);
            int id_pesan = generateUniqueId(filename);

            // Check if the file already exists
            if ((file = fopen(filename, "a")) != NULL) {
            	getCurrentTimestamp(timestamp);
                fprintf(file, "%d, %s, %s, %s, 1, %d, ", id_pesan, timestamp, nama_target, nama_pengirimpesan, keyangka);

                // Use fwrite to write encryptedMsg as binary data
                fwrite(encryptedMsg, sizeof(char), msgLen, file);
                fprintf(file, "\n");

                fclose(file);
            } else {
                printf("Error creating or opening file.\n");
                return;
            }

            // Simpan juga ke file DataMenfess.txt
		    if ((file = fopen("DataMenfess.txt", "a")) != NULL) {
            	id_pesan = generateUniqueId("DataMenfess.txt");
				fprintf(file, "%d, %s, %s, %s, 1, %d, ", id_pesan, timestamp, nama_target, nama_pengirimpesan, keyangka);
		        // Use fwrite to write encryptedMsg as binary data
		        fwrite(encryptedMsg, sizeof(char), msgLen, file);
		        fprintf(file, "\n");

		        fclose(file);
		    } else {
		        printf("Error creating or opening DataMenfess.txt.\n");
		        return;
		    }

            printf("Message successfully encrypted and saved to file.\n");
            break;
        case 2:  //hill cipher
			;
			int n2=0;
//		    char s[MAX_SIZE], cipher_text[MAX_SIZE];  cipher_text (pesan) : msg || s (key) : keyhuruf  || pesan enkripsi : encryptedMsg
		    printf("Berapa ukuran orde matriks persegi nya (ketik 2 : 2x2 atau 3 : 3x3): ");
//		    scanf("%d", &n2);

			while (1) {
		        if (scanf("%d", &n2)!= 1) {
		            printf("Input harus berupa angka!\n");
		            while (getchar() != '\n');		// Membersihkan stdin dari karakter yang tidak valid
		    		printf("Berapa ukuran orde matriks persegi nya (ketik 2 : 2x2 atau 3 : 3x3): ");
		        } else if (n2 == 3 || n2 == 2) {
		            break; // Keluar dari loop jika input valid
		        } else {
		            printf("Pilihan tidak valid.\n");
		    		printf("Berapa ukuran orde matriks persegi nya (ketik 2 : 2x2 atau 3 : 3x3): ");
		        }
		    }

			while (1) {
		        printf("Enter the key: ");
		        scanf("%s", keyhuruf);

		        // Validasi key
		        if (is_valid_key(keyhuruf, n2)) {
		            break; // Jika key valid, keluar dari loop
		        } else {
		            printf("Invalid key. Mohon pastikan key menggunakan huruf kecil dan panjang key adalah %d.\n", n2*n2);
		        }
		    }

		    printf("Key accepted: %s\n", keyhuruf);

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
            id_pesan = generateUniqueId(filename);

            // Check if the file already exists
            if ((file = fopen(filename, "a")) != NULL) {
		    	getCurrentTimestamp(timestamp);
                fprintf(file, "%d, %s, %s, %s, 2, %d, %s, ", id_pesan, timestamp, nama_target, nama_pengirimpesan, n2, keyhuruf);

                // Use fwrite to write encryptedMsg as binary data
                fwrite(encryptedMsg, sizeof(char), msgLen, file);
                fprintf(file, "\n");

                fclose(file);
            } else {
                printf("Error creating or opening file.\n");
                return;
            }

            // Simpan juga ke file DataMenfess.txt
		    if ((file = fopen("DataMenfess.txt", "a")) != NULL) {
            	id_pesan = generateUniqueId("DataMenfess.txt");
		        fprintf(file, "%d, %s, %s, %s, 2, %d, %s, ", id_pesan, timestamp, nama_target, nama_pengirimpesan, n2, keyhuruf);

		        // Use fwrite to write encryptedMsg as binary data
		        fwrite(encryptedMsg, sizeof(char), msgLen, file);
		        fprintf(file, "\n");

		        fclose(file);
		    } else {
		        printf("Error creating or opening DataMenfess.txt.\n");
		        return;
		    }


            printf("Message successfully encrypted and saved to file.\n");

            break;
        case 3:  //vernam cipher
        	;
        	//plain_text (pesan) : msg || key : keyhuruf  || pesan enkripsi : encryptedMsg

		    int c;
			while ((c = getchar()) != '\n' && c != EOF); 		//menghapus buffer
//		    printf("Masukkan kunci one time pad: ");
//		    fgets(keyhuruf, sizeof(keyhuruf), stdin);
//		    keyhuruf[strcspn(keyhuruf, "\n")] = '\0';

			do {		//validasi input
		        printf("Masukkan kunci one time pad yang panjangnya sama dengan panjang pesan (%lu karakter): ", strlen(msg));
		        fgets(keyhuruf, sizeof(keyhuruf), stdin);
		    	keyhuruf[strcspn(keyhuruf, "\n")] = '\0';
		        // Memeriksa apakah panjang kunci sama dengan panjang pesan
		        if (strlen(keyhuruf) != strlen(msg)) {
		            printf("Panjang kunci tidak sama dengan panjang pesan. Silakan masukkan kunci lagi.\n");
		        } else {
		            break; // Keluar dari loop jika panjang kunci sama dengan panjang pesan
		        }
		    } while (1);

		    enkripsiVernam(msg, keyhuruf,encryptedMsg);
		    printf("\nHasil enkripsi pesan adalah: %s\n", encryptedMsg);

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

            // Simpan juga ke file DataMenfess.txt
		    if ((file = fopen("DataMenfess.txt", "a")) != NULL) {
            	id_pesan = generateUniqueId("DataMenfess.txt");
		        fprintf(file, "%d, %s, %s, %s, 3, %s, ", id_pesan, timestamp, nama_target, nama_pengirimpesan, keyhuruf);

		        // Use fwrite to write encryptedMsg as binary data
		        fwrite(encryptedMsg, sizeof(char), msgLen, file);
		        fprintf(file, "\n");

		        fclose(file);
		    } else {
		        printf("Error creating or opening DataMenfess.txt.\n");
		        return;
		    }

            printf("Message successfully encrypted and saved to file.\n");

            break;
        case 4:  //vigenere
            printf("Enter the encryption key (berupa huruf): ");
	        scanf("%s", &keyhuruf);

            // Implement Vigenere Encryption logic
            vigenere_encrypt(msg, keyhuruf, encryptedMsg);

            sprintf(filename, "%s.txt", nama_target);
            id_pesan = generateUniqueId(filename);

            // Check if the file already exists
            if ((file = fopen(filename, "a")) != NULL) {
                getCurrentTimestamp(timestamp);
                fprintf(file, "%d, %s, %s, %s, 4, %s, ", id_pesan, timestamp, nama_target, nama_pengirimpesan, keyhuruf);

                // Use fwrite to write encryptedMsg as binary data
                fwrite(encryptedMsg, sizeof(char), msgLen, file);
                fprintf(file, "\n");

                fclose(file);
            } else {
                printf("Error creating or opening file.\n");
                return;
            }

            // Simpan juga ke file DataMenfess.txt
		    if ((file = fopen("DataMenfess.txt", "a")) != NULL) {
            	id_pesan = generateUniqueId("DataMenfess.txt");
		        fprintf(file, "%d, %s, %s, %s, 4, %s, ", id_pesan, timestamp, nama_target, nama_pengirimpesan, keyhuruf);

		        // Use fwrite to write encryptedMsg as binary data
		        fwrite(encryptedMsg, sizeof(char), msgLen, file);
		        fprintf(file, "\n");

		        fclose(file);
		    } else {
		        printf("Error creating or opening DataMenfess.txt.\n");
		        return;
		    }

            printf("Message successfully encrypted and saved to file.\n");
            break;
        case 5:
            ;  //RSA
            printf("Silahkan Masukkan 2 Nomor Prima yang tidak lebih dari 17\n");
            int inputStatus = 0;
            while(inputStatus == 0){
                inputStatus = 0;
                printf("Masukkan Angka Prima Pertama: ");
                scanf("%ld", &p);
                flag = prime(p);
                int i;
                inputStatus = 1;
                if (flag == 0 || p == 1 || p > 17)
                {
                    printf("Input Tidak Diterima!, ");
                    printf("Silahkan input kembali\n");
                    inputStatus = 0;
                }
            }
            inputStatus  = 0;
            while(inputStatus == 0){
                printf("Masukkan Angka Prima Kedua: ");
                scanf("%ld", &q);
                flag = prime(q);
                inputStatus = 1;
                if (flag == 0 || q == 1 || p == q || q > 17)
                {
                    printf("Input Tidak Diterima!, ");
                    printf("Silahkan input kembali\n");
                    inputStatus = 0;
                }
            }


//		    printf("ENTER MESSAGE: ");
//		    scanf(" %[^\n]s", msg);
		    for (int i = 0; i < strlen(msg); i++)
		        m[i] = msg[i];

		    n = p * q;
		    t = (p - 1) * (q - 1);

		    ce();

		    printf("\nPOSSIBLE VALUES OF e AND d ARE:\n");
		    for (int i = 0; i < j - 1; i++)
		        printf("%ld\t%ld\n", e[i], d[i]);

            long int pt, ct, key = e[0], k, len;
            printf("ini pesannnn : %s \n",msg);
            int i = 0;
            len = strlen(msg);
            char RSAEncryptedMsg[100] = "";
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
            for (i = 0; en[i] != -1; i++){
                char bitMessage = (char)en[i];
                printf("%c", bitMessage);
                strncat(RSAEncryptedMsg, &bitMessage, 2);
            }
            printf("encrytedRSA: %s\n", RSAEncryptedMsg);

                   sprintf(filename, "%s.txt", nama_target);
                   if ((file = fopen(filename, "a")) != NULL) {
                        getCurrentTimestamp(timestamp);
                        id_pesan = generateUniqueId(filename);
                        fprintf(file, "%d, %s, %s, %s, 5, %d, %d, ", id_pesan, timestamp, nama_target, nama_pengirimpesan, p, q);

                        // Use fwrite to write encryptedMsg as binary data
                        fwrite(RSAEncryptedMsg, sizeof(char), msgLen, file);
                        fprintf(file, "\n");

                        fclose(file);
                    } else {
                        printf("Error creating or opening file.\n");
                        return;
                    }

                    // Simpan juga ke file DataMenfess.txt
                    if ((file = fopen("DataMenfess.txt", "a")) != NULL) {
                        getCurrentTimestamp(timestamp);
                        id_pesan = generateUniqueId("DataMenfess.txt");
                        fprintf(file, "%d, %s, %s, %s, 5, %d, %d, ", id_pesan, timestamp, nama_target, nama_pengirimpesan, p, q);
                        // Use fwrite to write encryptedMsg as binary data
                        fwrite(RSAEncryptedMsg, sizeof(char), msgLen, file);
                        fprintf(file, "\n");

                        fclose(file);
                    } else {
                        printf("Error creating or opening DataMenfess.txt.\n");
                        return;
                    }

                    printf("Message successfully encrypted and saved to file.\n");


            // Check if the file already exists

            break;

        default:
            printf("Pilihan tidak valid\n");
            return;



    }
}


int mainOpsi2(char username[100]) {
	Member members[MAX_MEMBERS];
    char *usernameArray[MAX_MEMBERS];
    int numMembers = readMembersFromFile(members);
    int targetID;
    int selectedOption;
    char msg[100];

    // Menampilkan menu dan daftar pengguna ke layar
    printMenu();
    printMembers(members, numMembers, username);
    printOptions();
    targetID = processOption(numMembers);
    if(targetID == 0)
        return 1;
	char *targetUsername = getUsernameFromID(targetID, members, numMembers);		//mengambil username berdasar id target

	selectMetode(&selectedOption, msg);

    saveEncryptedMessageToFile(targetUsername, username, msg, selectedOption);

	char selesai, terminator;
	scanf("%c", &terminator);
	printf("\nklik enter untuk lanjut");
	scanf("%c", &selesai);

    return 0;
}
