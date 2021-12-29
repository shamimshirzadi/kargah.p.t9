#include<iostream> 
#include<conio.h>
#include<fstream>
#include<iomanip>
#include<cstdio>
#include<windows.h>
#include<cstring>
#include<cstdlib>

using namespace std;

int k=7,r=0,flag=0;
COORD coord = {0, 0};

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct date
{
    int mm,dd,yy;
};

ifstream fin;
ofstream fout;

class item
{
    int itemno;
    char name[25];
    date d;

public:
    void add()
    {
        cout<<"code cala : ";
        cin>>itemno;
        cout<<"name cala : ";
        cin>>name;

    }
    
    void show()
    {
        cout<<"\n\ code cala: ";
        cout<<itemno;
        cout<<"\n\n\ name cala : ";
        cout<<name;
    }
    
    void report()
    {
        gotoxy(3,k);
        cout<<itemno;
        gotoxy(13,k);
        puts(name);
    }
    
    int retno()
    {
        return(itemno);

    }

};

class amount: public item
{
    float netamt, gross, qty, price, dis;

public:
    void report();
    void add();
    void pay();
    void show();
    void calculate();
    float retnetamt()
    {
        return(netamt);
    }
} amt;


void amount::add()
{
    item::add();
    cout<<"\n\n\ mablagh : ";
    cin>>price;
    cout<<"\n\n\ meghdar : ";
    cin>>qty;
    cout<<"\n\n\ takhfif : ";
    cin>>dis;
    calculate();
    fout.write((char *)&amt,sizeof(amt));
    fout.close();
}

void amount::calculate()
{
    netamt=qty*(gross-(gross*(dis/100)));
}

void amount::show()
{
    fin.open("itemstore.dat",ios::binary);
    fin.read((char*)&amt,sizeof(amt));
    item::show();
    cout<<"\n\n\t meghdare khales : ";
    cout<<netamt;
    fin.close();
}

void amount::report()
{
    item::report();
    gotoxy(23,k);
    cout<<price;
    gotoxy(33,k);
    cout<<qty;
    gotoxy(52,k);
    cout<<dis;
    gotoxy(64,k);
    cout<<netamt;
    k=k+1;
    if(k==50)
    {
        gotoxy(25,50);
        cout<<"baraye edame klidi ra bezanin ";
        getch();
        k=7;
        system("cls");
        gotoxy(30,3);
        cout<<" moshakhasat cala  ";
        gotoxy(3,5);
        cout<<"number";
        gotoxy(13,5);
        cout<<"name cala ";
        gotoxy(23,5);
        cout<<"mablagh cala ";
        gotoxy(33,5);
        cout<<"meghdar";
        gotoxy(52,5);
        cout<<"kasr";
        gotoxy(64,5);
        cout<<"meghdare khales";
    }
}

void amount::pay()
{
    show();
    cout<<"\n\n\n\t\t*********************************************";
    cout<<"\n\t\t               moshakhasat                  ";
    cout<<"\n\t\t*********************************************";
    cout<<"\n\n\t\ mablagh                     :"<<price;
    cout<<"\n\n\t\ meghdar                  :"<<qty;
    cout<<"\n\t\ takhfif        :"<<dis;
    cout<<"\n\n\n\t\t meghdar khales             :Rs."<<netamt;
    cout<<"\n\t\t*********************************************";
}




int main()
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout<<setprecision(2);
    fstream tmp("temp.dat",ios::binary|ios::out);
menu:
    system("cls");
    gotoxy(25,2);
    cout<<"factore foroshgah ";
    gotoxy(25,3);
    cout<<"===========================\n\n";
    cout<<"\n\t\t1.faktor\n\n";
    cout<<"\t\t2. afzodan ya cancelli cala \n\n";
    cout<<"\t\t3. moshakhasat cala \n\n";
    cout<<"\t\t4.kharej shodan\n\n";
    cout<<"\t\ sabt item morede nazar : ";
    int ch,ff;
    float gtotal;
    cin>>ch;
    switch(ch)
    {
    case 1:
ss:
        system("cls");
        gotoxy(25,2);
        cout<<"moshakhasat factor";
        gotoxy(25,3);
        cout<<"================\n\n";
        cout<<"\n\t\t1.tamami item ha\n\n";
        cout<<"\t\t2.bazgasht be meno \n\n";
        cout<<"\t\t: sabt item morede nazareton : ";
        int cho;
        cin>>cho;
        if(cho==1)
        {
            system("cls");
            gotoxy(30,3);
            cout<<" faktor ";
            gotoxy(3,5);
            cout<<" code cala ";
            gotoxy(13,5);
            cout<<"name cala";
            gotoxy(23,5);
            cout<<"mablagh";
            gotoxy(33,5);
            cout<<"meghdar";
            gotoxy(52,5);
            cout<<"takhfif";
            gotoxy(64,5);
            cout<<"meghdare khales";
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\n item yaft nashod ";
                goto menu;
            }
            fin.seekg(0);
            gtotal=0;
            
            while(!fin.eof())
            {
                fin.read((char*)&amt,sizeof(amt));
                if(!fin.eof())
                {
                    amt.report();
                    gtotal+=amt.retnetamt();
                    ff=0;
                }
                if(ff!=0) gtotal=0;
            }
            gotoxy(17,k);
            cout<<"\n\n\n\t\t\ majmoe hazine "<<gtotal;
            getch();
            fin.close();
        }
        if(cho==2)
        {
            goto menu;
        }
        goto ss;
    case 2:
