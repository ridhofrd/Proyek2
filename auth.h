#ifndef auth
#define CHAR_MAX_SIZE 100
#define NIM_MAX 100
#define KELAS_MAX

void userAuth();
int authMenu();
void inputCredentials(char *username[CHAR_MAX_SIZE], char *password[CHAR_MAX_SIZE]);
int checkCredentials(char username[CHAR_MAX_SIZE], char password[CHAR_MAX_SIZE], int role);
void inputDetail(char NIM[NIM_MAX], char kelas[KELAS_MAX]);
int checkUnique(int authIsSuccess);
int checkPasswordStrength(char *password);
void addMhs(char *username, char *password, char *NIM, char *kelas);
void redirectPage(int authStatusCode, int role);
#endif // auth
