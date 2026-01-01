#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<fstream.h>
#include<dos.h>
#include "user.cpp"

class pass
{
  public:
void login()
{
    clrscr();
    char username[50], password[50];
    char u[50], p[50];
    char ch;
    int i;

	clrscr();
			cout<<"                ***********************************************\n";
			cout<<"               (<------------------LOGIN PANEL--------------->)\n";
			cout<<"                ***********************************************\n";
			cout<<"\n\n\n\n\n\n\n\n";

    cout << "\t\tEnter username: ";
    cin >> username;
    //cout << "Enter password: ";
   // cin >> password;
	printf("\t\tEnter Password: ");
	i = 0;
	while (1) {
	    ch = getch();
	    if (ch == 13) // Enter key
		break;
	    if (ch == 8 && i > 0) { // Backspace
		i--;
		printf("\b \b");
	    } else if (i < sizeof(password) - 1) {
		password[i++] = ch;
		printf("*");
	    }
	}
	password[i] = '\0';

    ifstream fin("users.txt");
    int found = 0;

    while(fin >> u >> p)
    {
	if(strcmp(u, username) == 0 && strcmp(p, password) == 0)
	{
	    found = 1;
	    break;
	}
    }
    fin.close();
if(found)
{
    // demo.txt me current login save hoga (overwrite)
    ofstream demo("demo.txt");
    demo << username << " " << password;
    demo.close();

    cout << "\nLogin Successful! Welcome " << username;
    getch();
    users();
}
else
{
    cout << "\nInvalid username or password!";
    getch();
}

   
}

void createAccount()
{
    clrscr();
    char username[50], password[50];
    char u[50], p[50];

	cout<<"                ***********************************************\n";
	cout<<"               (<------------------Create PANEL--------------->)\n";
	cout<<"                ***********************************************\n";
	cout<<"\n\n\n\n\n\n\n\n";

    cout << "\n--- Create Account ---\n";
    cout << "\t\tEnter username: ";
    cin >> username;
    cout << "\t\tEnter password: ";
    cin >> password;

    // Pehle check karo username exist?
    ifstream fin("users.txt");
    int exists = 0;

    while(fin >> u >> p)
    {
	if(strcmp(u, username) == 0)
	{
	    exists = 1;
	    break;
	}
    }
    fin.close();

   if(exists)
{
    cout << "\nAccount already exists! Please login.";
    getch();
    return;
}


    //Username or password save ho raha hai
    ofstream fout("users.txt", ios::app);
    fout << username << " " << password << "\n";
    fout.close();

    cout << "\nAccount created successfully!";
}

};


void passwords()
{
    pass b1;

    while(1)
    {
	int y;
		clrscr();
	       cout<<"                ******************************************************\n";
	       cout<<"               (<-------------------USER ACCOUNT MENU--------------->)\n";
	       cout<<"                *****************************************************\n";
	       cout<<"\n\n\n\n\n\n\n\n";

	// USER ACCOUNT MENU\n";
	cout<<"\t\t1. Create Account\n";
	cout<<"\t\t2. Login Account\n";
	cout<<"\t\t3. Exit\n\n";
	cout<<"\t\t  Select an Action: ";
	cin>>y;

	if(y==3)
	    return;

	switch(y)
	{
	    case 1:
		b1.createAccount();
		break;
	    case 2:
		b1.login();
		break;
	    default:
		cout<<"INVALID VALUE";
	}

	getch();
    }
}
