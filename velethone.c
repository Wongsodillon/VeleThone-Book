#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

void menu1();
void menu2();
void menu3();
void menu4();

int counter = 0;

typedef struct person
{
	char name[255];
	char number[255];
	char address[255];
}person;

person people[500];

void menuScreen()
{
	system("cls");
	int menu;
	printf("1. Add telephone book\n");
	printf("2. Search telephone book\n");
	printf("3. View telephone book\n");
	printf("4. Exit\n");
	do
	{
		printf(">> ");
		scanf("%i", &menu); getchar();
	}
	while(menu <= 0 || menu > 4);
	if (menu == 1)
	{
		menu1();
	}
	else if (menu == 2)
	{
		menu2();
	}
	else if (menu == 3)
	{
		menu3();
	}
	else if (menu == 4)
	{
		system("cls");
		printf("Through courage and perseverace, we shape and define our future\n");
		printf("                     Bluejacket 22-1\n");
		return;
	}
}

void binary_search(person people[], int left, int right, char target[])
{
	person temp;
	for (int i = 0; i < counter - 1; i++)
	{
		for (int j = 0; j < counter - 1 - i; j++)
		{
			if(strcmp(people[j].name, people[j+1].name) > 0)
			{
				temp = people[j];
				people[j] = people[j+1];
				people[j+1] = temp;
			}
		}
	}
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (strcmp(people[mid].name, target) == 0)
		{
			printf("Name: %s\nPhone Number: %s\nAddress: %s\n\n", people[mid].name, people[mid].number, people[mid].address);
			printf("Press enter to continue... \n");
			getch();
			system("cls");
			menuScreen();
			return;
		}
		else if (strcmp(people[mid].name, target) < 0)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	printf("No data found!\n\n");
	printf("Press enter to continue... ");
	getch();
	system("cls");
	menuScreen();
}


void menu1()
{
	system("cls");
	printf("--Add telephone book--\n");
	int loopnumber = 0;
	char name[255];
	char number[255];
	char address[255];
	do
	{
		printf("Please Input Name [Must be more than 3 characters long]: ");
		scanf("%[^\n]", name); getchar();
	}
	while (strlen(name) < 3);
	while (loopnumber == 0)
	{
		printf("Please Input Phone Number [10..12 characters long, must start with '0', must be a number]: ");
		scanf("%s", number); getchar();
		int flag = 0;
		for (int i = 0; number[i] != '\0'; i++)
		{
			if(number[i] <= 47 || number[i] > 57)
			{
				flag++;
			}
		}
		if (number[0] != '0')
		{
			printf("Phone number must start with '0'\n");
			continue;
		}
		if (flag != 0)
		{
			printf("Phone number must consists of only numbers\n");
			continue;
		}
		if (strlen(number) < 9 || strlen(number) > 12)
		{
			printf("Phone number must be between 10 to 12 characters long!\n");
			continue;
		}
		loopnumber = 1;
	}
	char check[10];
	do
	{
		int checkcount = 0;
		printf("Please Input Address [Must end with street]: ");
		scanf("%[^\n]", address); getchar();
		for (int i = strlen(address) - 6; address[i] != '\0'; i++)
		{
			check[checkcount] = address[i];
			checkcount++;
		}
	}
	while (strcmpi(check, "street") != 0);
	FILE *file;
	file = fopen("file.txt", "a");
	fprintf(file, "%s#%s#%s\n", name, number, address);
	fclose(file);

	printf("Phone data added successfully!\n");
	printf("Press enter to continue...");
	getch();
	system("cls");
	menuScreen();
}

void menu2()
{
	system("cls");
	counter = 0;
	char search[255];
	FILE *file;
	file = fopen("file.txt", "r");
	while (fscanf(file, "%[^#]#%[^#]#%[^\n]\n", people[counter].name, people[counter].number, people[counter].address) != EOF)
	{
		counter++;
	}
	printf("--Search telephone book--\n");
	printf("Input name to search data: ");
	scanf("%[^\n]", search); getchar();
	binary_search(people, 0, counter, search);
	fclose(file);
}

void menu3()
{
	system("cls");
	counter = 0;
	char view[5];
	printf("--View telephone book--\n\n");
	do
	{
		printf("How would you like to view telephone book ? [ASC | DESC]: ");
		scanf("%s", view);
	}
	while (strcmp(view, "ASC") != 0 && strcmp(view, "DESC") != 0);
	FILE *file;
	file = fopen("file.txt", "r");
	while (fscanf(file, "%[^#]#%[^#]#%[^\n]\n", people[counter].name, people[counter].number, people[counter].address) != EOF)
	{
		counter++;
	}
	person temp;
	if (strcmp(view, "ASC") == 0)
	{
		for (int i = 0; i < counter - 1; i++)
		{
			for (int j = 0; j < counter - 1 - i; j++)
			{
				if(strcmp(people[j].name, people[j+1].name) > 0)
				{
					temp = people[j];
					people[j] = people[j+1];
					people[j+1] = temp;
				}
			}
		}
		system("cls");
		printf("====================================================================================\n");
		printf("|No.  |  Name.            | Phone Number         | Address                         |\n");
		printf("====================================================================================\n");
		for (int i = 0; i < counter; i++)
		{
			printf("|%-5i|  %-13s    | %-12s         | %-32s|\n", i + 1, people[i].name, people[i].number, people[i].address);
		}
		printf("====================================================================================\n");
		fclose(file);
		printf("Press enter to continue... ");
		getch();
		system("cls");
		menuScreen();
	}
	else if (strcmp(view, "DESC") == 0)
	{
		for (int i = 0; i < counter - 1; i++)
		{
			for (int j = 0; j < counter - 1 - i; j++)
			{
				if(strcmp(people[j].name, people[j+1].name) < 0)
				{
					temp = people[j];
					people[j] = people[j+1];
					people[j+1] = temp;
				}
			}
		}
		system("cls");
		printf("====================================================================================\n");
		printf("|No.  |  Name.            | Phone Number         | Address                         |\n");
		printf("====================================================================================\n");
		for (int i = 0; i < counter; i++)
		{
			printf("|%-5i|  %-13s    | %-12s         | %-32s|\n", i + 1, people[i].name, people[i].number, people[i].address);
		}
		printf("====================================================================================\n");
		fclose(file);
		printf("Press enter to continue... ");
		getch();
		system("cls");
		menuScreen();
	}
	
}

int main(void)
{
	menuScreen();
}