db:
        system("cls");
        gotoxy(25,2);
        cout<<"eslahe factore";
        gotoxy(25,3);
        cout<<"=================\n\n";
        cout<<"\n\t\t1. moshakhasat cala ezafe shavad\n\n";
        cout<<"\t\t2.virayeshe moshakhasat cala \n\n";
        cout<<"\t\t3.moshakhasat cala delete \n\n";
        cout<<"\t\t4.bazgasht be meno  ";
        int apc;
        cin>>apc;
        switch(apc)
        {
        case 1:
            fout.open("itemstore.dat",ios::binary|ios::app);
            amt.add();
            cout<<"\n\t\ cala added ";
            getch();
            goto db;

        case 2:
            int ino;
            flag=0;
            cout<<"\n\n\ code cala ra baraye edit bezanid :";
            cin>>ino;
            fin.open("itemstore.dat",ios::binary);
            fout.open("itemstore.dat",ios::binary|ios::app);
            if(!fin)
            {
                cout<<"\n\n yaft nashod";
                goto menu;
            }
            fin.seekg(0);
            r=0;
            while(!fin.eof())
            {
                fin.read((char*)&amt,sizeof(amt));
                if(!fin.eof())
                {
                    int x=amt.item::retno();
                    if(x==ino)
                    {
                        flag=1;
                        fout.seekp(r*sizeof(amt));
                        system("cls");
                        cout<<"\n\t\ moshakhasat mojodi \n";
                        amt.show();
                        cout<<"\n\n\t\ new moshakhasat \n";
                        amt.add();
                        cout<<"\n\t\ apdate ";
                    }
                }
                r++;
            }
            if(flag==0)
            {
                cout<<"\n\t\ cala tamam shode lotfan calaye digari entekhab konin";
                getch();
                goto db;
            }
            fin.close();
            getch();
            goto db;

        case 3:
            flag=0;
            cout<<"\n\n\ code calaye cancelli ra bezanid ";
            cin>>ino;
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\n yaft nashod ";
                goto menu;
            }
            fin.seekg(0);
            while(fin.read((char*)&amt, sizeof(amt)))
            {
                int x=amt.item::retno();
                if(x!=ino)
                    tmp.write((char*)&amt,sizeof(amt));
                else
                {
                    flag=1;
                }
            }
            fin.close();
            tmp.close();
            fout.open("itemstore.dat",ios::trunc|ios::binary);
            fout.seekp(0);
            tmp.open("temp.dat",ios::binary|ios::in);
            if(!tmp)
            {
                cout<<"khata!";
                goto db;
            }
            while(tmp.read((char*)&amt,sizeof(amt)))
                fout.write((char*)&amt,sizeof(amt));
            tmp.close();
            fout.close();
            if(flag==1)
                cout<<"\n\t\ cala deleted";
            else if (flag==0)
                cout<<"\n\t\ cala tamam shode dobare entekhab konid";
            getch();
            goto db;
        case 4:
            goto menu;
        default:
            cout<<"\n\n\t\ mojadad test ";
            getch();
            goto db;
        }
    case 3:
        system("cls");
        flag=0;
        int ino;
        cout<<"\n\n\t\ code cala ra bezanid :";
        cin>>ino;
        fin.open("itemstore.dat",ios::binary);
        if(!fin)
        {
            cout<<"\n\n yaft nashod...\ nProgram Terminated!";
            goto menu;
        }
        fin.seekg(0);
        while(fin.read((char*)&amt,sizeof(amt)))
        {
            int x=amt.item::retno();
            if(x==ino)
            {
                amt.pay();
                flag=1;
                break;
            }
        }
        if(flag==0)
            cout<<"\n\t\ cala tamam shode dobare entekhab konid ";
        getch();
        fin.close();
        goto menu;
    case 4:
        system("cls");
        gotoxy(20,20);
        cout<<"exit?";
        char yn;
        cin>>yn;
        if((yn=='Y')||(yn=='y'))
        {
            gotoxy(12,20);
            system("cls");
            cout<<"sepas";
            getch();
            exit(0);
        }
        else if((yn=='N')||(yn=='n'))
            goto menu;
        
        else
        {
            goto menu;
        }
    default:
        cout<<"\n\n\t\ test mojadad ";
        getch();
        goto menu;
    }
    return 0;
}
