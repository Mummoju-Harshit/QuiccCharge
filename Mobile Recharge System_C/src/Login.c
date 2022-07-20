#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <windows.h>

#include "Main.h"
#define ENTER 13

struct Account {
	char userName[20];
	char password[20];
	int numberOfPlans;
	int date, month, year;
};

struct Date {
    int date;
	int month;
	int year;
};

//Global Variables
int WrongUserName, WrongPassword;
int days_1GB[] = {336, 84, 84, 28, 28};
int days_2GB[] = {365, 84, 56, 28};
int numberOfDaysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int m2, d2;
int remDays;
struct Account acc[100];

//Functions Prototype
int totalUsers();
void start(int users, char* mobileNumber);
void checkStatus(int users, char* mobileNumber);
void unregister(int users, char* mobileNumber);
void changePassword(int users, char* mobileNumber);
void plans(char* mobileNumber);
void Plan1(char* fileName, char* mobileNumber, int choice);
void Topup(char* fileName, char* mobileNumber);
void update(char* mobileNumber, int plan, int choice);
void cashBack(char* mobileNumber, int plans);

int isLeap(int y);
int offsetDays(int d, int m, int y);
void revoffsetDays(int offset, int y);
struct Date addDays(int d1, int m1, int y1, int x);

int countLeapYears(struct Date date);
int getDifference(struct Date date1, struct Date date2);

void Login(int a, int b) {
	WrongUserName = a;
	WrongPassword = b;
	int day, month, year;
	int hours, minutes, seconds;
	
	system("cls");
	char mobileNumber[20];
	char password[20];
	char ch;
	int r1, r2, i, j;
	int users = totalUsers();
	if (users != 0) {
		FILE *fp;
		
		fp = fopen("JioCustomers.csv", "r");
		char line[100];
		i = 0;
		while (fgets(line, sizeof(line), fp)) {
			char* s;
			s = strtok(line, ",");
			strcpy(acc[i].userName, s);
			s = strtok(NULL, ",");
			strcpy(acc[i].password, s);
			s = strtok(NULL, ",");
			int value;
			sscanf(s, "%d", &value);
			Sleep(3000);
			acc[i].numberOfPlans = value;
			s = strtok(NULL, ",");
			
			char* tk;
			tk = strtok(s, "/");
			sscanf(tk, "%d", &acc[i].date);
			tk = strtok(NULL, "/");
			sscanf(tk, "%d", &acc[i].month);
			tk = strtok(NULL, "/");
			sscanf(tk, "%d", &acc[i].year);
			i += 1;
		}
		
		fclose(fp);
	}
	
	gotoxy(60, 8);
	printf("INFORMATION TO LOGIN INTO ACCOUNT");
	//Implementation of checking username
	gotoxy(65, 10);
	printf("    USER NAME");
	gotoxy(65, 12);
	rectangularBox(65, 12, 80, 14);
	gotoxy(66, 13);
	scanf("%s", mobileNumber);
	
	int k = 0;
	for (i = 0; i < users; i++) {
		r1 = strcmp(acc[i].userName, mobileNumber);
		if (r1 == 0) {
			break;
		}
	}
	if (r1 != 0) {
		WrongUserName += 1;
		if (WrongUserName > 2) {
			gotoxy(55, 30);
			printf("You have entered wrong user name more than 2 times");
			Sleep(3000);
			return;
		}
		gotoxy(65, 17);
		printf("Invalid Username");
		Sleep(2000);
		Login(WrongUserName, WrongPassword);
	}
	
	if (r1 == 0) {
		gotoxy(65, 20);
		printf("    PASSWORD");
		gotoxy(65, 22);
		rectangularBox(65, 22, 80, 24);
		gotoxy(66, 23);
		j = 0;
		while (1) {
			ch = getch();
			if (ch == ENTER) 
				break;
			password[j] = ch;
			putchar('*');
			j++;
		}
		password[j] = '\0';
		for (i = 0; i < users; i++) {
			r2 = strcmp(acc[i].password, password);
			if (r2 == 0) {
				gotoxy(55, 30);
				printf("          Login Successfull\n");
				Sleep(3000);
				start(users, mobileNumber);
				break;
			}
		}
		if (r2 != 0) {
			WrongPassword += 1;
			if (WrongPassword > 2) {
				gotoxy(55, 30);
				printf("You have entered wrong password name more than 2 times");
				Sleep(3000);
				return;
			}
			gotoxy(65, 25);
			printf("Invalid Password");
			Sleep(2000);
			Login(WrongUserName, WrongPassword);
		}
	}
}

