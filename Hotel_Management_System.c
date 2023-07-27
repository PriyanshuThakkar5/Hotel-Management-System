#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<unistd.h>

void roomAdd();
void roomEdit();
void roomDel();
void roomSearch();
void roomView();
void newUser(int isUpd);
void newData();
void login(int isUpd);
void menu();
void viewHere(char bkID[20],char rmID[20]);
void readTok(char str[400]);
void editMenu();
void returnMenu();
void clearscreen();
void spcDash();
void dashSpc();

struct CustomerDetails
{
    char bookingID[20];
    char roomNo[20];
    char custName[20];
    char custAddress[100];
    char custPhone[20];
    char custPhoneISD[20];
    char custNationality[20];
    char custEmail[50];
    char DOA[20];
    char noOfDays[20];
} cd;

char name[25],pwd[25],ver[25],pass[20],usr[20];
char bookID[10],roomID[10];
char buffer1[25],temp[400],temp2[400];

int main()
{
    login(0);
    newData();
    menu();
    return 0;
}

void login(int isUpd)
{

    // isUpd = 1 means Update the Credentials
    // isUpd = 0 means New User

    clearscreen();

    FILE *fileExist;
    if(access("UserData.txt", F_OK) != 0 || isUpd!=0)
    {
        newUser(isUpd);

        // Remove Existing User Credentials for Updating
        if(isUpd!=0)
            remove("UserData.txt");

        FILE *fp;

        fp = fopen ("UserData.txt","a+");

        if(isUpd!=0)
            printf("Creating a New User Database...");

        else
            printf("Updating New User Database...");

        fputs(name,fp);
        fputs("\n",fp);
        fputs(pwd,fp);
        fputs("\n",fp);

        fclose(fp);

        printf("Done!");

        if(isUpd!=0)
        {
            clearscreen();
            menu();
        }
    }


    // Execute if Login Data Exists
    else
    {

        FILE *fr;
        fr = fopen("UserData.txt","r");

        fgets(name,25,fr);
        fgets(pwd,25,fr);

        int nameLen=strlen(name);
        name[nameLen-1]='\0';

        int pwdLen=strlen(pwd);
        pwd[pwdLen-1]='\0';

        char username[25];
        char password[25];

        fclose(fr);

loginStart:

        printf("\n\tEnter your login: ");

        gets(username);


        if(strcmp(username,name)==0)
        {

            printf("\tEnter your password:");


            // To Hide Password on Input Screen
            int i=0;
            char c='c';
            while(i<25)
            {
                password[i]=getch();
                c=password[i];
                if(c==13)
                    break;
                else printf("*");
                i++;
            }
            password[i]='\0';


            if(strcmp(password,pwd)==0)
            {
                printf("\033[0;32m");
                printf("\n\n\tWelcome.Login Success!");
                printf("\033[0;3m");
                printf("\n\tPress any key to continue...");
                getch();
            }
            else
            {
                printf("\033[0;31m");
                printf("\n\n\tError: Incorrect Password");
                printf("\033[0;3m");
                printf("\n\tPress any key to retry: ");
                getch();
                clearscreen();
                goto loginStart;
            }
        }
        else
        {
            printf("\033[0;31m");
            printf("\n\n\tError: Incorrect User");
            printf("\033[0;3m");
            printf("\n\tPress any key to retry: ");
            getch();
            clearscreen();
            goto loginStart;
        }

    }
}

