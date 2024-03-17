#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#include "modul.h"

#define CHAR_MAX_SIZE 100
#define NIM_MAX 100
#define KELAS_MAX 100



int authMenu(){
	/**
		* Untuk pemisahan role admin dan user (mahasiswa).
		* @param: tidak ada.
		* prosedur: menyimpan nilai variabel opsi pilihan menu.
	**/

	/** kamus data **/


    int key = 1, status = 1;
    int selectedOption = 1, submenuOption = 0;

    while(status == 1)
    {
        do {
            gotoxy(30,9);printf("=================Autentikasi - Aplikasi Menfess=================\n");
                // display the main menu
                gotoxy(30,11);printf("[%c]Login Mahasiswa\n", (selectedOption == 1) ? 'x' : ' ');
                gotoxy(30,12);printf("[%c]Register Akun Mahasiswa\n", (selectedOption == 2) ? 'x' : ' ');
                gotoxy(30,13);printf("[%c]Kembali Ke Menu Awal\n", (selectedOption == 3) ? 'x' : ' ');

                key = getch();
                // Handle arrow key input for the main menu
                switch (key) {
                    case 72:  // Up arrow key
                        selectedOption = (selectedOption > 1) ? selectedOption - 1 : 3;
                        system("cls");
                        break;
                    case 80:  // Down arrow key
                        selectedOption = (selectedOption < 3) ? selectedOption + 1 : 1;
                        system("cls");
                        break;
                    case 13:  // Enter key
                        return selectedOption;
                        break;
                    default:
                        // Ignore other keys
                        break;
                }
            }while (key != 13);  // 13 is the ASCII code for Enter key
    }

            // Clear the console screen (for Windows) - Moved outside of the submenu loop
        system("cls");

        if (submenuOption == 0) {
            printf("Exiting...\n");
        }

	system("cls");
	return selectedOption;
}

void inputCredentials(char *username[CHAR_MAX_SIZE], char *password[CHAR_MAX_SIZE]){
	/**
		* Untuk penginputan kredensial akun admin dan user (mahasiswa).
		* @param: username, password.
		* prosedur: menyimpan nilai variabel username dan password.
	**/

	/** proses **/
	gotoxy(30, 8); printf("===================================================================");
	gotoxy(30, 9); printf("============= Autentikasi - Aplikasi Menfess ======================");
	gotoxy(30, 10); printf("===================================================================");

	gotoxy(30, 12); printf("Masukkan Username : ");
	scanf("%s", &*username);
	gotoxy(30, 14); printf("Masukkan Password : ");
	scanf("%s", &*password);
}

int checkCredentials(char username[CHAR_MAX_SIZE], char password[CHAR_MAX_SIZE], int role){
	/**
		* Untuk pengecekan kredensial akun admin dan user (mahasiswa).
		* @param: username, password, role.
		* return: 2 jika autentikasi berhasil, -1 jika username sama.
	**/

	/** kamus data **/

	int findId;
	int status = 0;
    char findUsername[CHAR_MAX_SIZE] = {'0'}, findPassword[CHAR_MAX_SIZE] = {'0'}, findNIM[NIM_MAX] = {'0'}, findkelas[KELAS_MAX] = {'0'};

	FILE * fileMahasiswa = fopen("mahasiswa.txt", "r");

	/** proses **/
		if(fileMahasiswa != NULL){
            fscanf(fileMahasiswa, "%d %s %s %s %s", &findId, findUsername, findPassword, findNIM, findkelas);
            rewind(fileMahasiswa);
			while(!feof(fileMahasiswa)) {
                char testDrive[100];
                fscanf(fileMahasiswa, "%d %s %s %s %s", &findId, findUsername, findPassword, findNIM, findkelas);

				if ((strcmp(findUsername, username) == 0) && (strcmp(findPassword, password) == 0)) {
					status = 2;
				} else if (strcmp(findUsername, username) == 0) {
					status = -1;
				}

			}
			if(feof(fileMahasiswa))
                return status;


		} else {
			printf("File salah.");
		}
		fclose(fileMahasiswa);
	return status;
}

void inputDetail(char NIM[NIM_MAX], char kelas[KELAS_MAX]){
	/**
		* Untuk menambahkan informasi NIM dan kelas bagi akun mahasiswa yang diregistrasi.
		* @param: NIM, kelas.
		* prosedur: variabel NIM dan kelas akan terisi.
	**/

	/** proses **/
	gotoxy(30, 16);printf("Masukkan NIM : ");
	scanf("%s", &*NIM);
	gotoxy(30,18);printf("Masukkan Kelas (Misal: D3-1A) : ");
	scanf("%s", &*kelas);
}

int checkUnique(int authIsSuccess){
	/**
		* Untuk pengecekan nilai unik username saat registrasi.
		* @param: authIsSuccess. (nilai 0 bermakna username unik.)
		* prosedur: registrasi diulang jika username yang dimasukkan sudah pernah ada dalam data.
	**/

	/** proses **/
	if (authIsSuccess == 0){
        return 1;
	} else {
		gotoxy(30, 16); printf("Username sudah terpakai. Coba yang lain.\n");
    	gotoxy(30, 17);system("pause");
		return 0;
	}
}

int checkPasswordStrength(char *password) {
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
    	gotoxy(30, 16);printf("Password minimal 8 digit\n");
    	gotoxy(30, 17);system("pause");
		system("cls");
		return 0;
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
        return 1;
    } else {
        gotoxy(30, 16);printf("Password minimal terdiri dari uppercase, lowercase, angka, dan karakter spesial\n");
    	gotoxy(30, 17);system("pause");
		system("cls");
		return 0;
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
			mhsMenu();
		}
		/*ini harus dihapus*/mhsMenu();
	} else {
		if (authStatusCode == 1) {
			printSeparator("Maaf password yang dimasukkan salah.");
		}
		else if (authStatusCode == 0 || authStatusCode == -1){
			printSeparator("Maaf kredensial akun tidak valid.");
			system("cls");
            /*ini harus dihapus*/mhsMenu();

		}
		system("pause");
		system("cls");

		//userAuth();
	}
}

