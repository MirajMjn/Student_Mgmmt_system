#include <stdio.h>
#include <stdlib.h> //cls
#include <conio.h>
#include <string.h>
//--------------------------------------------------------------------------------------------- header files

#define NUM_DIFF 48
#define ESC_KEY 27
#define ENTER_KEY 13
#define BKSPC_KEY 8
//--------------------------------------------------------------------------------------------- constants

void welcome();
int is_new_user();	//questions login or sign up
int signup();		//create new profile
void read_signup();
void display_signup();
void write_signup();
int login(); //under construction
void wipe();		//clean screen
void segment(); //draws line
//--------------------------------------------------------------------------------------------- functions
int length = 25; //length of horizontal rule

typedef struct roll_number{
    char college[4];
    int batch;
    char faculty[4];
    int roll;
} ioe_roll_num;

typedef struct student {
    char name[64];
    long long int contact;
    char email[64];
    int semester;
    char stream[16];
    ioe_roll_num roll;
    int access_level;
    char u_id[64];
    char pwd[16];
} stu;

typedef struct teacher {
    char name[64];
    long long int contact;
    char email[64];
    char sub[16];
    int access_level;
    char u_id[64];
    char pwd[16];
} teach;

typedef struct admin {
    char name[64];
    long long int contact;
    char email[64];
    int access_level;
    char u_id[64];
    char pwd[16];
} admn;

stu student_info;
teach teacher_info;
admn admin_info;

FILE *student_data;
FILE *teacher_data;
//--------------------------------------------------------------------------------------------- global variables

int main ()
{
	int new_user;
	int signup_status;
	int login_status;
	char redo; //answer to question, redo signup (failed case)

	welcome();

	home:
    new_user	= is_new_user(); //asks and returns answer of new user or not (0 or 1) =========> home page


    /*based on value of new user the following will be executed.
    1 -> sign up
    2 -> login

    */
    switch (new_user) //compares answer to returning user question
	{
        // sign up
        case 1:

			//if failed and chose to redo flow comes here ->
            repeat_signup:

			//goes to the sign up function
            signup_status	= signup();

			//Based on the sign up status the following are executed:
            if (signup_status == 1)
            {
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

void welcome()
{
    int exit_cont;
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

int signup()
{
	int status = 0, key;	//success status of sign in process

signup:	wipe();
	printf("SIGN-UP PAGE: \n\n");
	printf("\n\n\tAre you a ....... ?\n\n\t<1> Student\n\t<2> Teacher\n\t<ESC> To exit\n\t<BKSPC> To Go Home");

enter_role:;
	int access_level = getch() - NUM_DIFF;

	if (access_level == (ESC_KEY - NUM_DIFF)) //esc
	{
		//printf("\n %d", status);
		exit(0);
	}

	else if (access_level == (BKSPC_KEY - NUM_DIFF)) //return back
	{
		//printf("\n %d", status);
		return 13;
	}

	else if ((access_level != 1) && (access_level != 2)) //look for valid entry
	{
		//printf("\n %d", access_level);
		goto enter_role;
	}

	else
	{
		wipe();
	}

	read_signup(access_level);

	segment();

	printf("\nPress <ENTER> to confirm submission\nPress <ESC> to exit\nPress <x> to re-enter\nPress <BKSPC> to go back to previous screen");
	key = getch();
	switch(key)
	{
		case ENTER_KEY:

			display_signup(access_level);

			segment();
			printf("\nPress <ENTER> to confirm submission\nPress <ESC> to exit\nPress <x> to re-enter\n");
			enter_key: key = getch();
			switch (key)
			{
				case ENTER_KEY:
					switch (access_level) {
                        case 1:
                            student_data = fopen("student_records.txt", "w+");
                            fwrite(&student_info, sizeof(student_info), 1, student_data);
                            fclose(student_data);
                        break;

                        case 2:
                            teacher_data = fopen("teacher_records.txt", "w+");
                            fwrite(&teacher_info, sizeof(teacher_info), 1, teacher_data);
                            fclose(teacher_data);
                        break;

                        default:wipe();
                                printf("\n\tError while trying to write\n");
                                exit(1);

                    }
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
			read_signup(access_level);
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

void read_signup(int access_level)
{
    data_entry:
    printf("\nPLease Fill Out The Following Info Correctly: \n");
	switch(access_level)
	{
		case 1: //student

			printf("\n\tName\t:");
			scanf("%[^\n]", student_info.name);

			printf("\n\tContact\t:");
			scanf("%lld", &student_info.contact);

			printf("\n\tE-Mail\t:");
			scanf("%s", student_info.email);

			printf("\n\tSemester:");
			scanf("%d", &student_info.semester);

            printf("\n\tStream :/t <1>BCE <2>BCT <3>BEI <4>BEL");
            stream_entry:;
			int strm_opt = getch() - NUM_DIFF;
            switch (strm_opt)
            {
                    case 1:
                        strcpy(student_info.stream, "BCE");
                    break;
                    case 2:
                        strcpy(student_info.stream, "BCT");
                    break;
                    case 3:
                        strcpy(student_info.stream, "BEI");
                    break;
                    case 4:
                        strcpy(student_info.stream, "BEL");
                    break;

                    default: goto stream_entry;
            }

            printf("\n\tBATCH \t: ");
            scanf("%d", &student_info.roll.batch);
            printf("\n\tROLL\t: ");
            scanf("%d", &student_info.roll.roll);

            strcpy(student_info.roll.college, "ACE");
            strcpy(student_info.roll.faculty, student_info.stream);

            student_info.access_level = access_level;

		break;

        case 2:

			printf("\n\tName\t:");
			scanf("%[^\n]", teacher_info.name);

			printf("\n\tContact\t:");
			scanf("%lld", &teacher_info.contact);

			printf("\n\tE-Mail\t:");
			scanf("%s", teacher_info.email);

			printf("\n\tSubject\t:");
			scanf(" %[^\n]", teacher_info.sub);

            teacher_info.access_level = access_level;

		break;

		default:
		printf("\n\tFatal Error!\n\t");
		exit(1);
	}
}

void display_signup(int access_level)
{
    wipe();
    printf("\nPlease Check The Information Entered Carefully\n\n");
    if (access_level == 1){

        printf("\n\tName\t: %s\n", student_info.name);
        printf("\n\tContact\t: %lld\n", student_info.contact);
        printf("\n\tEmail\t: %s\n", student_info.email);
        printf("\n\tSemester : %d\n", student_info.semester);
        printf("\n\tStream \t: %s\n", student_info.stream);
        printf("\n\tIOE Roll: %s%03d%s%03d\n", student_info.roll.college, student_info.roll.batch, student_info.roll.faculty, student_info.roll.roll);
        printf("\n\tType\t: STUDENT\n");
    }
    else{

        printf("\n\tName\t: %s\n", teacher_info.name);
        printf("\n\tContact\t: %lld\n", teacher_info.contact);
        printf("\n\tEmail\t: %s\n", teacher_info.email);
        printf("\n\tSubject\t: %s\n", teacher_info.sub);
        printf("\n\tType\t: TEACHER\n");
    }
}

void write_signup(int access_level)
{

}

int login()
{
	wipe();
	printf("LOGIN PAGE: \n\n");
	printf("\n\n\tLOGIN PAGE HERE!!\n\n");
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
