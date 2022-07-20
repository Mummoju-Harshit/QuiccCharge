#include <stdio.h>
#include <windows.h>
#include <conio.h>

#include "Main.h"

COORD coord = {0, 0};

void Login(int a, int b);
void CreateAccount(void);

int main() {
	system("COLOR F1");
	int choice, flag;
	flag = 0;
	
	while (!flag) {
		system("cls");
		gotoxy(60, 10);
		printf("MOBILE RECHARGE SYSTEM\n");
		Sleep(2000);
		gotoxy(65, 15);
		printf("1. REGISTER");
		gotoxy(65, 20);
		printf("2. LOGIN");
		gotoxy(65, 25);
		printf("3. EXIT");
		gotoxy(55, 30);
		printf("Enter your choice: ");
		scanf("%d", &choice);
		if (choice == 1) {
			CreateAccount();
		}
		else if (choice == 2) {
			Login(0, 0);
		}
		else if (choice == 3) {
			flag = 1;
		}
	}
	
	system("cls");
    return 0;
}

//Pre-Defined Function Implementation
void gotoxy(short x, short y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Function Implementation
void rectangularBox(int d1, int d2, int d3, int d4) {
    int i, j;

    //For Horizantal Lines
    for (i = d1; i < d3; i++) {
        gotoxy(i, d2); printf("\xcd");
        gotoxy(i, d4); printf("\xcd");
    }

    //For vertical Lines
    for (j = d2 + 1; j < d4; j++) {
        gotoxy(d1, j); printf("\xba");
        gotoxy(d3, j); printf("\xba");
    }

    gotoxy(d1, d2); printf("\xc9");
    gotoxy(d3, d2); printf("\xbb");
    gotoxy(d1, d4); printf("\xc8");
    gotoxy(d3, d4); printf("\xbc");
}