void newUser(int isUpd)
{

    clearscreen();

    fflush(stdin);
    int pwdLen,digi,up,low,schar,isErr = 0;
    printf("\tCreate New Login:\n\tEnter your Name: ");
    gets(name);

passStart:
    clearscreen();

    digi=0;
    up=0;
    low=0;
    schar=0;

    printf("\tHello %s!, Please enter your password: ",name);

    int i=0;
    char c=' ';
    while(i<25)
    {
        pwd[i]=getch();
        c=pwd[i];
        if(c==13)
            break;
        else printf("*");
        i++;
    }
    pwd[i]='\0';

    pwdLen=strlen(pwd);


    // Check Length of Password

    if(pwdLen<5)
    {
        printf("\033[0;31m");
        printf("\n\tError: Password should contain minimum 5 characters ");
        printf("\033[0;3m");
        printf("\n\tPress any key to retry: ");
        getch();
        goto passStart;
    }

    else if(pwdLen>12)
    {
        printf("\033[0;31m");
        printf("\n\tError: Password should not exceed 12 characters ");
        printf("\033[0;3m");
        printf("\n\tPress any key to retry: ");
        getch();
        goto passStart;
    }

    // Check Characters types used

    else
    {
        for(int i=0; pwd[i]!='\0'; i++)
        {
            if(pwd[i]>='A' && pwd[i]<='Z')
                up++;
            if(pwd[i]>='a' && pwd[i]<='z')
                low++;
            if(pwd[i]>='0' && pwd[i]<='9')
                digi++;
            if(pwd[i]=='@'||pwd[i]=='#'||pwd[i]=='$')
                schar++;
        }
    }


    //Password Errors
    if(up==0)
    {
        printf("\033[0;31m");
        printf("\n\tThere must be at least one Uppercase");
        printf("\033[0;3m");
        isErr=1;
    }
    if(low==0)
    {
        printf("\033[0;31m");
        printf("\n\tThere must be at least one Lowercase");
        printf("\033[0;3m");
        isErr=1;
    }
    if(digi==0)
    {
        printf("\033[0;31m");
        printf("\n\tThere must be at least one Digit");
        printf("\033[0;3m");
        isErr=1;
    }
    if(schar==0)
    {
        printf("\033[0;31m");
        printf("\n\tThere must be at least one Special Character");
        printf("\033[0;3");
        isErr=1;
    }

    if(isErr==1)
    {
        printf("\n\n\tPress any key to retry: ");
        getch();
        goto passStart;
    }
    else
    {
        printf("\n\tConfirm your Password: ");
        int i=0;
        char c=' ';

        fflush(stdin);
        while(i<25)
        {
            ver[i]=getch();
            c=ver[i];
            if(c==13)
                break;
            else printf("*");
            i++;
        }
        ver[i]='\0';

        if(strcmp(pwd,ver)==0)
        {
            printf("\033[0;32m");
            printf("\n\tWelcome %s, your is Password Verified",name);
            printf("\033[0;3m");
            printf("\n\tPress any key to continue: ");
            fflush(stdin);
            getch();
            fflush(stdin);
            return;
        }
        else
        {
            printf("\033[0;31m");
            printf("\nPassword did not match");
            printf("\033[0;3m");
            printf("\nPress any key to retry: ");
            fflush(stdin);
            getch();
            fflush(stdin);
            clearscreen();
            goto passStart;
        }
    }

    fflush(stdin);
    clearscreen();
    returnMenu();
}