//Functions Implementation
void start(int users, char* mobileNumber) {
	int choice = 1;
	while (choice) {
		system("cls");
		int option;
		rectangularBox(60, 10, 92, 35);
		gotoxy(67, 13);
		printf("1. Recharge Plans");
		gotoxy(67, 16);
		printf("2. Check Status");
		gotoxy(67, 19);
		printf("3. Change Password");
		gotoxy(67, 22);
		printf("4. Unregister");
		gotoxy(67, 25);
		printf("5. Go Back");
		gotoxy(62, 30);
		printf("  Choose your option: ");
		scanf("%d", &option);
		switch(option) {
			case 1:
				plans(mobileNumber);
				break;
			case 2:
				checkStatus(users, mobileNumber);
				break;
			case 3:
				changePassword(users, mobileNumber);
				break;
			case 4:
				unregister(users, mobileNumber);
				choice = 0;
				break;
			case 5:
				choice = 0;
				break;
			default:
				gotoxy(62, 30);
				printf("\nInvalid option entered\n");
				Sleep(3000);
				break;
		}
	}
}

int totalUsers() {
	FILE *fp;
	fp = fopen("JioCustomers.csv", "r");
	
	if (fp == NULL) {
		return 0;
	}
	
	int count = 0;
	char line[101];
	while (fgets(line, sizeof(line), fp)) {
		count++;
	}
	
	fclose(fp);
	return count;
}

void checkStatus(int users, char* mobileNumber) {
	system("cls");
	int d, m, y;
	int i;
	for (i = 0; i < users; i++) {
		if ((strcmp(acc[i].userName, mobileNumber)) == 0) {
			d = acc[i].date;
			m = acc[i].month;
			y = acc[i].year;
			break;
		}
	}
	
	time_t currentTime;
	
	time(&currentTime); //Obtains Current Time
	
	struct tm *localTime = localtime(&currentTime);
	int date, month, year, ad;
	date = localTime->tm_mday;
	month = localTime->tm_mon + 1;
	year = localTime->tm_year + 1900;
	
	struct Date d1 = {date, month, year};
	struct Date d2 = {d, m, y};
	remDays = getDifference(d1, d2);
	
	if (remDays > 0) {
		gotoxy(60, 20);
		printf("Mobile Number:     %s",mobileNumber);
		gotoxy(60, 22);
		printf("There are %d days for the expiry of plan", remDays);
		Sleep(3000);
	}
	else if (remDays == 0) {
		gotoxy(60, 20);
		printf("Mobile Number:     %s",mobileNumber);
		gotoxy(60, 22);
		if (acc[i].numberOfPlans != 0)
			printf("Your plan has been expired today");
		else
			printf("NO PLANS");
		Sleep(3000);
	}
	else if (remDays < 0) {
		gotoxy(60, 20);
		printf("Mobile Number:     %s",mobileNumber);
		gotoxy(60, 22);
		printf("Your plan has expired %d days ago", (-1 * remDays));
		Sleep(3000);
	}
}	
	
void unregister(int users, char* mobileNumber) {
	system("cls");
	FILE *fp;
	int i;
	
	char fileName[20];
	strcpy(fileName, mobileNumber);
	strcat(fileName, ".txt");
	remove(fileName);
	remove("JioCustomers.csv");
	fp = fopen("JioCustomers.csv", "w");
	for (i = 0; i < users; i++) {
		if ((strcmp(acc[i].userName, mobileNumber)) != 0) {
			fprintf(fp, "%s,%s,%d,%d/%d/%d,\n", acc[i].userName, acc[i].password, acc[i].numberOfPlans, acc[i].date, acc[i].month, acc[i].year);
		}
	}
	fclose(fp);
	
	gotoxy(56, 30);
	printf("You account has been succesfully unregistered\n");
	Sleep(5000);
}

