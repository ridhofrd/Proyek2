#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>

struct Node {
    char data;
    int key;
    struct Node* left;
    struct Node* right;
};

Node* newNode(char data, int key) {
	/**
		* Untuk membuat Tree baru dari inputan password yang dimasukkan oleh user.
		* @param: data, key
		* return: Node dengan subvar yang terisi
	**/
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

Node* insert(Node* node, char data, int key) {
	/**
		* Untuk melakukan insert Tree dengan level order dari setiap karakter password yang dimasukkan oleh user.
		* @param: node, data, key
		* return: Tree yang masing-masing node berisi karakter dari password user dengan urutan level order
	**/
    if (node == NULL) {
        return newNode(data, key);
    }

    std::queue<Node*> q;
    q.push(node);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        if (current->left == NULL) {
            current->left = newNode(data, key);
            break;
        } else {
            q.push(current->left);
        }

        if (current->right == NULL) {
            current->right = newNode(data, key);
            break;
        } else {
            q.push(current->right);
        }
    }

    return node;
}

char* inorder(struct Node* temp) {
	/**
		* Untuk melakukan pengacakan (shuffle) tree dengan InOrder dari Tree yang sudah diinsert sebelumnya secara level order
		* @param: node
		* return: Array of char berupa password user yang urutan karakternya sudah teracak
	**/
    static char str[1024];
    static int i = 0;

    if (temp == NULL)
        return "";

    inorder(temp->left);
    str[i++] = temp->data;
    inorder(temp->right);

    return str;
}

void chiper(char* password, int len) {
	/**
		* Untuk melakukan penyamaran password agar karakter aslinya tidak terlihat, sehingga tidak memungkinkan untuk menerka-nerka password sebenarnya yang di shuffle.
		* @param: password, len
		* return: Array of char berupa password user yang karakter aslinya sudah disamarkan
	**/
    for (int i = 0; i < len; i++) {
        if (password[i] >= 'A' && password[i] <= 'Z') {
            password[i] = password[i] + 3;
        } else if (password[i] >= 'a' && password[i] <= 'z') {
            password[i] = password[i] + 3;
        }
    }
}

char* encryptPassword(char *password) {
	/**
		* Untuk melakukan proses enkripsi (driver main untuk enkripsi password) yang akan menerima password dari section registrasi atau login pada sistem Cryptfess untuk disamarkan
		* @param: password
		* return: Array of char berupa password user yang urutan karakternya sudah teracak dan disamarkan
	**/
    int len = strlen(password);

    // Build tree
    struct Node *root = NULL;
    for (int i = 0; i < len; i++) {
        root = insert(root, password[i], i);
    }

    // Travsersal inoder
    password = inorder(root);
	chiper(password, len);

    return password;
}

int main() {
    char password[100];
    printf("Enter password: ");
    scanf("%s", password);
    printf("Encrypted password: %s\n", encryptPassword(password));
    return 0;
    
    
    // Klo dipake di main.c nya cryptFess, nanti gini
//    if (authRole == 1){
//                    system("cls");
//                    int userStatus;
//                    inputCredentials(&username, &password);
//                    printf("%s", password);
//                    encrypted_password = encryptPassword(password);   <---- Nah pas login, setelah input password, tar passwordnya di enkrip, abis itu dicocokin
//                    authStatusCode = checkCredentials(username, encrypted_password, authRole);

//if(uniqueUsername == 1){
//                            int strongPass = 0;
//                            strongPass = checkPasswordStrength(password);
//                            if(strongPass == 1){
//                                inputDetail(NIM, kelas);
//                                mainCreateFile(username);
//                                statusRegister = 1;
//                                encrypted_password = encryptPassword(password);    <--- Nah pas registrasi, setelah dicek kekuatan password, baru di enkrip dan di save ke txt
//                                addMhs(username, encrypted_password, NIM, kelas);
//                            }
//                        }
}
