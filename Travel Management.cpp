#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<iostream>
#include<fstream>

using namespace std;

enum state{menu,loggedin};
enum state currentstate=menu;

typedef struct user
{
    char username[100];
    char password[100];
    char place[100];
    char passengername[20][20];
    int passengerage[10];
    char gender[6];
    int age;
    float price;
    int numtick;
    struct user *next;
}user;


char currentuser[50];

//user* InitializeList(user*);



user* InitializeList(user *h)
{
    user* t,*ptr,temp;
    FILE *fp;
    int cc=0,x;
    float ff;
    fp=fopen("stud.txt","r");

    if(fp==NULL)
        return NULL;

    if(fgetc(fp)==EOF)
        return NULL;

    rewind(fp);
	while(fscanf(fp,"%s %s %s %f %d %s %d",temp.username,temp.password,temp.place,&temp.price,&temp.numtick,temp.passengername,&temp.age)!=EOF)
	{
		ptr=(user*)malloc(sizeof(user));
		strcpy(ptr->username,temp.username);
		strcpy(ptr->password,temp.password);
		strcpy(ptr->place,temp.place);
		ptr->price=temp.price;
		ptr->numtick=temp.numtick;
		ptr->age=temp.age;
		ptr->next=NULL;

		if(h==NULL)
            h=t=ptr;
		else
		{
			h->next=ptr;
			h=ptr;
		}
	}
	fclose(fp);
    return t;
}

void WriteToFile(user *h)
{
    FILE *fp;
    fp=fopen("stud.txt","w");
    while(h!=NULL)
    {
        fprintf(fp,"%s %s %s %f %d %19s %d\n",h->username,h->password,h->place,h->price,h->numtick,h->passengername,h->passengerage);
        h=h->next;
    }
    fclose(fp);
}

user* AddUser(user* h)
{
    user *t;
    t=h;
    user *nw;
    nw=new user;
    cout<<"\n\t\t\t\tEnter username or email : ";
    cin>>nw->username;
    while(h!=NULL)
    {
        if(!strcmp(h->username,nw->username))
        {
            cout<<"\n\t\t\t\tThat email already exists\n";
            return t;
        }
        h=h->next;
    }
    h=t;
    cout<<"\t\t\t\tEnter password : ";
    cin>>nw->password;
    cout<<"\t\t\t\tEnter Gender : ";
    cin>>nw->gender;
    cout<<"\t\t\t\tEnter Age : ";
    cin>>nw->age;
    nw->next=NULL;
    strcpy(nw->place,"N/A");
    nw->price=0.0;
    nw->numtick=0;

    if(h==NULL)
    {
        h=t=nw;
    }
    else
    {
        while(h->next!=NULL)
        {
            h=h->next;
        }
        h->next=nw;
    }
    WriteToFile(t);
    return t;
}

void LoginUser(user* u)
{
 char username[30];
 char password[20];
 cout<<"\n\t\t\t\tEnter Email/Username : ";
 cin>>username;
 cout<<"\n\t\t\t\tEnter Password : ";
 cin>>password;
    while(u!=NULL)
    {
        if((!strcmp(u->username,username)) && (!strcmp(u->password,password)))
        {
            currentstate=loggedin;
            strcpy(currentuser,username);

            printf("\n\t\t\t\tLogin successful!\n");
            return;
        }
        else if((!strcmp(u->username,username)) && (strcmp(u->password,password)))
        {
            printf("\n\t\t\t\tPassword mismatch\n");
            return;
        }
        u=u->next;
    }
    printf("\n\t\t\t\tSorry, no such user record was found\n");
}