void changePassword(int users, char* mobileNumber) {
	FILE *fp;
	int i, j = 0;
	
	FILE *fp1;
	fp1 = fopen("JioCustomers.csv", "r");
	char totalLine[100];
	while (fgets(totalLine, sizeof(totalLine), fp1)) {
		char* token;
		token = strtok(totalLine, ",");
		int r = strcmp(mobileNumber, token);
		if (r == 0) {
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			
			char* tk;
			tk = strtok(token, "/");
			sscanf(tk, "%d", &acc[j].date);
			tk = strtok(NULL, "/");
			sscanf(tk, "%d", &acc[j].month);
			tk = strtok(NULL, "/");
			sscanf(tk, "%d", &acc[j].year);
		}
		j += 1;
	}
	fclose(fp1);
	
	remove("JioCustomers.csv");
	fp = fopen("JioCustomers.csv", "w");
	for (i = 0; i < users; i++) {
		if ((strcmp(acc[i].userName, mobileNumber)) != 0) {
			fprintf(fp, "%s,%s,%d,%d/%d/%d,\n", acc[i].userName, acc[i].password, acc[i].numberOfPlans, acc[i].date, acc[i].month, acc[i].year);
		}
		else {
			system("cls");
			char pass[20], check[20];
			char ch;
			int j = 0, l = 0, result = 0, res = 1;
			gotoxy(60, 16);
			printf("Enter new password: ");
			while (1) {
				ch = getch();
				if (ch == ENTER) 
					break;
				pass[j] = ch;
				putchar('*');
				j++;
			}
			pass[j] = '\0';
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
				result = strcmp(pass, check);
				if (result != 0) {
					l += 2;
					gotoxy(60, 18 + l);
					printf("Password didn't match");
					l += 2;
					res = 0;
				}
				else {
					gotoxy(60, 27);
					printf("Password has been updated\n");
					Sleep(5000);
					strcpy(acc[i].password, pass);
					fprintf(fp, "%s,%s,%d,%d/%d/%d,\n", acc[i].userName, acc[i].password, acc[i].numberOfPlans, acc[i].date, acc[i].month, acc[i].year);
				}
			}while (result != 0);
		}
	}
	fclose(fp);
}

void plans(char* mobileNumber) {
	system("cls");
	int choice;
	int finish = 0;
	do {
		gotoxy(65, 15);
		printf("1>> 1.5GB per day");
		gotoxy(65, 18);
		printf("2>> 2GB per day");
		gotoxy(65, 21);
		printf("3>> TopUp plans");
		gotoxy(65, 24);
		printf("4>> GoBack");
		gotoxy(61, 28);
		printf("   Enter your choice: ");
		scanf("%d", &choice);
		switch(choice) {
			case 1:
				Plan1("1.5GB.txt", mobileNumber, choice);
				finish = 1;
				break;
			case 2:
				Plan1("2GB.txt", mobileNumber, choice);
				break;
			case 3:
				Topup("Topup.txt", mobileNumber);
				break;
			case 4:
				finish = 1;
				break;
			default:
				printf("\nInvalid option entered\n");
				break;
		}
	}while (finish != 1);
}

void Plan1(char* fileName, char* mobileNumber, int choice) {
	system("cls");
	FILE *fp;
	fp = fopen(fileName, "r");
	char totalLine[300];
	while (fgets(totalLine, sizeof(totalLine), fp)) {
		puts(totalLine);
	}
	fclose(fp);
	
	printf("\n\n");
	int plan;
	printf("Enter your plan: ");
	scanf("%d", &plan);
	
	char fname[20];
	strcpy(fname, mobileNumber);
	strcat(fname, ".txt");
	FILE *fp1, *fp2;
	fp1 = fopen(fileName, "r");
	fp2 = fopen(fname, "a");
	fprintf(fp2, "-------------------------------------------------------------------\n");
	int count = 0;
	while (fgets(totalLine, sizeof(totalLine), fp1)) {
		count += 1;
		if (plan == 1) {
			if ((count >= 3) && (count <= 7)) {
				fprintf(fp2, "%s", totalLine);
			}
		}
		else if (plan == 2) {
			if ((count >= 9) && (count <= 13)) {
				fprintf(fp2, "%s", totalLine);
			}
		}
		else if (plan == 3) {
			if ((count >= 15) && (count <= 19)) {
				fprintf(fp2, "%s", totalLine);
			}
		}
		else if (plan == 4) {
			if ((count >= 21) && (count <= 25)) {
				fprintf(fp2, "%s", totalLine);
			}
		}
		else if (plan == 5) {
			int r;
			r = strcmp(fileName, "1.5GB.txt");
			if (r == 0) {
				if ((count >= 27) && (count <= 31)) {
					fprintf(fp2, "%s", totalLine);
				}
			}
			else {
				printf("You have entered wrong choice\n");
				system("cls");
				return;
			}
		}
		else {
			printf("You have entered wrong choice\n");
			system("cls");
			return;
		}
	}
	fclose(fp1);
	fclose(fp2);
	
	printf("\nYour plan has been recharged succesfully\n");
	Sleep(3000);
	update(mobileNumber, plan, choice);
	system("cls");
}

