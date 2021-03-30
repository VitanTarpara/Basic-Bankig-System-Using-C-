#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<fstream>
#include<iomanip>
using namespace std;

void write_account();
void deposite(int);
void withdraw(int);
void display_all();
void srch(int);

class bank
{
     private:

     int acno,account,deposit;
     float balance;
     char name[20];

     public:

     void creat(void);
     void dep(int);
     void wid(int);
     void srch(int);
     void display()const;
     int retacno() const;
     int retdeposit() const;
     void srh();
};

    void bank::creat(void)

     {

         cout<<"\nENTER YOUR NAME :  ";
         cin>>name;
         cout<<"\nENTER YOUR ACCOUNT NUMBER(ONLY FOUR DIGIT):  ";
         cin>>acno;
         cout<<"\nENTER THE AMOUNT OF MONEY :  ";
         cin>>balance;

     }

    void bank::dep(int j)

     {
          balance+=j;
     }

    void bank::wid(int k)

     {
       balance-=k;
     }


    void bank::display()const

     {
        cout<<acno<<setw(15)<<name<<setw(15)<<balance<<endl;
     }

     int bank::retacno() const

     {
 	  return acno;
     }

     int bank::retdeposit() const

     {
	  return deposit;
     }


    void bank::srh()

     {
         cout<<"------------------------------------------------------";
         cout<<"\n\t\tAccount Holder's INFO";
         cout<<"\n------------------------------------------------------";
         cout<<"\n\n\t\tNAME : "<<name<<"\n\n\t\tACCOUNT NO. "<<acno<<"\n\n\t\tBALANCE : "<<balance<<"\n\n";
         cout<<"\n------------------------------------------------------\n\n";

      }


int main()
{
        int num;
        bank b;
        int index;

        cout<<"Project prepared by: Vitan Tarpara\n\t\t "<<endl;

        for(int i=0;i<120;i++)
        {
        cout<<"-";
        }

        cout<<"\n\t\t\t\t\t\t--------------------------";
        cout<<"\n\t\t\t\t\t\tBANKING MANAGEMENT SYSTEM";
        cout<<"\n\t\t\t\t\t\t--------------------------\n";

        for(int i=0;i<120;i++)
        {
        cout<<"-";
        }
        cout<<"\n\n   ***** HELLO, WELCOME TO THE BANK!!! *****\n";

        do
        {
            cout<<"\n\nPRESS 1 TO OPEN ACCOUNT\n\n"<<"PRESS 2 TO DEPOSITE AMOUNT\n\n"<<"PRESS 3 TO WITHDRAW MONEY \n\n"<<"PRESS 4 ALL ACCOUNT HOLDER LIST \n\n"<<"PRESS 5 TO SEARCH \n\n"<<"PRESS 6 TO EXIT \n\n\t\n";
            cout<<"Your option......";

            cin>>index;

            switch(index)
            {
                case 1:

                 write_account();
                 break;

                case 2:

                 cout<<"\nENTER YOUR ACCOUNT NUMBER(ONLY FOUR DIGIT):  ";
                 cin>>num;
                 deposite(num);
                 break;

                case 3:

                 cout<<"\nENTER YOUR ACCOUNT NUMBER(ONLY FOUR DIGIT):  ";
                 cin>>num;
                 withdraw(num);
                 break;

                case 4:

                 display_all();
                 break;

                case 5:

                 cout<<"\nENTER YOUR ACCOUNT NUMBER(ONLY FOUR DIGIT):  ";
                 cin>>num;
                 srch(num);
                 break;

                case 6:
                break;

               default:cout<<"\nYOU HAVE PRESSED THE WRONG KEY. PLEASE TRY AGAIN. \n\n\n";
               break;
            }
         }     while(index!=6);
}

    void write_account()
    {
        bank ac;
        ofstream outFile;
        outFile.open("acc.txt",ios::binary|ios::app);
        ac.creat();
        outFile.write((char *) (&ac), sizeof(bank));
        outFile.close();
    }

    void deposite(int n)
    {
        bank dp;
        int j;

        fstream outFile;
        outFile.open("acc.txt",ios::binary|ios::in|ios::out);

        if(!outFile)
            {
                cout<<"File could not be open !! Press any Key...";
                return;
            }

        while(!outFile.eof())
            {
                outFile.read((char *) (&dp), sizeof(bank));

                if(dp.retacno()==n)
                {
                    cout<<"\n\t-------------------------";
                    cout<<"\n\t  TO DEPOSITE AMOUNT \n";
                    cout<<"\t-------------------------";
                    cout<<"\n\nEnter The amount to be deposited : ";
                    cin>>j;
                    dp.dep(j);

                    int pos=(-1)*static_cast<int>(sizeof(dp));
                    outFile.seekp(pos,ios::cur);
                    outFile.write((char *) (&dp), sizeof(bank));
                    cout<<"\t-------------------------";
                    cout<<"\n\t  Record Updated \n";
                    cout<<"\t-------------------------";
                }
            }
        outFile.close();
    }


    void withdraw(int n)
    {
        bank wd;
        int y;

        fstream outFile;
        outFile.open("acc.txt",ios::binary|ios::in|ios::out);

        if(!outFile)
            {
                cout<<"File could not be open !! Press any Key...";
                return;
            }

        while(!outFile.eof())
            {
                outFile.read((char *) (&wd), sizeof(bank));

                if(wd.retacno()==n)
                {
                    cout<<"\n\t-------------------------";
                    cout<<"\n\t  TO  WITHDRAW AMOUNT \n";
                    cout<<"\t-------------------------";
                    cout<<"\n\nEnter The amount to be WITHDRAW : ";
                    cin>>y;
                    int bal=wd.retdeposit()-y;
                    wd.wid(y);

                    int pos=(-1)*static_cast<int>(sizeof(wd));
                    outFile.seekp(pos,ios::cur);
                    outFile.write((char *) (&wd), sizeof(bank));
                    cout<<"\t-------------------------";
                    cout<<"\n\t  Record Updated \n";
                    cout<<"\t-------------------------";
                }
            }
        outFile.close();
    }

    void display_all()
    {
        bank ba;

        ifstream inFile;
        inFile.open("acc.txt",ios::binary);

        if(!inFile)
            {
            cout<<"File could not be open !! Press any Key...";
            return;
            }
            cout<<"\t   _____________________________";
            cout<<"\n\n\t\tACCOUNT HOLDER LIST\n";
            cout<<"\t   _____________________________\n\n";
            cout<<"----------------------------------------------------\n";
            cout<<"A/c no.       NAME            Balance\n";
            cout<<"----------------------------------------------------\n";

            while(inFile.read((char *) (&ba), sizeof(bank)))
            {
            ba.display();
            }
            cout<<"----------------------------------------------------\n";
	inFile.close();
}

void srch(int n)
{
    bank sr;

    fstream outfile;
    outfile.open("acc.txt");

    if(!outfile)
            {
                cout<<"File could not be open !! Press any Key...";
                return;
            }

        while(!outfile.eof())
            {
                outfile.read((char *) (&sr), sizeof(bank));

                if(sr.retacno()==n)
                {
                    sr.srh();
                }

            }
            outfile.close();
}