void menu()
{
    clearscreen();

    printf("\n");
    printf("\t***********************************************************\n");
    printf("\t*                                                         *\n");
    printf("\t*          0    0  000000  0       0       000000         *\n");
    printf("\t*          0    0  0       0       0       0    0         *\n");
    printf("\t*          000000  000000  0       0       0    0         *\n");
    printf("\t*          0    0  0       0       0       0    0         *\n");
    printf("\t*          0    0  000000  000000  000000  000000         *\n");
    printf("\t*                                                         *\n");
    printf("\t***********************************************************\n");
    printf("\t*                                                         *\n");
    printf("\t*                Welcome to our services!                 *\n");
    printf("\t*                  How may we help you?                   *\n");
    printf("\t*                                                         *\n");
    printf("\t********************* ||MAIN MENU|| ***********************\n");
    printf("\t*                                                         *\n");
    printf("\t*            Please enter your choice for menu:           *\n");
    printf("\t*                                                         *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*          | Enter 1 -> View Occupants Records |          *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*          | Enter 2 -> New  Booking           |          *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*          | Enter 3 -> Delete Booking         |          *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*          | Enter 4 -> Search Bookings        |          *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*          | Enter 5 -> Edit Booking           |          *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*          | Enter 6 -> Exit                   |          *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*          | Enter 7 -> Change Login           |          *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*                                                         *\n");
    printf("\t***********************************************************\n");

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("\n\tTime now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    int n;
    fflush(stdin);

mainMenuStart:
    printf("\nEnter your choice number:");
    scanf("%d", &n);

    switch(n)
    {
    case 1:
        roomView();
        break;
    case 2:
        roomAdd();
        break;
    case 3:
        roomDel();
        break;
    case 4:
        roomSearch();
        break;
    case 5:
        roomEdit();
        break;
    case 6:
        exit(0);
        break;
    case 7:
        login(1);
    default:
        printf("\033[0;31m");
        printf("Invalid Input. Please Try Again!");
        printf("\033[0;3m");
        goto mainMenuStart;

    }

}

void newData()
{

    FILE *fileExist;
    if(access("Bookings.csv", F_OK) != 0)
    {
        printf("Creating a New Booking Database...");

        FILE *fp;
        fp = fopen ("Bookings.csv","a+");
        fprintf(fp,"BookingID,RoomNo.,Name,ResidentialAddress,PhoneNo.,ISD,Nationality,EmailAddress,DateOfArrival,NightsStay\n");
        printf("Created.");
        fclose(fp);
    }

}

void roomAdd()
{

    FILE *f;
    f=fopen("Bookings.csv","a+");

    clearscreen();
    printf("\n*******************Enter Customer Details******************");

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("\nTime now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    printf("\nBooking ID: ");
    scanf("%s",cd.bookingID);

    printf("\nRoom Number: ");
    scanf("%s",cd.roomNo);

    printf("Enter Name: ");
    fflush(stdin);
    scanf("%[^\n]s",cd.custName);
    spcDash(1);

    printf("Enter Address: ");
    fflush(stdin);
    scanf("%[^\n]s",cd.custAddress);
    spcDash(2);

    printf("Enter Contact Number: ");
    fflush(stdin);
    scanf("%s",cd.custPhone);
    printf("Enter Contact Number ISD: ");
    scanf("%s",cd.custPhoneISD);

    printf("Enter Nationality: ");
    scanf("%s",cd.custNationality);

    printf("Enter Email: ");
    scanf("%s",cd.custEmail);

    printf("Enter no of nights: ");
    scanf("%s",cd.noOfDays);

    printf("Enter Arrival date (dd/mm/yyyy):");
    fflush(stdin);
    scanf("%[^\n]s",cd.DOA);
    fflush(stdin);
    spcDash(3);

    fprintf(f,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",cd.bookingID,cd.roomNo,cd.custName,cd.custAddress,cd.custPhone,cd.custPhoneISD,cd.custNationality,cd.custEmail,cd.DOA,cd.noOfDays);
    fflush(stdin);

    printf("\033[0;32m");
    printf("Room booked!");
    printf("\033[0;3m");

    fclose(f);

    returnMenu();


}

void roomDel()
{

    FILE *f,*t;

    f=fopen("Bookings.csv","r");
    t=fopen("temp.csv","w");
    char temp[400],temp2[400];
    int i = 1;

    clearscreen();

    printf("Enter the Booking ID to be deleted: ");
    scanf("%s",bookID);

    while(feof(f)==0)
    {
        fscanf(f,"%s\n",temp);
        strcpy(temp2,temp);
        readTok(temp2);

        if(strcmp(cd.bookingID,bookID)==0)
        {
            i=0;
            continue;
        }
        else
            fprintf(t,"%s\n",temp);
    }

    if(i==1)
    {
        printf("\033[0;31m");
        printf("\nBooking ID not Found!");
        printf("\033[0;3m");
        fclose(f);
        fclose(t);
        returnMenu();

    }

    fclose(f);
    fclose(t);
    remove("Bookings.csv");
    rename("temp.csv","Bookings.csv");

    printf("\033[0;32m");
    printf("\nBooking Deleted!");
    printf("\033[0;3m");

    fclose(f);
    fclose(t);

    returnMenu();
}

void roomView()
{

    clearscreen();
    printf("\n");
    printf("\t********************* ||VIEW MENU|| ***********************\n");
    printf("\t*                                                         *\n");
    printf("\t*            Please enter your choice for menu:           *\n");
    printf("\t*                                                         *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*          | Enter 1 -> View in Notepad        |          *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*          | Enter 2 -> View in Excel          |          *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*          | Enter 3 -> View in Other Apps     |          *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*          | Enter 4 -> View here              |          *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*          | Enter 5 -> Main Menu              |          *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*                                                         *\n");
    printf("\t***********************************************************\n");

    int n;

viewMenuStart:
    printf("\nEnter your choice number:");
    scanf("%d", &n);

    switch(n)
    {
    case 1:
        system("notepad Bookings.csv");
        returnMenu();
        break;
    case 2:
        system("Bookings.csv");
        returnMenu();
        break;
    case 3:
        printf("Press any key to open the File Explorer. \nOpen Bookings.csv file in desired app.");
        getch();
        system("start .");
        returnMenu();
        break;
    case 4:
        viewHere("A","");
        returnMenu();
        break;
    case 5:
        returnMenu();
        break;
    default:
        printf("\033[0;31m");
        printf("Invalid Input. Please Try Again!");
        printf("\033[0;3m");
        goto viewMenuStart;
    }

}

void viewHere(char bkID[20], char rmID[20])
{

    FILE *f;
    char temp[400],temp2[400];
    int i;
    if((f=fopen("Bookings.csv","r"))==NULL)
        exit(0);
    clearscreen();

    printf("\n");
    for(int j=0; j<165; j++)
        printf("-");

    printf("\n");

    // Execute if redirected from View Menu (View All)
    if(strcmp(bkID,"A")==0)
    {

        while(feof(f)==0)
        {
            fscanf(f,"%s\n",temp);
            readTok(temp);

            dashSpc(1);
            dashSpc(2);

            printf("%-10s",cd.bookingID);
            printf("%-10s",cd.roomNo);
            printf("%-15s",cd.custName);
            printf("%-30s",cd.custAddress);
            printf("%-15s",cd.custPhone);
            printf("%-10s",cd.custPhoneISD);
            printf("%-17s",cd.custNationality);
            printf("%-30s",cd.custEmail);
            printf("%-15s",cd.DOA);
            printf("%-10s",cd.noOfDays);

            printf("\n");
        }
    }

    // Execute if redirected from Search (View Conditions)
    else
    {
        while(feof(f)==0)
        {
            fscanf(f,"%s\n",temp);
            strcpy(temp2,temp);
            readTok(temp2);

            if(strcmp(cd.bookingID,bkID)==0||strcmp(cd.roomNo,rmID)==0||strcmp(cd.bookingID,"BookingID")==0)
            {
                dashSpc(1);
                dashSpc(2);

                printf("%-10s",cd.bookingID);
                printf("%-10s",cd.roomNo);
                printf("%-15s",cd.custName);
                printf("%-30s",cd.custAddress);
                printf("%-15s",cd.custPhone);
                printf("%-10s",cd.custPhoneISD);
                printf("%-17s",cd.custNationality);
                printf("%-30s",cd.custEmail);
                printf("%-15s",cd.DOA);
                printf("%-10s",cd.noOfDays);

                printf("\n");;
                i=0;
                continue;
            }
        }

        if(i==1)
        {
            printf("\033[0;31m");
            printf("\nParameter did not Match!");
            printf("\033[0;3m");
            fclose(f);

            returnMenu();
        }


    }

    printf("\n");
    for(int j=0; j<165; j++)
        printf("-");

    fclose(f);
    returnMenu();

}

void readTok(char str[400])
{

    char sep[10][100];

    char * pch;
    pch = strtok (str,",");

    int i=0;
    while (pch != NULL)
    {
        strcpy(sep[i],pch);
        pch = strtok (NULL,",");
        i++;
    }

    strcpy(cd.bookingID,sep[0]);
    strcpy(cd.roomNo,sep[1]);
    strcpy(cd.custName,sep[2]);
    strcpy(cd.custAddress,sep[3]);
    strcpy(cd.custPhone,sep[4]);
    strcpy(cd.custPhoneISD,sep[5]);
    strcpy(cd.custNationality,sep[6]);
    strcpy(cd.custEmail,sep[7]);
    strcpy(cd.DOA,sep[8]);
    strcpy(cd.noOfDays,sep[9]);

}

void roomSearch()
{

    clearscreen();
    printf("\n\n\n");
    printf("\t******************** ||SEARCH MENU|| **********************\n");
    printf("\t*                                                         *\n");
    printf("\t*            What do you want to search by?               *\n");
    printf("\t*                                                         *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*          | Enter 1 -> By Booking ID          |          *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*          | Enter 2 -> By Room No.            |          *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*          | Enter 3 -> Main Menu              |          *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*                                                         *\n");
    printf("\t***********************************************************\n");

    int m;
    char n[20];

searchMenuStart:

    printf("\nEnter your choice number: ");
    scanf("%d", &m);

    if(m==1||m==2)
    {
        printf("\nEnter search parameter: ");
        scanf("%s", n);
    }


    switch(m)
    {
    case 1:
        viewHere(n,"");
        break;
    case 2:
        viewHere("",n);
        break;
    case 3:
        returnMenu();
        break;
    default:
        printf("\033[0;31m");
        printf("Invalid Input. Please Try Again!");
        printf("\033[0;3m");
        goto searchMenuStart;
    }

}

void roomEdit()
{

    FILE *f,*t;

    f=fopen("Bookings.csv","r");
    t=fopen("temp.csv","w");
    char temp[400],temp2[400];

    clearscreen();

    printf("Enter the Booking ID to Edit: ");
    scanf("%s",bookID);

    int i = 1;

    while(feof(f)==0)
    {
        fscanf(f,"%s\n",temp);
        strcpy(temp2,temp);
        readTok(temp2);

        if(strcmp(cd.bookingID,bookID)==0)
        {
            i=0;
            dashSpc(1);
            dashSpc(2);

            for(int j=0; j<165; j++)
                printf("-");
            printf("\nBookingID RoomNo.   Name           ResidentialAddress            PhoneNo.       ISD  Nationality      EmailAddress        DateOfArrival  NightsStay\n");
            printf("%-10s",cd.bookingID);
            printf("%-10s",cd.roomNo);
            printf("%-15s",cd.custName);
            printf("%-30s",cd.custAddress);
            printf("%-15s",cd.custPhone);
            printf("%-10s",cd.custPhoneISD);
            printf("%-17s",cd.custNationality);
            printf("%-30s",cd.custEmail);
            printf("%-15s",cd.DOA);
            printf("%-10s",cd.noOfDays);

            printf("\n");
            for(int j=0; j<165; j++)
                printf("-");

            editMenu();
            fprintf(t,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",cd.bookingID,cd.roomNo,cd.custName,cd.custAddress,cd.custPhone,cd.custPhoneISD,cd.custNationality,cd.custEmail,cd.DOA,cd.noOfDays);
            printf("Done");
        }
        else
            fprintf(t,"%s\n",temp);
    }

    if(i==1)
    {
        printf("\033[0;31m");
        printf("\nBooking ID not Found!");
        printf("\033[0;3m");
        fclose(f);
        fclose(t);
        printf("\nPress any key to return to Edit Menu: ");
        getch();
        clearscreen();
        roomEdit();
    }

    fclose(f);
    fclose(t);
    remove("Bookings.csv");
    rename("temp.csv","Bookings.csv");
    printf("\033[0;32m");
    printf("\nBooking Edited!");
    printf("\033[0;3m");
    fclose(f);
    fclose(t);

    printf("\nPress any key to return to Edit Menu: ");
    getch();
    clearscreen();
    roomEdit();

}

void editMenu()
{

    printf("\n\n\n");
    printf("\t********************* ||EDIT MENU|| ***********************\n");
    printf("\t*                                                         *\n");
    printf("\t*          Please enter your choice for editing:          *\n");
    printf("\t*                                                         *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*          | Enter 1 -> Room No.               |          *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*          | Enter 2 -> Customer Name          |          *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*          | Enter 3 -> Customer Address       |          *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*          | Enter 4 -> Customer Phone Number  |          *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*          | Enter 5 -> Date of Arrival        |          *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*          | Enter 6 -> Period of Stay (Night) |          *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*          | Enter 7 -> Main Menu              |          *\n");
    printf("\t*          |-----------------------------------|          *\n");
    printf("\t*                                                         *\n");
    printf("\t***********************************************************\n");

    int n;

editMenuStart:

    printf("\nEnter your choice number:");
    scanf("%d", &n);

    switch(n)
    {
    case 1:
        printf("\nRoom Number: ");
        scanf("%s",cd.roomNo);
        break;
    case 2:
        printf("Enter Name: ");
        fflush(stdin);
        scanf("%[^\n]s",cd.custName);
        spcDash(1);
        fflush(stdin);
        break;
    case 3:
        printf("Enter Address: ");
        fflush(stdin);
        scanf("%[^\n]s",cd.custAddress);
        spcDash(2);
        fflush(stdin);
        break;
    case 4:
        printf("Enter Contact Number: ");
        scanf("%s",cd.custPhone);
        printf("Enter Contact Number ISD: ");
        scanf("%s",cd.custPhoneISD);
        break;
    case 5:
        printf("Enter Arrival date (dd/mm/yyyy): ");
        fflush(stdin);
        scanf("%[^\n]s",cd.DOA);
        spcDash(3);
        fflush(stdin);
        break;
    case 6:
        printf("Enter no of nights: ");
        scanf("%s",cd.noOfDays);
        break;
    case 7:
        returnMenu();
        break;
    default:
        printf("\033[0;31m");
        printf("Invalid Input. Please Try Again!");
        printf("\033[0;3m");
        goto editMenuStart;
    }


}

void clearscreen()
{

    system("cls");
    fflush(stdin);

    printf("\t***********************************************************\n");
    printf("\t*                                                         *\n");
    printf("\t*                 7 Mirror Hotels Ltd.                    *\n");
    printf("\t*                                                         *\n");
    printf("\t***********************************************************\n");

}

void spcDash(int a)
{
    //Name
    if(a==1)
        for(int i =0; i<strlen(cd.custName); ++i)
            if(cd.custName[i]==' ')
                cd.custName[i]='-';
            else
                continue;

    //Address
    else if (a==2)
        for(int i =0; i<strlen(cd.custAddress); ++i)
            if(cd.custAddress[i]==' ')
                cd.custAddress[i]='-';
            else if(cd.custAddress[i]==',')
                cd.custAddress[i]='_';
            else
                continue;

    //Date of Arrival
    else if (a==3)
        for(int i =0; i<strlen(cd.DOA); ++i)
            if(cd.DOA[i]==' '||cd.DOA[i]=='-')
                cd.DOA[i]='/';
            else
                continue;

    else
        return;
}

void dashSpc(int a)
{
    if(a==1)
        for(int i =0; i<strlen(cd.custName); ++i)
            if(cd.custName[i]=='-')
                cd.custName[i]=' ';
            else
                continue;

    else if (a==2)
        for(int i =0; i<strlen(cd.custAddress); ++i)
            if(cd.custAddress[i]=='-')
                cd.custAddress[i]=' ';
            else if(cd.custAddress[i]=='_')
                cd.custAddress[i]=',';
            else
                continue;

    else
        return;
}

void returnMenu()
{

    printf("\nPress any key to return to Main Menu: ");
    getch();
    fflush(stdin);
    menu();
}


//*************************** END OF CODE ************************
