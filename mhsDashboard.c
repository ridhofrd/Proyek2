#include<stdio.h>
#include<stdlib.h>
#include"modul.h"

void mhsDashboard(){
	int pilihanMenu;
	
	pilihanMenu = mhsMenu();
	redirectMhsMenu(pilihanMenu);
}

int mhsMenu(){
	/** kamus data **/
	int a;
	
	/** proses **/	
	printSeparator("Menu Utama");
	
	printf("1. Lihat Beranda Menfess\n");
	printf("2. Kirim Menfess\n");
	printf("3. Cek Menfess Masuk\n");
	printf("4. Logout\n");
	printDivider();
	
	printf("Pilih menu yang diinginkan: ");
	scanf("%d", &a);
	
	system("cls");
	return a;
}

void redirectMhsMenu(int pilihanMenu){
	/** kamus data **/
	int isAdmin = 0;
	
	/** proses **/	
	switch (pilihanMenu){
		case 1: {
			system("cls");
			printf("Data Menfess Tersedia\n");
			break;
		}
		case 2:{
			system("cls");
			printf("Menu Kirim Menfess\n");
			break;
		}
		case 3:{
			system("cls");
			printf("Menu Cek Menfess\n");
			break;
		}
		case 4:{
			system("cls");
			userAuth();
			break;
		}
		default:{
			printSeparator("Input tidak tepat, mohon diulang.");
			system("pause");
			system("cls");
			mhsDashboard();
			break;
		}
	}
}

