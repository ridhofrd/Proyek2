#include <stdio.h>
#include <stdlib.h>
#include "RSA.h"
#include "vigenere_dekrip.h"
#include "vigenere_enkrip.h"
#include "hilldekrip.h"
#include "hillenkrip.h"
#include "opsi2.h"
#include "auth.h"
#include "commons.h"
#include "deskripsi_vernam.h"
#include "enkripsi_vernam.h"
#include "mhsDashboard.h"
#include "modul.h"
#include "welcome.h"
#include "Logout.h"
#include "datamenfess.h"
#include <conio.h>


int main()
{
	char username[100], password[50];
	char NIM[25], kelas[10];
	int authRole;
	int authStatusCode = 0;
    int firstState, secondState, thirdState, exitStatus = 0;

    loading();
    system("cls");
    firstState = pilihanLoginWelcome();


    while(exitStatus == 0){
        if(firstState == 1){
            system("cls");
            authRole = authMenu();
            if (authRole == 1){
                int userStatus;
                inputCredentials(&username, &password);
                authStatusCode = checkCredentials(username, password, authRole);
                    if(authStatusCode == 2){
                        system("cls");
                        if (authRole == 1){
                            userStatus = mhsMenu();
                            if(userStatus == 1){

                            }
                            else if(userStatus == 2){

                            }
                            else if(userStatus == 3){

                            }
                            else
                            {
                                logout();
                                return 0;
                            }
                        }
                    }
                    else {
                        if (authStatusCode == 1) {
                            printSeparator("Maaf password yang dimasukkan salah.");
                        }
                        else if (authStatusCode == 0 || authStatusCode == -1){
                            //system("cls");
                            printSeparator("Maaf kredensial akun tidak valid(Username atau Password salah!).");
                    }


                    system("pause");
                    system("cls");

                    //userAuth();
                }
            }
            else if(authRole == 2){
                //statusRegister 0 berarti registrasi belum berhasil
                int statusRegister = 0;
                while(statusRegister == 0){
                    int uniqueUsername = 0;
                    inputCredentials(&username, &password);
                    authStatusCode = checkCredentials(username, password, authRole);
                    uniqueUsername = checkUnique(authStatusCode);
                    if(uniqueUsername == 1){
                        int strongPass = 0;
                        strongPass = checkPasswordStrength(password);
                        if(strongPass == 1){
                            inputDetail(NIM, kelas);
                            statusRegister = 1;
                        }
                    }
                    else
                        printf("Maaf username telah digunakan!\n");

                }

                addMhs(username, password, NIM, kelas);

            }

        }
        else if(firstState == 2){
            system("cls");
            gotoxy(30,2); printf("Ini adalah aplikasi cryptfess\n");
        }
        else if(firstState == 3){
            logout();
            return 0;
        }
        else
            return 0;
    }
}
