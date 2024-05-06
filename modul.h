#ifndef modul_H
#define modul_H

#include<stdio.h>

#define N_MAX 999
#define CHAR_MAX_SIZE 16
#define NIM_MAX 9
#define KELAS_MAX 5
#define TEXT_MAX 100

typedef struct{
	int id;
	char username[CHAR_MAX_SIZE];
	char password[CHAR_MAX_SIZE];
	char NIM[NIM_MAX];
	char kelas[KELAS_MAX];
}db_mahasiswa[N_MAX];

struct Node {
    char data;
    int key;
    struct Node* left;
    struct Node* right;
};

Node* newNode(char data, int key);
Node* insert(Node* node, char data, int key);
char* inorder(struct Node* temp);
void chiper(char* password, int len);
char* encryptPassword(char *password);


// definisi fungsional: commons/helpers
void printSeparator(char title[TEXT_MAX]);
void printDivider();

// definisi fungsional: userAuth
// autentikasi
void userAuth(); 	
	// login																					// autentikasi
void inputCredentials(char username[CHAR_MAX_SIZE], char password[CHAR_MAX_SIZE]);				// input username dan password
int checkCredentials(char username[CHAR_MAX_SIZE], char password[CHAR_MAX_SIZE], int role);		// validasi kredensial mahasiswa
void redirectPage(int authStatusCode, int role);												// redirect dashboard mahasiswa
	// registrasi
void checkUnique(int authIsSuccess);																// validasi username unik
void checkPasswordStrength(char *password);														// validasi kekuatan password
void inputDetail(char NIM[NIM_MAX], char kelas[KELAS_MAX]);										// input nim dan kelas
void addMhs(char *username, char *password, char *NIM, char *kelas);							// tambah data mahasiswa
	
// Mahasiswa
	// definisi fungsional: mhsDashboard
void mhsDashboard();
int mhsMenu();
void redirectMhsMenu(int pilihanMenu);
#endif
