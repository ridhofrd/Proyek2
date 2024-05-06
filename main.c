#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "AnnisaDian.h"
#include "HayaQonita.h"
#include "MuhammadHarish.h"
#include "MuhammadRidhoF.h"
#include "RafkaImanda.h"


int main()
{
	char username[100], password[50];
	char NIM[25], kelas[10];
	int authRole;
	int authStatusCode = 0;
    int firstState, secondState, thirdState, exitStatus = 0, welcomeExitStatus = 0;

    while(welcomeExitStatus == 0)
    {
        loading();
        system("cls");
        firstState = pilihanLoginWelcome();

        exitStatus = 0;
        while(exitStatus == 0){
            if(firstState == 1){
                system("cls");
                authRole = authMenu();
                if (authRole == 1){
                    system("cls");
                    int userStatus;
                    inputCredentials(&username, &password);
                    printf("%s", password);
                    encrypted_password = encryptPassword(password);
                    authStatusCode = checkCredentials(username, encrypted_password, authRole);
                    
                        if(authStatusCode == 2){
                            system("cls");

                            if (authRole == 1){
                                int mainMenuStatus = 1;
                                while(mainMenuStatus == 1){
                                    int modulExitStatus = 0;
                                    userStatus = mhsMenu();
                                    char terminator;
                                    if(userStatus == 1){
                                        while(modulExitStatus == 0){
                                            system("cls");
                                            modulExitStatus = mainDataMenfess();
                                            scanf("%c", &terminator);
                                            system("cls");
                                        }
                                    }
                                    else if(userStatus == 2){
                                        while(modulExitStatus == 0){
                                            modulExitStatus = mainOpsi2(username);
                                            system("cls");
                                        }
                                    }
                                    else if(userStatus == 3){
                                        while(modulExitStatus == 0){
                                            modulExitStatus = mainOpsi3(username);
                                            system("cls");
                                        }
                                    }
                                    else
                                    {
                                        mainMenuStatus = 0;
                                    }
                                }
                            }
                        }
                        else {
                            system("cls");
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
                    system("cls");
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
                                mainCreateFile(username);
                                statusRegister = 1;
                                encrypted_password = encryptPassword(password);
                                addMhs(username, encrypted_password, NIM, kelas);
                            }
                        }
                        else{
                            gotoxy(30, 16);
                            printf("Maaf username telah digunakan!\n");
                            system("cls");
                            gotoxy(30, 16);printf("Apakah ingin melanjutkan?(Y/n)");
                            char terminator;
                            scanf("%c", &terminator);
                            statusRegister = checkContinue();
                            system("cls");
                        }
                    }

                }
                else{
                    exitStatus = 1;
                }

            }
            else if(firstState == 2){
                system("cls");
                gotoxy(30,2); printf("Ini adalah aplikasi cryptfess\n");
                gotoxy(30, 4);printf("Kembali Ke Menu Utama?(Y\\n)");
                welcomeExitStatus = checkContinue();
                if(welcomeExitStatus == 1)
                    logout();
                exitStatus = 1;

            }
            else if(firstState == 3){
                logout();
                return 0;
            }
            else
                return 0;
        }
    }
}
