#ifndef hillenkrip

int determinantOfMatrix(int mat[MAX_SIZE][MAX_SIZE], int n);
int modInverse(int a, int m);
int method(int a, int m);
void generateKey(int key[MAX_SIZE][MAX_SIZE], char *s, int n);
void hillEncrypt(int key[MAX_SIZE][MAX_SIZE], char *text, int n);
int mainHillEnkrip();

#endif