void ShowBrochure()
{
 char type[100];
 char ch;;
 cout<<"\t\t\t\ta. India Tour Packages\n";
 cout<<"\t\t\t\tb. International Tour Packages\n\n";
 cout<<"\t\t\t\tEnter Choice for tour packages: ";
 cin>>ch;
 switch(ch)
 {
  case 'a': strcpy(type, "India Tour Package");
            cout<<"\t\t\t\t1. ST - Shimla Tour Packages 6 Days 7 Nights Rs 18880/-\n";
            cout<<"\t\t\t\t2. KT - Kashmir Tour Packages 5 Days 4 Nights Rs 35500/-\n";
            cout<<"\t\t\t\t3. OT - Kolkata Tour Packages 11 Days 10 Nights Rs 40000/-\n";
           cout<<"\t\t\t\t4. JT - Jaipur Tour Packages 4 Days 3 Nights Rs 8500/-\n";
           cout<<"\t\t\t\t5. UT - Uttrakhand Tour Packages 5 Days 4 Nights Rs 25000/-\n\n\n";
           break;


  case 'b': strcpy(type, "International Tour Package");
            cout<<"\t\t\t\t1. ET - England Tour Packages 6 Days 7 Nights Rs 28880/-\n";
            cout<<"\t\t\t\t2. TT - Thailand Tour Packages 5 Days 4 Nights Rs 15500/-\n";
            cout<<"\t\t\t\t3. NT - New York Tour Packages 11 Days 10 Nights Rs 567800/-\n";
            cout<<"\t\t\t\t4. GT - Germany Tour Packages 5 Days 4 Nights Rs 155500/-\n";
            cout<<"\t\t\t\t5. DT -  Dubai Tour Packages 11 Days 10 Nights Rs 467800/-\n\n\n";
             break;
 }
}



void details(user *h)
{
 int n;
 n=h->numtick;
 for(int i=0;i<n;i++){
  cout<<"\t\t\t\tEnter The "<<i+1<<" Passenger Name : ";
  cin>>h->passengername[i];
  cout<<"\t\t\t\tEnter The "<<i+1<<" Passenger Age : ",
  cin>>h->passengerage[i];
  cout<<"\n";
}
WriteToFile(h);
}



void BookTicket(user* h)
{
    user *t=h;
    char place[20];
    while(h!=NULL)
    {
        if(!strcmp(h->username,currentuser))
            break;
        h=h->next;
    }
    if(h==NULL)
        return;
    if(h->price!=0.0)
    {
        printf("\t\t\t\tYou must cancel your previous ticket before buying a new one\n");
        return;
    }
    float pricelist[]={18880.00,35500.00,40000.00,8500.00,25000.00,28880.00,15500.00,567800.00,155500.00,467800.00};;
    cout<<"\n\t\t\t\tEnter place code (eg: LT,ST) ";
    cin>>place;
    float price;
    int n;
    cout<<"\n\t\t\t\tWould You Like to Confirm Booking?\n\t\t\t\t[1] - Yes\n\t\t\t\t[2] - No \n\t\t\t\t ";
    cin>>n;
    if(n!=1)
        return;
    if(n==1)
    {
     if(strcmp(place,"ST")==0)
        price=pricelist[0];
    else if(strcmp(place,"KT")==0)
        price=pricelist[1];
    else if(strcmp(place,"OT")==0)
        price=pricelist[2];
    else if(strcmp(place,"JT")==0)
        price=pricelist[3];
    else if(strcmp(place,"UT")==0)
        price=pricelist[4];
    else if(strcmp(place,"ET")==0)
        price=pricelist[5];
    else if(strcmp(place,"TT")==0)
        price=pricelist[6];
    else if(strcmp(place,"NT")==0)
        price=pricelist[7];
    else if(strcmp(place,"GT")==0)
        price=pricelist[8];
    else if(strcmp(place,"DT")==0)
        price=pricelist[9];
    else
    {
        cout<<"That tour code doesn't exist\n";
        return;
    }
    }
    int numtick;
    cout<<"\n\t\t\t\tEnter the number of tickets you want to book? : ";
    cin>>numtick;
    h->numtick=numtick;
    if(h->numtick==0)
        return;
    else{
    strcpy(h->place,place);
    h->price=price;
    details(h);
    WriteToFile(t);
    cout<<"\t\t\t\tBookings Done!!\n";
    cout<<"\t\t\t\t"<<h->numtick<<" no. of ticket is booked for "<<h->place<<" for total price of Rs - "<<(h->price)*numtick<<"\n";

}
}

