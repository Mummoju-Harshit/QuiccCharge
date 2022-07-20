#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define ENTER 13

#include "Main.h"

struct Account
{
	char FirstName[50];
	char LastName[50];
	char password[30];
	char PN[11];
};

//Functions Prototype
int checkMobileNumber(char mobileNumber[30]);
int validateMobileNumber(char mobileNumber[30]);

void CreateAccount(void) 
{
	int r1, r2;
	struct Account* AC = (struct Account*)malloc(sizeof(struct Account));
	system("cls");
	gotoxy(60, 8);
	printf("      Account Create\n");
	gotoxy(60, 10);
	printf("Enter FisrtName: ");
	scanf("%s",AC->FirstName);
	gotoxy(60, 12);
	printf("Enter LastName: ");
	scanf("%s",AC->LastName);
	gotoxy(60, 14);
	printf("Enter PhoneNumber: ");
	scanf("%s", AC->PN);
	r2 = validateMobileNumber(AC->PN);
	if (r2 == 0) {
		gotoxy(60, 20);
		printf("Invalid Phone number\n");
		Sleep(3000);
		return;
	}
	r1 = checkMobileNumber(AC->PN);
	if (r1 == 0) {
		return;
	}
	gotoxy(60, 16);
	printf("Enter password: ");
	int j = 0, l = 0, result = 0, res = 1;
	char ch, check[20];
	while (1) {
		ch = getch();
		if (ch == ENTER) 
			break;
		AC->password[j] = ch;
		putchar('*');
		j++;
	}
	AC->password[j] = '\0';
	do {
		j = 0;
		gotoxy(60, 18 + l);
		printf("Enter to re-confirm password: ");
		while (1) {
			ch = getch();
			if (ch == ENTER) 
				break;
			check[j] = ch;
			putchar('*');
			j++;
		}
		check[j] = '\0';
		result = strcmp(AC->password, check);
		if (result != 0) {
			l += 2;
			gotoxy(60, 18 + l);
			printf("Password didn't match");
			l += 2;
			res = 0;
		}
	}while (result != 0);
	
	char number[20];
	strcpy(number, AC->PN);
    strcat(number, ".txt");
	
	if (res == 0) {
		gotoxy(50, 27 + l);
		printf("Account has created SUCCESSFULLY with user name: %s\n", AC->PN);
	}
	else {
		gotoxy(50, 27 + l);
		printf("Account has created SUCCESSFULLY with user name: %s\n", AC->PN);
	}
	Sleep(5000);
	FILE *fp1, *fp2;

	fp1 = fopen(number, "w");
	fp2 = fopen("JioCustomers.csv", "a");
	if (fp1 == NULL) {
		printf("Unable to access the file\n");
		return;
	}
	if (fp2 == NULL) {
		printf("Unable to access the file\n");
		return;
	}
	
	fprintf(fp1, "Name of the customer: %s %s\n", AC->FirstName, AC->LastName);
	fprintf(fp1, "Phone number of the customer: %s\n", AC->PN);
	
	int plans = 0;
	time_t currentTime;
	
	time(&currentTime); //Obtains Current Time
	
	struct tm *localTime = localtime(&currentTime);
	int date, month, year, ad;
	date = localTime->tm_mday;
	month = localTime->tm_mon + 1;
	year = localTime->tm_year + 1900;
	fprintf(fp2, "%s,%s,%d,%d/%d/%d,\n", AC->PN, AC->password, plans, date, month, year);
	
	fclose(fp1);
	fclose(fp2);
}

//Functions Implementation
int checkMobileNumber(char mobileNumber[30]) {
	FILE *fp;
	fp = fopen("JioCustomers.csv", "r");
	if (fp == NULL) {
		return 1;
	}
	
	char totalLine[100];
	while (fgets(totalLine, sizeof(totalLine), fp)) {
		char* t;
		t = strtok(totalLine, ",");
		if ((strcmp(t, mobileNumber)) == 0) {
			fclose(fp);
			gotoxy(55, 20);
			printf("Account already exists on given phone number: %s\n", mobileNumber);
			Sleep(3000);
			return 0;
		}
	}
	fclose(fp);
	return 1;
}

int validateMobileNumber(char mobileNumber[30]) {
	int l = 0;
	if (strlen(mobileNumber) != 10) {
		return 0;
	}
	
	if ((mobileNumber[0] == '9') || (mobileNumber[0] == '8')) {
		for (int i = 0; i < 10; i++) {
			if ((mobileNumber[i] >= 48) && (mobileNumber[i] <= 57)) {
				l++;
			}
		}
		if (l == 10) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}