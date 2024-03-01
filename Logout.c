#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>


void gotoxy(int x, int y) {
    COORD coord;

    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void logout(){
	system("cls");
    system("color F1");

		gotoxy(30,8); printf("================================================");
		gotoxy(30,10);printf("   Terimakasih Telah Menggunakan Program Kami,");
        gotoxy(30,11);printf("              Sampai Jumpa Lagi!");
		gotoxy(30,13);printf("================================================");

    getch();

}

int main(){
    logout();

    return 0;
}