void CheckTicket(user* h)
{

  while(h!=NULL)
    {
        if(!strcmp(h->username,currentuser))
            break;
        h=h->next;
    }
    if(!strcmp(h->place,"\0") || h->price==0.0 || h->numtick==0)
    {
        cout<<"\t\t\t\tYou do not have a ticket booked yet\n";
        return;
    }
    float total=0.0;
    total=(h->price)*(h->numtick);
    cout<<"\n\t\t\t\tYou have booked "<<(h->numtick)<<" tickets"<<"\n";
    for(int i=0;i<h->numtick;i++)
    {
     cout<<"\t\t\t\tPassenger "<<i+1<<" name is - "<<h->passengername[i];
     cout<<"\n";
    }
    cout<<"\t\t\t\tSum total of Rs - "<<total;
    cout<<"\n\t\t\t\tTour code - "<<h->place<<"\n\n";

}

void PrintTicket(user* h)
{
 FILE *fp;
 fp=fopen("stud.txt","w");
 //if(fgetc(fp)==EOF)
 //{
 cout<<"\n\t\t\t ************************************************";
 cout<<"\n\t\t\t ||                                            ||";
 cout<<"\n\t\t\t ||             N/V Travel Agency              ||";
 cout<<"\n\t\t\t ||                                            ||";
 cout<<"\n\t\t\t ************************************************";
 cout<<"\n\t\t\t                                                 ";
 cout<<"\n\t\t\t     No.of Tickets        : "<<h->numtick<<"                   ";
 cout<<"\n\t\t\t                                                 ";
 cout<<"\n\t\t\t     Place Code           : "<<h->place<<"                   ";
 cout<<"\n\t\t\t                                                 ";
 for(int i=0;i<h->numtick;i++){
 cout<<"\n\t\t\t     Passenger "<<i+1<<" name is  : "<<h->passengername[i];
 cout<<"\n\t\t\t                                                 ";
 cout<<"\n\t\t\t     Passenger "<<i+1<<" age is   : "<<h->passengerage[i];
 cout<<"\n\t\t\t                                                 ";}
 cout<<"\n\t\t\t     Amount Paid is       : "<<(h->price)*(h->numtick);
 cout<<"\n\t\t\t                                                 ";
 cout<<"\n\t\t\t                                                 ";
 cout<<"\n\t\t\t ************************************************\n";
 cout<<"\n\t\t\t       *****THANK YOU FOR BOOKING !! ******      ";
 cout<<"\n\t\t\t                                                 ";
 cout<<"\n\t\t\t         ====== Have A Nice Day ======           ";
 cout<<"\n\t\t\t                                                 ";
 cout<<"\n\t\t\t ************************************************\n\n";
 fclose(fp);
}