void Topup(char* fileName, char* mobileNumber) {
	system("cls");
	FILE *fp;
	fp = fopen(fileName, "r");
	char totalLine[300];
	while (fgets(totalLine, sizeof(totalLine), fp)) {
		puts(totalLine);
	}
	fclose(fp);
	
	printf("\n\n");
	int topup;
	printf("Enter your topup: ");
	scanf("%d", &topup);
	
	char fname[20];
	strcpy(fname, mobileNumber);
	strcat(fname, ".txt");
	FILE *fp1, *fp2;
	fp1 = fopen(fileName, "r");
	fp2 = fopen(fname, "a");
	fprintf(fp2, "-------------------------------------------------------------------\n");
	int count = 0;
	while (fgets(totalLine, sizeof(totalLine), fp1)) {
		count += 1;
		if (topup == 1) {
			if (count == 3) {
				fprintf(fp2, "%s", totalLine);
			}
		}
		else if (topup == 2) {
			if (count == 5) {
				fprintf(fp2, "%s", totalLine);
			}
		}
		else if (topup == 3) {
			if (count == 7) {
				fprintf(fp2, "%s", totalLine);
			}
		}
		else if (topup == 4) {
			if (count == 9) {
				fprintf(fp2, "%s", totalLine);
			}
		}
		else if (topup == 5) {
			if (count == 11) {
				fprintf(fp2, "%s", totalLine);
			}
		}
	}
	fclose(fp1);
	fclose(fp2);
	
	printf("\nYour topup has been recharged succesfully\n");
	Sleep(3000);
	system("cls");
}

void update(char* mobileNumber, int plan, int choice) {
	int users = totalUsers();
	int i, j;
	j = 0;
	FILE *fp1;
	fp1 = fopen("JioCustomers.csv", "r");
	char totalLine[100];
	while (fgets(totalLine, sizeof(totalLine), fp1)) {
		char* token;
		token = strtok(totalLine, ",");
		int r = strcmp(mobileNumber, token);
		if (r == 0) {
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			
			char* tk;
			tk = strtok(token, "/");
			sscanf(tk, "%d", &acc[j].date);
			tk = strtok(NULL, "/");
			sscanf(tk, "%d", &acc[j].month);
			tk = strtok(NULL, "/");
			sscanf(tk, "%d", &acc[j].year);
		}
		j += 1;
	}
	fclose(fp1);
	
	for (i = 0; i < users; i++) {
		if ((strcmp(acc[i].userName, mobileNumber)) == 0) {
			acc[i].numberOfPlans++;
			break;
		}
	}
	
	int ad;
	if (choice == 1) {
		ad = days_1GB[plan - 1];
	}
	else if (choice == 2) {
		ad = days_2GB[plan - 1];
	}
	
	struct Date dt1;
	if (remDays < 0) {
		dt1 = addDays(acc[i].date, acc[i].month, acc[i].year, (ad + (-1 * remDays)));
	}
	else {
		dt1 = addDays(acc[i].date, acc[i].month, acc[i].year, ad);
	}
	
	FILE *fp;
	fp = fopen("JioCustomers.csv", "w");
	for (int i = 0; i < users; i++) {
		cashBack(mobileNumber, acc[i].numberOfPlans);
		if ((strcmp(acc[i].userName, mobileNumber)) == 0) {
			acc[i].date = dt1.date;
			acc[i].month = dt1.month;
			acc[i].year = dt1.year;
			fprintf(fp, "%s,%s,%d,%d/%d/%d,\n", acc[i].userName, acc[i].password, acc[i].numberOfPlans, dt1.date, dt1.month, dt1.year);
		}
		else if (acc[i].numberOfPlans == 0) {
			time_t currentTime;
	
			time(&currentTime); //Obtains Current Time
			
			struct tm *localTime = localtime(&currentTime);
			int date, month, year, ad;
			date = localTime->tm_mday;
			month = localTime->tm_mon + 1;
			year = localTime->tm_year + 1900;
			acc[i].date = date;
			acc[i].month = month;
			acc[i].year = year;
			fprintf(fp, "%s,%s,%d,%d/%d/%d,\n", acc[i].userName, acc[i].password, acc[i].numberOfPlans, date, month, year);
		}
		else {
			fprintf(fp, "%s,%s,%d,%d/%d/%d,\n", acc[i].userName, acc[i].password, acc[i].numberOfPlans, acc[i].date, acc[i].month, acc[i].year);
		}
	}
	fclose(fp);
}

