#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<fstream.h>
#include<dos.h>
#include<stdio.h> // printf ke liye zaruri hai

class rtc
{
 long int Rollno,ssrno,tcno;
      char phone_no[100],Aadhaar[100];
      char name[100],Fname[100],mname[100],dob[100],address[100],email[100];
      char bg[100];
      char gender[100], category[100],section;
      int SRno,clas;
	  char username[100],password[100];
   public:
int getTCno()
{
    ifstream fin("TCnumber.txt");
    int lastTC = 100;   // starting se pehla TC 101 hoga

    if(fin)
    {
        fin >> lastTC;
        fin.close();
    }

    int newTC = lastTC + 1;

    ofstream fout("TCnumber.txt");
    fout << newTC;
    fout.close();

    return newTC;
}

   void request()
   {
     rtc s;
    int c, Roll, found=0;
    char sec;
    char line[400];
	char u[100],p[100];
	int ssrno;
	
   ifstream dfin("demo.txt");
	if(!dfin)
	{
    cout<<"Please login first!";
    getch();
    return;
	}
	dfin >> s.username >> s.password;
	strcpy(u, s.username);
	strcpy(p, s.password);

	dfin.close();

	ifstream fin("student.txt");
		if(!fin)
		{
    		cout<<"Student file not found!";
    		getch();
    		return;
		}

    clrscr();
    cout<<"\t\t----- Student Search Result -----\n\n";

    while(fin.getline(line,400))
    {
	sscanf(line,"%d|%d|%c|%ld|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]",
        &s.SRno,&s.clas,&s.section,&s.Rollno,
        s.name,s.Fname,s.mname,s.dob,s.phone_no,
        s.Aadhaar,s.gender,s.category,
        s.email,s.address,s.bg,
        s.username, s.password);

	if(strcmp(s.username,u)==0 && strcmp(s.password,p)==0)
	{
	    found=1;
		  ssrno=s.SRno;        //TCnumber         
		cout<<"\t\tSR No      : "<<s.SRno<<endl;
	    cout<<"\t\tRoll No    : "<<s.Rollno<<endl;
	    cout<<"\t\tName       : "<<s.name<<endl;
	    cout<<"\t\tFather     : "<<s.Fname<<endl;
	    cout<<"\t\tMother     : "<<s.mname<<endl;
	    cout<<"\t\tDOB        : "<<s.dob<<endl;
	    cout<<"\t\tPhone      : "<<s.phone_no<<endl;
	    cout<<"\t\tAadhaar    : "<<s.Aadhaar<<endl;
	    cout<<"\t\tGender     : "<<s.gender<<endl;
	    cout<<"\t\tCategory   : "<<s.category<<endl;
	    cout<<"\t\tEmail      : "<<s.email<<endl;
	    cout<<"\t\tAddress    : "<<s.address<<endl;
	    cout<<"\t\tBlood Group: "<<s.bg<<endl;
	    cout<<"\t----------------------------------------------------------\n";
	    break;
	}
    }
    if(!found)
	{
    cout<<"No Record Found";
    fin.close();
    getch();
    return;
	}
    fin.close();
    char l[100];
	cout << "\n\nNOTE:- Do you want to send a TC request to the Admin/Principal? (YES/NO): ";
    cin>>l;

	if(strcmp(l,"YES")==0 || strcmp(l,"yes")==0)
	{
		 addRequest(ssrno);
		 delete_studentData(ssrno);
	}

   }
 void addRequest(int x)
 {
   cout<<endl<<x;
    rtc s;
    int found=0;
   char line[400];
   char u[100],p[100];
	
   ifstream dfin("demo.txt");
	if(!dfin)
	{
    cout<<"Please login first!";
    getch();
    return;
	}
	dfin >> s.username >> s.password;
	strcpy(u, s.username);
	strcpy(p, s.password);

	dfin.close();




    s.tcno=getTCno();
       ifstream fin("student.txt");
       ofstream fout("tcrequest.txt",ios::app);

	if(!fin || !fout)
	{
	   cout<<"File error";
	   getch();
	   return;
	}
    clrscr();

    while(fin.getline(line,400))
    {
	sscanf(line,"%d|%d|%c|%ld|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]",
        &s.SRno,&s.clas,&s.section,&s.Rollno,
        s.name,s.Fname,s.mname,s.dob,s.phone_no,
        s.Aadhaar,s.gender,s.category,
        s.email,s.address,s.bg,
        s.username, s.password);

	if(strcmp(s.username,u)==0 && strcmp(s.password,p)==0)
	{
	    found=1;
	     fout <<s.tcno  <<"|"
		  << s.SRno << "|"
		  << s.clas << "|"
		  << s.section << "|"
		  << s.Rollno << "|"
		  << s.name << "|"
		  << s.Fname << "|"
		  << s.mname << "|"
		  << s.dob << "|"
		  << s.phone_no << "|"
		  << s.Aadhaar << "|"
		  << s.gender << "|"
		  << s.category << "|"
		  << s.email << "|"
		  << s.address << "|"
		  << s.bg << "|"<< s.username << "|"
     	  << s.password  << "\n";
		  break;
	   }
     }
     fin.close();
     fout.close();
     if(found)
     {
     cout<<"\n TC Request Added SuccessFully!";
     }
     else
     {
       cout<<"\n Student Not Found !";
     }
   getch();
 }
			//Student Data Delete

void delete_studentData(int x)
{
    rtc s;
    int c, Roll, found=0;
    char sec, line[400];

    clrscr();
    ifstream fin("student.txt");
    ofstream fout("temp.txt");

    while(fin.getline(line,400))
    {
	sscanf(line, "%d|%d|%c|%ld|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]",
	       &s.SRno,&s.clas,&s.section,&s.Rollno,
	       s.name,s.Fname,s.mname,s.dob,s.phone_no,
	       s.Aadhaar,s.gender,s.category,
	       s.email,s.address,s.bg);

	if(s.SRno==x)
	 found=1;
	else
	 fout<<line<<"\n";
    }
    fin.close(); fout.close();
    remove("student.txt");
    rename("temp.txt","student.txt");

    if(found) cout<<"\nStudent Record Deleted!";
    else cout<<"\nRecord Not Found!";
    getch();
}void viewTC()
{
    rtc t;
    char line[500];
    int found = 0;

    char u[100], p[100];   // login username & password

    clrscr();

    // -------- LOGIN CHECK --------
    ifstream dfin("demo.txt");
    if(!dfin)
    {
        cout<<"Please login first!";
        getch();
        return;
    }

    dfin >> u >> p;   // username | password
    dfin.close();

    // -------- TC FILE OPEN --------
    ifstream fin("tcview.txt");
    if(!fin)
    {
        cout<<"TC file not found!";
        getch();
        return;
    }

    clrscr();
    cout<<"----------- TRANSFER CERTIFICATE -----------\n\n";

    while(fin.getline(line,500))
    {
        sscanf(line,
        "%ld|%d|%d|%c|%ld|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]",
        &t.tcno,
        &t.SRno,
        &t.clas,
        &t.section,
        &t.Rollno,
        t.name,
        t.Fname,
        t.mname,
        t.dob,
        t.phone_no,
        t.Aadhaar,
        t.gender,
        t.category,
        t.email,
        t.address,
        t.bg,
        t.username
        );

        if(strcmp(t.username, u) == 0)
        {
            found = 1;

            cout<<"TC No        : "<<t.tcno<<endl;
            cout<<"SR No        : "<<t.SRno<<endl;
            cout<<"Roll No      : "<<t.Rollno<<endl;
            cout<<"Name         : "<<t.name<<endl;
            cout<<"Father Name  : "<<t.Fname<<endl;
            cout<<"Mother Name  : "<<t.mname<<endl;
            cout<<"Class        : "<<t.clas<<endl;
            cout<<"Section      : "<<t.section<<endl;
            cout<<"DOB          : "<<t.dob<<endl;
            cout<<"Phone        : "<<t.phone_no<<endl;
            cout<<"Aadhaar      : "<<t.Aadhaar<<endl;
            cout<<"Gender       : "<<t.gender<<endl;
            cout<<"Category     : "<<t.category<<endl;
            cout<<"Email        : "<<t.email<<endl;
            cout<<"Address      : "<<t.address<<endl;
            cout<<"Blood Group  : "<<t.bg<<endl;

            cout<<"\n-------------------------------------------\n";
            break;
        }
    }

    if(!found)
        cout<<"No TC Record Found!";

    fin.close();
    getch();
}

};
void usertc()
{
	rtc k;
	while(1)
	{
	    int h;
	    clrscr();
cout<<"\t===============================================================\n";
cout<<"\t           TRANSFER CERTIFICATE MANAGEMENT\n";
cout<<"\t===============================================================\n\n\n\n";

	    cout<<"\t\t1. Request TC\n";
	    cout<<"\t\t2. View TC\n";
	    cout<<"\t\t3. Back\n\n";
	    cout<<"\t\t  Select an Action:- ";
	    cin>>h;
			  if(h==3)
			      return;
			  switch(h)
			 {
			     case 1:
			     k.request();
			     break;
			     case 2:
			     k.viewTC();
			     break;
			     default:
			     cout<<"INVALID VALUE";
			     break;
			 }


	}

getch();
}