#ifndef opsi2
typedef struct {
    char nama[50];
    char username[50];
    char password[50];
} Member;

int readMembersFromFile(Member *members);
void printMenu();
void printOptions();
void processOption() ;
void printMembers(Member *members, int numMembers, char *loggedInUsername);
void selectMetode();
int opsi2Harris();

#endif // opsi2
