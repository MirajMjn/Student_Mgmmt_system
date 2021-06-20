#include <stdio.h>
#include <stdlib.h> //cls
#include <conio.h>
//--------------------------------------------------------------------------------------------- header files

#define NUM_DIFF 48
#define ESC_KEY 27
#define ENTER_KEY 13
#define BKSPC_KEY 8
//--------------------------------------------------------------------------------------------- constants

int is_new_user();	//questions login or sign up
int signup();		//create new profile
int login(); //under construction
void wipe();		//clean screen
void segment(); //draws line
//--------------------------------------------------------------------------------------------- functions
int length = 25;

char fname[16];
char lname[16];
long long int contact;
char email[32];
int grade;
char stream[16];	// admin teacher student
char sub[16];
int access_level = 0;// 1-> admin, 2-> teachers, 3-> student

char u_id[32];
char pwd[8];
//--------------------------------------------------------------------------------------------- global variables

int main ()
{
	int new_user;
	int signup_status;
	int login_status;
	char redo; //answer to question, redo signup (failed case)
	int exit_cont;


//---------------------------------------------------------------------------------------------	<opening welcome>
	printf("\t\t\t\t\t**************************************\t\t\n\n");
	printf("\t\t\t\t\t-WELCOME TO STUDENT MANAGEMENT SYSTEM-\n\n");
	printf("\t\t\t\t\t**************************************\t\t\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t\t\t\t\t\tThe Project Was Created By:-\n\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t-Miraj Maharjan\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t-Sajja Aryal\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t-Norgen Moktan\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t-Bipin Subedi\n");
	printf("\tPlease contact ADMIN for queries\n\n");

	printf("\tPress ANY KEY to continue, <ESC> to exit. \n");
	exit_cont = getch();
	//printf("\n%d", exit_cont);
	if (exit_cont == ESC_KEY)
	{
		exit(0);
	}
//---------------------------------------------------------------------------------------------</opening welcome>

	home: new_user	= is_new_user(); //asks and returns answer of new user or not (0 or 1) =========> home page
	switch (new_user) //compares answer to returning user question
	{
		case 1:// sign up

			repeat_signup://if failed and chose to redo flow comes here ->

			signup_status	= signup(); //goes to the sign up section ----------------------> goes to sign up page

			if (signup_status == 1) {
				wipe();
				printf("\n\tSUCCESSFULLY SIGNED UP\n\t<Enter to continue>\n");
				getch();

				login_status = login();
			}

			else if (signup_status == 13)
			{
				goto home;
			}

			else
			{
				wipe();
				printf("\n\tFAILED SIGNED UP\n\tDo you wish to try again?<Y/N>\n");
				repeat_signup_question:;
				redo = getch();
				if ((redo != 'y')&&(redo != 'Y')&&(redo != 'n')&&(redo != 'N')&&(redo != ESC_KEY))
				{
					goto repeat_signup_question;
				}

				else if ((redo == 'y')||(redo == 'Y'))
				{
					goto repeat_signup;
				}

				else if ((redo == 'n')||(redo == 'N')||(redo == ESC_KEY))
				{
					exit(0);
				}
			}
		break;

		case 0:
			login_status = login();
		break;

		default: printf("\nERROR\n");
	}

	exit:printf("\n\n\tCODE TRMINATED.....");
	return 0;
}

int is_new_user()
{
	int status;
	wipe();
	printf(" \t\t\t\t\t\tHOME PAGE\n");
	printf("\t\t\t\t\t--------------------------\n\n");
	printf(
		"\n\tPlease enter key based on requirement :\n\n \tlogin\t->(0)\n \tsign-up\t->(1)\n\n\n\t<PRESS ESC KEY TO EXIT>\n\t"
	);
input:
	status = getch() - NUM_DIFF; //ascii 48 -> ...

	if (status == (ESC_KEY - NUM_DIFF))
	{
		exit(0);
	}

	else if ((status != 1) && (status != 0))
	{
		//printf("\n %d", status);
		goto input;
	}
	return status;
}

int login()
{
	wipe();
	printf("LOGIN PAGE: \n\n");
	printf("\n\n\tLOGIN PAGE HERE!!\n\n");
}

int signup()
{
	int status = 0, key;	//success status of sign in process

signup:	wipe();
	printf("SIGN-UP PAGE: \n\n");
	printf("\n\n\tAre you a ....... ?\n\n\t<1> Student\n\t<2> Teacher\n\t<ESC> To exit\n\t<BKSPC> To Go Home");

enter_role:
	access_level = getch() - NUM_DIFF;

	if (access_level == (ESC_KEY - NUM_DIFF))
	{
		//printf("\n %d", status);
		exit(0);
	}

	else if (access_level == (BKSPC_KEY - NUM_DIFF))
	{
		//printf("\n %d", status);
		return 13;
	}

	else if ((access_level != 1) && (access_level != 2))
	{
		//printf("\n %d", access_level);
		goto enter_role;
	}

	else
	{
		wipe();
	}

	data_entry: printf("\nPLease Fill Out The Following Info Correctly: \n");
	switch(access_level)
	{
		case 1: //student
			printf("\n\tName\t:");
			scanf("%s %s", &fname, &lname);

			printf("\n\tContact\t:");
			scanf("%lld", &contact);

			printf("\n\tE-Mail\t:");
			scanf("%s", &email);

			printf("\n\tStream\t:");
			scanf("%s", &stream);
		break;

		case 2: //teacher
			printf("\n\tName\t:");
			scanf("%s %s", &fname, &lname);

			printf("\n\tContact\t:");
			scanf("%lld", &contact);

			printf("\n\tE-Mail\t:");
			scanf("%s", &email);

			printf("\n\tSubject\t:");
			scanf("%s", &sub);
		break;

		default:
		printf("\n\tFatal Error!\n\t");
		exit(1);
	}
	segment();
	printf("\nPress <ENTER> to confirm submission\nPress <ESC> to exit\nPress <x> to re-enter\nPress <BKSPC> to go back to previous screen");
	key = getch();
	switch(key)
	{
		case ENTER_KEY:
			wipe();
			printf("\nPlease Check The Information Entered Carefully\n\n");
			printf("\n\tName\t: %s %s\n", fname, lname);
			printf("\n\tContact\t: %lld\n", contact);
			printf("\n\tEmail\t: %s\n", email);
			if (access_level == 1){
				printf("\n\tStream\t: %s\n", stream);
				printf("\n\tType\t: STUDENT\n");
			}
			else{
				printf("\n\tSubject\t: %s\n", sub);
				printf("\n\tType\t: TEACHER\n");
			}
			segment();
			printf("\nPress <ENTER> to confirm submission\nPress <ESC> to exit\nPress <x> to re-enter\n");
			enter_key: key = getch();
			switch (key)
			{
				case ENTER_KEY:
					printf("//Data needs to be stored.");
					getch();
					status = 1;
				break;

				case ('x'):
				case ('X'):
					goto signup;
				break;

				case ESC_KEY:
					exit(0);
				break;
				default: goto enter_key;
			}
		break;

		case BKSPC_KEY:
			goto data_entry;
		break;

		case ('x'):
		case ('X'):
			goto signup;
		break;

		case ESC_KEY:
			exit(0);
		break;
	}
	return status;
}

void wipe()
{
	system("cls");
}

void segment()
{
	int i;
	for (i = length; i >= 1; i--)
	{
		printf("__ ");
	}
	printf("\n");
}