void cashBack(char* mobileNumber, int plans) {
	int min = 50, max = 100;
	int range;
	range = (max - min) + 1;
	
	int cashback = (rand() % range) + min;
	
	FILE *fp;
	char fname[50];
	strcpy(fname, mobileNumber);
	strcat(fname, ".txt");
	
	fp = fopen(fname, "a");
	if (fp != NULL) {
		if ((plans % 5) == 0) {
			fprintf(fp, "Cash Back: Rs. %d\n", cashback);
		}
	}
	fclose(fp);
}

int isLeap(int y)  
{  
    if (y % 100 != 0 && y % 4 == 0 || y % 400 == 0)  
        return 1;  
		
    return 0;  
}

int offsetDays(int d, int m, int y)  
{  
    int offset = d;  
  
    if(m - 1 == 11)  
        offset += 335; 
    if(m - 1 == 10) 
        offset += 304; 
    if(m - 1 == 9) 
        offset += 273; 
    if(m - 1 == 8) 
        offset += 243; 
    if(m - 1 == 7) 
        offset += 212; 
    if(m - 1 == 6) 
        offset += 181; 
    if(m - 1 == 5) 
        offset += 151; 
    if(m - 1 == 4) 
        offset += 120; 
    if(m - 1 == 3) 
        offset += 90; 
    if(m - 1 == 2) 
        offset += 59; 
    if(m - 1 == 1) 
        offset += 31;  
  
    if (isLeap(y) && m > 2)  
        offset += 1;  
 
    return offset;  
}

void revoffsetDays(int offset, int y)  
{  
    int month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };  
  
    if (isLeap(y))  
        month[2] = 29;  
    int i;  
    for (i = 1; i <= 12; i++)  
    {  
        if (offset <= month[i])  
            break;  
        offset = offset - month[i];  
    }  
  
    d2 = offset;  
    m2 = i;  
}

struct Date addDays(int d1, int m1, int y1, int x)  
{  
    int offset1 = offsetDays(d1, m1, y1);  
    int remDays = isLeap(y1) ? (366 - offset1) : (365 - offset1);  
  
    int y2, offset2 = 0;  
    if (x <= remDays)  
    {  
        y2 = y1;  
        offset2 =offset1 + x;  
    }  
  
    else
    {    
        x -= remDays;  
        y2 = y1 + 1;  
        int y2days = isLeap(y2) ? 366 : 365;  
        while (x >= y2days)  
        {  
            x -= y2days;  
            y2++;  
            y2days = isLeap(y2) ? 366 : 365;  
        }  
        offset2 = x;  
    }  
    revoffsetDays(offset2, y2);
	
	//Creating Of Date variable
	struct Date d;
	d.date = d2;
	d.month = m2;
	d.year = y2;
	return d;
}

int countLeapYears(struct Date d)
{
    int years = d.year;
    if (d.month <= 2)
		years--;
    return years / 4 
           - years / 100
           + years / 400;
}

int getDifference(struct Date dt1, struct Date dt2)
{
    long int n1 = dt1.year * 365 + dt1.date;
 
    for (int i = 0; i < dt1.month - 1; i++)
        n1 += numberOfDaysInMonth[i];

    n1 += countLeapYears(dt1);
 
    long int n2 = dt2.year * 365 + dt2.date;
    for (int i = 0; i < dt2.month - 1; i++)
        n2 += numberOfDaysInMonth[i];
    n2 += countLeapYears(dt2);
	
    return (n2 - n1);
}