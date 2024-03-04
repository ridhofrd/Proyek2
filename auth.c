#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "modul.h"

#define CHAR_MAX_SIZE 16
#define NIM_MAX 9
#define KELAS_MAX 5

void userAuth(){
	/**
		* Untuk login, register, serta pengecekan kredensial akun.
		* @param: tidak ada.

		* function authMenu untuk menampilkan piilihan pada autentikasi.
		* prosedur inputCredentials untuk menginput kredensial akun.
		* function checkCredentials untuk validasi kredensial akun.
		* prosedur checkUnique untuk mengecek username saat registrasi itu unik.
		* prosedur checkPasswordStrength untuk validasi tingkat kekuatan password.
		* prosedur inputDetail untuk menambah informasi NIM dan kelas mahasiswa.
		* prosedur addMhs untuk menambah hasil registrasi data akun mahasiswa.
		* prosedur redirectPage untuk mengarahkan user sesuai role ke dashboard jika autentikasi sukses.
	**/

	/** kamus data **/
	char username[CHAR_MAX_SIZE], password[CHAR_MAX_SIZE];
	char NIM[NIM_MAX], kelas[KELAS_MAX];
	int authRole;
	int authIsSuccess = 0;

	/** proses **/
	authRole = authMenu();

	if (authRole == 1 || authRole == 2){
		inputCredentials(username, password);
		authIsSuccess = checkCredentials(username, password, authRole);

		if (authRole != 2){
			redirectPage(authIsSuccess, authRole);
		} else {
			checkUnique(authIsSuccess);
			checkPasswordStrength(password);
			inputDetail(NIM, kelas);
			addMhs(username, password, NIM, kelas);
			userAuth();
		}
	} else if (authRole == 3){
	} else {
		userAuth();
	}
}

int authMenu(){
	/**
		* Untuk pemisahan role admin dan user (mahasiswa).
		* @param: tidak ada.
		* prosedur: menyimpan nilai variabel opsi pilihan menu.
	**/

	/** kamus data **/
	int a;

	/** proses **/
	printSeparator("Autentikasi - Aplikasi Menfess");

	printf("1. Login Mahasiswa\n");
	printf("2. Register Akun Mahasiswa\n");
	printf("3. Exit\n\n");
	printDivider();

	printf("Pilih menu yang diinginkan: ");
	scanf("%d", &a);

	system("cls");
	return a;
}

void inputCredentials(char username[CHAR_MAX_SIZE], char password[CHAR_MAX_SIZE]){
	/**
		* Untuk penginputan kredensial akun admin dan user (mahasiswa).
		* @param: username, password.
		* prosedur: menyimpan nilai variabel username dan password.
	**/

	/** proses **/
	printSeparator("Autentikasi - Aplikasi Menfess");

	printf("Masukkan Username : ");
	scanf("%s", &*username);
	printf("Masukkan Password : ");
	scanf("%s", &*password);
}

int checkCredentials(char username[CHAR_MAX_SIZE], char password[CHAR_MAX_SIZE], int role){
	/**
		* Untuk pengecekan kredensial akun admin dan user (mahasiswa).
		* @param: username, password, role.
		* return: 2 jika autentikasi berhasil, 1 jika password salah, 0 jika password salah, -1 jika username sama.
	**/

	/** kamus data **/
	char findUsername[CHAR_MAX_SIZE], findPassword[CHAR_MAX_SIZE];
	char findNIM[NIM_MAX], findkelas[KELAS_MAX];
	int findId;
	int status = 0;

	FILE *file;

	/** proses **/
	if (role == 1){
		file = fopen("mahasiswa.txt", "r");
		if(file){
			while(fscanf(file, "%d %s %s %s %s", &findId, &findUsername, &findPassword, &findNIM, &findkelas)  != EOF) {
				if ((strcmp(findUsername, username) == 0) && (strcmp(findPassword, password) == 0)) {
					status = 2;
					return status;
				} else if ((strcmp(findUsername, username) == 0) && (strcmp(findPassword, password) == 1)) {
					status = 1;
				} else if (strcmp(findUsername, username) == 0) {
					status = -1;
				}
			}
		} else {
			printf("File salah.");
		}
		fclose(file);
	}
	return status;
}

