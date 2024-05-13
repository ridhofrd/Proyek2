#ifndef RafkaImanda.h
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

typedef struct Node {
    char data;
    int key;
    struct Node* left;
    struct Node* right;
};

// Autentikasi
void userAuth();
int authMenu();
void inputCredentials(char *username[CHAR_MAX_SIZE], char *password[CHAR_MAX_SIZE]);
int checkCredentials(char username[CHAR_MAX_SIZE], char password[CHAR_MAX_SIZE], int role);
void inputDetail(char NIM[NIM_MAX], char kelas[KELAS_MAX]);
int checkUnique(int authIsSuccess);
int checkPasswordStrength(char *password);
void addMhs(char *username, char *password, char *NIM, char *kelas);
void redirectPage(int authStatusCode, int role);
void mhsDashboard();
int mhsMenu();
void redirectMhsMenu(int pilihanMenu);
void enkripsiVernam(char* plain_text, char* key, char *cipher_text);
void decryptVernam(char* cipher_text, char* key, char* decryptedMsg);
char* encryptPassword(char *password);

// Enkripsi dengan Tree
Node* newNode(char data, int key);
Node* insert(Node* node, char data, int key);
char* inorder(struct Node* temp);
void chiper(char* password, int len);
char* encryptPassword(char *password);

#endif // RafkaImanda