void CancelTicket(user* h)
{
 user *t=h;
    while(h!=NULL)
    {
        if(!strcmp(h->username,currentuser))
            break;
        h=h->next;
    }

    int cancel=-1;

    if(h==NULL)
        cout<<"\t\t\t\tNo such user\n";
    else{
    if(strcmp(h->place,"ST")==0)
        cancel++;
    else if(strcmp(h->place,"KT")==0)
        cancel++;
    else if(strcmp(h->place,"OT")==0)
        cancel++;
    else if(strcmp(h->place,"JT")==0)
        cancel++;
    else if(strcmp(h->place,"UT")==0)
        cancel++;
    else if(strcmp(h->place,"ET")==0)
        cancel++;
    else if(strcmp(h->place,"TT")==0)
        cancel++;
    else if(strcmp(h->place,"NT")==0)
        cancel++;
    else if(strcmp(h->place,"GT")==0)
        cancel++;
    else if(strcmp(h->place,"DT")==0)
        cancel++;
    else
    {
        printf("You haven't booked a tour yet\n");
        return;
    }
    }
    if(cancel==0)
    {
        cout<<"\n\t\t\t\tCancellation charges is 2000/-";
        cout<<"\n\t\t\t\tYour ticket has been successfully cancelled";
        cout<<"\n\tA refund of Rs "<<((h->price*h->numtick)-2000)<<" for Tour Code "<<h->place<<" for "<<h->numtick<<" tickets will soon be made to your original source of purchase\n\n\n";
        strcpy(h->place,"N/A");
        h->price=0.0;
        h->numtick=0;
        WriteToFile(t);
    }
}

void LogoutUser()
{
  if(currentstate==menu || strcmp(currentuser,"\0")==0)
    {
        printf("You must be logged in to logout\n");
        return;
    }
    strcpy(currentuser,"\0");
    currentstate=menu;
    printf("\t\t\t\tYou have been successfully logged out\n");
}




void heading()
{
    cout << "\t\t\t\<<=======================================================================>>";
    cout << "\n\t\t\t\t             Tourism Package Management System ";
    cout << "\n\t\t\t\<<=======================================================================>>";
    cout<<"\n\n\t\t\t    ******Vaccination Certificate "
           "Is Necessary For Travel Purpose******    \n\n";
}

int main()
{
    int ch;
    user *h=NULL;
    h=InitializeList(h);
    // Calling heading() function
    // Taking Choice From User
    while(1){
    if(currentstate==menu)
    {
    heading();
    cout<<"\t\t\t\t1. Register User\n";
    cout<<"\t\t\t\t2. Login User\n";
    cout<<"\t\t\t\t3. Brochure\n";
    cout<<"\t\t\t\t4. Exit\n\n\n";
    cout<<"\t\t\t\tEnter the choice ";
    cin>>ch;
    switch(ch)
    {
      case 1: h=AddUser(h);
              system("PAUSE");
              system("CLS");
              break;

      case 2: LoginUser(h);
              system("PAUSE");
              system("CLS");
              break;

      case 3: ShowBrochure();
              system("PAUSE");
              system("CLS");
              break;
      case 4: exit(0);
              cout<<"\n Thank You for visiting our page..";
              break;

    }
    }

 if(currentstate==loggedin)
    {
    system("CLS");
    heading();
    cout<<"\t\t\t\t1. Brochure\n";
    cout<<"\t\t\t\t2. Book Package\n";
    cout<<"\t\t\t\t3. Check Ticket\n";
    cout<<"\t\t\t\t4. Print Ticket\n";
    cout<<"\t\t\t\t5. Cancel Ticket\n";
    cout<<"\t\t\t\t6. Logout User\n";
    cout<<"\t\t\t\t7. Exit";
    cout<<"\n\n\t\t\t\tEnter Choice: ";
    cin>>ch;
    switch(ch) {
    // Calling inter() function
    case 1: cout<<"\n";
            ShowBrochure();
            system("PAUSE");
            system("CLS");
            break;

    case 2: BookTicket(h);
            system("PAUSE");
            system("CLS");
            break;

    case 3: CheckTicket(h);
            system("PAUSE");
            system("CLS");
            break;

    case 4: PrintTicket(h);
            system("PAUSE");
            system("CLS");
            break;

    case 5:CancelTicket(h);
           system("PAUSE");
            system("CLS");
           break;

    case 6: LogoutUser();
            system("PAUSE");
            system("CLS");
            break;

    case 7: exit(0);
              cout<<"\n\t\t\t Thank You for visiting our page..";
              break;
    default:
        cout<<"Enter Right Choice...";
        break;
    }}
    }
    return 0;
}