void inputDetail(char NIM[NIM_MAX], char kelas[KELAS_MAX]){
	/**
		* Untuk menambahkan informasi NIM dan kelas bagi akun mahasiswa yang diregistrasi.
		* @param: NIM, kelas.
		* prosedur: variabel NIM dan kelas akan terisi.
	**/

	/** proses **/
	printf("Masukkan NIM : ");
	scanf("%s", &*NIM);
	printf("Masukkan Kelas (Misal: D3-1A) : ");
	scanf("%s", &*kelas);
}

void checkUnique(int authIsSuccess){
	/**
		* Untuk pengecekan nilai unik username saat registrasi.
		* @param: authIsSuccess. (nilai 0 bermakna username unik.)
		* prosedur: registrasi diulang jika username yang dimasukkan sudah pernah ada dalam data.
	**/

	/** proses **/
	printf("%d", authIsSuccess);
	if (authIsSuccess == 0){
	} else {
		printf("Username sudah terpakai. Coba yang lain.\n");
    	system("pause");
		system("cls");
        userAuth();
	}
}

void checkPasswordStrength(char *password) {
	/**
		* Untuk pengecekan kekuatan password.
		* @param: password.
		* prosedur: proses registrasi diulang kembali jika password tidak memiliki salah satu dari
					password yang kurang dari 8 digit, kapital, angka, karakter spesial.
	**/

	/** kamus data **/
    int uppercase = 0, lowercase = 0, digit = 0, special_char = 0, i = 0;
    int password_length = strlen(password);

    /** proses **/
    if (password_length < 8) {
    	printf("Password minimal 8 digit\n");
    	system("pause");
		system("cls");
        userAuth();
    }

    while (password[i]){
        if (isupper(password[i])) {
            uppercase = 1;
        } else if (islower(password[i])) {
            lowercase = 1;
        } else if (isdigit(password[i])) {
            digit = 1;
        } else {
            special_char = 1;
        }
        i ++;
    }

    if (uppercase && lowercase && digit && special_char) {
    } else {
        printf("Password minimal terdiri dari uppercase, lowercase, angka, dan karakter spesial\n");
    	system("pause");
		system("cls");
        userAuth();
    }
}

void addMhs(char *username, char *password, char *NIM, char *kelas){
	/**
		* Untuk menambahkan data mahasiswa yang sukses registrasi.
		* @param: username, password, nim, kelas.
		* prosedur: tambah data mahasiswa jika proses pengecekan username unik dan kekuatan password berhasil.
	**/

	/** kamus data **/
	FILE *dt_mhs;
    int count = 0;
    char buffer[256];

    /** proses **/
    dt_mhs = fopen("mahasiswa.txt", "r");
    if (dt_mhs != NULL) {
        while (fgets(buffer, sizeof(buffer), dt_mhs) != NULL) {
            count++;
        }
        fclose(dt_mhs);
    }

    dt_mhs = fopen("mahasiswa.txt", "a");
    if (dt_mhs != NULL) {
        fprintf(dt_mhs, "%d %s %s %s %s\n", count, username, password, NIM, kelas);
        fclose(dt_mhs);
        printf("Data berhasil ditambahkan. Silakan Login.\n");
        system("pause");
        system("cls");
    }
}

void redirectPage(int authStatusCode, int role){
	/**
		* Untuk pengalihan laman setelah autentikasi dilakukan.
		* @param: authStatusCode, role.
		* prosedur: redirect ke dashboard sesuai role jika autentikasi berhasil, ulangi autentikasi jika gagal.
	**/

	/** proses **/
	if(authStatusCode == 2){
		system("cls");
		if (role == 1){
			mhsDashboard();
		}
	} else {
		if (authStatusCode == 1) {
			printSeparator("Maaf password yang dimasukkan salah.");
		} else if (authStatusCode == 0 || authStatusCode == -1){
			printSeparator("Maaf kredensial akun tidak valid.");
		}
		system("pause");
		system("cls");

		userAuth();
	}
}

