#include <iostream>
#include<windows.h>
#include<string.h>
#include<mysql.h>
#include<sstream>
#include<stdlib.h>
using namespace std;

const char* hostname = "localhost";
const char* username = "root";
const char* password = "";
const char* database = "test1";
unsigned int port    = 3306;
const char* unixsocket =NULL;
unsigned long clientflag = 0 ;

//database connection

MYSQL* connectdatabase()
{
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, hostname, username, password, database, port,unixsocket, clientflag);
    if(conn)
    {
        cout<<"Connected successfully...\n"<<endl;
        return conn;
    }
    else
    {
        cout<<"Failed to connect to database"<<endl;
        return conn;
    }
}

insertion(MYSQL* conn)
{
    int ins1 = 0, ins2 = 0, ins3 = 0, ins4 = 0, d;
    stringstream ss1,ss2,ss3,ss4;
    string aadhar,name,add,dob,age,phone,diabetes,allergies,r_infec,covid,pid,vname,vid,dosage,bno,amt;
    cout<<"Enter the aadhar card number                        : ";
    cin>>aadhar;
    cout<<"Enter the name                                      : ";
    cin>>name;
    cout<<"Enter the address                                   : ";
    cin>>add;
    cout<<"Enter the DOB                                       : ";
    cin>>dob;
    cout<<"Enter the age                                       : ";
    cin>>age;
    cout<<"Enter the phone number                              : ";
    cin>>phone;
    cout<<"Enter YES or NO for Diabetes                        : ";
    cin>>diabetes;
    cout<<"Enter YES or NO for Allergies                       : ";
    cin>>allergies;
    cout<<"Enter YES or NO for Respiratory infections          : ";
    cin>>r_infec;
    cout<<"Enter YES or NO if Patient was infected by COVID-19 : ";
    cin>>covid;
    cout<<"Enter the Patient ID                                : ";
    cin>>pid;
    cout<<"Enter the Vaccination Name                          : ";
    cin>>vname;
    if(vname=="Covishield"){
        vid="1";
    }
    if(vname=="Covaxine"){
        vid="2";
    }
    if(vname=="SputnikV"){
        vid="3";
    }
    cout<<"Enter 0 for first dosage , 1 for second dosage and 2 for completion of 2 doses : ";
    cin>>d;

    while(!(d>=0 && d<=2)){
        cout<<"INVALID NUMBER !...Enter again \n";
        cin>>d;
    }
    cout<<"Enter the Bill No                                   : ";
    cin>>bno;
    cout<<"Enter the Amount                                    : ";
    cin>>amt;
    if(d==0){
        dosage = "Appearing for first dose";
    }
    if(d==1){
        dosage = "Completion of first dose";
    }
    if(d==2){
        dosage = "Completion of both the doses";
    }
    ss1<<"INSERT INTO Patient VALUES ('"+aadhar+"','"+name+"','"+add+"','"+dob+"','"+age+"','"+phone+"')";
    string query1 = ss1.str();
    const char* q1 = query1.c_str();
    ins1 = mysql_query(conn,q1);
    ss2<<"INSERT INTO Medical_history VALUES ('"+aadhar+"','"+diabetes+"','"+allergies+"','"+r_infec+"','"+covid+"')";
    string query2 = ss2.str();
    const char* q2 = query2.c_str();
    ins2 = mysql_query(conn,q2);
    ss3<<"INSERT INTO Vaccination_Lab VALUES ('"+aadhar+"','"+pid+"','"+vname+"','"+vid+"','"+dosage+"')";
    string query3 = ss3.str();
    const char* q3 = query3.c_str();
    ins3 = mysql_query(conn,q3);
    ss4<<"INSERT INTO Vaccination_dept VALUES ('"+pid+"','"+amt+"','"+bno+"')";
    string query4 = ss4.str();
    const char* q4 = query4.c_str();
    ins4 = mysql_query(conn,q4);
    if(ins1 == 0 && ins2 == 0 && ins3 == 0 && ins4 == 0)
    {
        cout<<"\nRecord inserted successfully.....!!!!\n"<<endl;
    }
    else
    {
        cout<<"Failed to insert........\n"<<endl;
    }
}

display(MYSQL* conn)
{
    int c = 1;
    MYSQL_ROW row,row1;
    MYSQL_RES* res;
    if(conn)
    {
        int qstate = mysql_query(conn,"SELECT * FROM Patient, Medical_History WHERE Patient.Aadhar_card = Medical_history.M_Aadhar");
        if(!qstate)
        {
            res = mysql_store_result(conn);
            int count = mysql_num_fields(res);
            cout<<"PERSONAL AND MEDICAL HISTORY OF PATIENTS\n"<<endl;
            while(row=mysql_fetch_row(res))
            {
                cout<<"PERSONAL AND MEDICAL DETAILS OF PATIENT "<<c<<"\n"<<endl;

                    cout<<"Name                    : "<<row[1]<<"\n";
                    cout<<"Address                 : "<<row[2]<<"\n";
                    cout<<"DOB                     : "<<row[3]<<"\n";
                    cout<<"Age                     : "<<row[4]<<"\n";
                    cout<<"Phone number            : "<<row[5]<<"\n";
                    cout<<"Diabetes                : "<<row[7]<<"\n";
                    cout<<"Allergies               : "<<row[8]<<"\n";
                    cout<<"Respiratory Infections  : "<<row[9]<<"\n";
                    cout<<"Covid-19                : "<<row[10]<<endl<<endl;
                c++;
                cout<<endl;
            }
        }
        cout<<endl;
    }
    else
    {
        cout<<"\nFailed to fetch data.....\n"<<endl;
    }
}
display1(MYSQL* conn)
{
    int c = 1;
    MYSQL_ROW row;
    MYSQL_RES* res;
    if(conn)
    {
        int qstate = mysql_query(conn,"SELECT * FROM Vaccination_lab,Vaccination_dept WHERE Vaccination_lab.Patient_ID = Vaccination_dept.VPatient_ID");
        if(!qstate)
        {
            res = mysql_store_result(conn);
            int count = mysql_num_fields(res);
            cout<<"VACCINATION DETAILS OF PATIENTS\n"<<endl;
            while(row=mysql_fetch_row(res))
            {
                cout<<"VACCINATION DETAILS OF PATIENT "<<c<<"\n"<<endl;

                    cout<<"Aadhar Number             : "<<row[0]<<"\n";
                    cout<<"Patient ID                : "<<row[1]<<"\n";
                    cout<<"Vaccine Name              : "<<row[2]<<"\n";
                    cout<<"Vaccine ID                : "<<row[3]<<"\n";
                    cout<<"Dosage                    : "<<row[4]<<"\n";
                    cout<<"Bill Number               : "<<row[7]<<"\n";
                    cout<<"Amount                    : "<<row[6]<<endl<<endl;
                    c++;
            }
            cout<<endl;
        }
        cout<<endl;
    }
    else
    {
        cout<<"\nFailed to fetch data.....\n"<<endl;
    }
}
display2(MYSQL* conn)
{
    string a;
    int not_found=0,tot=0,not_found1=0,tot1=0;
    cout<<"Enter the aadhar number for details to be searched : ";
    cin>>a;
    MYSQL_ROW row;
    MYSQL_RES* res;
    if(conn)
    {
        int qstate = mysql_query(conn,"SELECT * FROM Patient INNER JOIN Medical_history ON Patient.Aadhar_card=Medical_history.M_Aadhar");
        if(!qstate)
        {
            res = mysql_store_result(conn);
            int count = mysql_num_fields(res);
            while(row=mysql_fetch_row(res))
            {
                    if(row[0]==a)
                    {
                        cout<<"\n\nDETAILS OF PATIENT WHOSE AADHAR CARD NUMBER IS "<<a<<" :\n"<<endl;
                        cout<<"Aadhar Card            : "<<row[0]<<endl;
                        cout<<"Name                   : "<<row[1]<<endl;
                        cout<<"Address                : "<<row[2]<<endl;
                        cout<<"DOB                    : "<<row[3]<<endl;
                        cout<<"Age                    : "<<row[4]<<endl;
                        cout<<"Phone number           : "<<row[5]<<endl;
                        cout<<"Diabetes               : "<<row[7]<<endl;
                        cout<<"Allergies              : "<<row[8]<<endl;
                        cout<<"Respiratory Infections : "<<row[9]<<endl;
                        cout<<"Covid-19               : "<<row[10]<<endl;
                        int p = 1;
                        not_found=0;
                        tot++;
                        if(p=1)
                            break;
                    }
                    else
                    {
                        not_found++;
                    }
                    tot++;
            }
        }
        int qstate1 = mysql_query(conn,"SELECT * FROM Vaccination_Lab INNER JOIN Vaccination_dept ON Vaccination_lab.Patient_ID=Vaccination_dept.VPatient_ID");
        if(!qstate1)
        {
            res = mysql_store_result(conn);
            int count = mysql_num_fields(res);
            while(row=mysql_fetch_row(res))
            {
                    if(row[0]==a)
                    {
                        cout<<"Patient ID             : "<<row[1]<<"\n";
                        cout<<"Vaccination Name       : "<<row[2]<<"\n";
                        cout<<"Vaccination ID         : "<<row[3]<<"\n";
                        cout<<"Dosage                 : "<<row[4]<<"\n";
                        cout<<"Amount                 : "<<row[6]<<"\n";
                        cout<<"Bill Number            : "<<row[7]<<"\n"<<endl<<endl;
                        int p = 1;
                        not_found=0;
                        tot1++;
                        if(p=1)
                            break;
                    }
                    else
                    {
                        not_found1++;
                    }
                    tot1++;
            }
        }
        if(not_found==tot && not_found1==tot1)
        {
            cout<<"\nNo record found .....\n"<<endl;
        }
    }
}

deletion(MYSQL* conn)
{
    MYSQL_ROW row;
    MYSQL_RES* res;
    string username;
    char* name;
    stringstream ss,sss,s1;
    cout<<"Enter the Aadhar card of record which has to be deleted : ";
    cin>>username;
    sss<<"SELECT * FROM Patient WHERE Aadhar_card = ' "+username+" ' ";
    cout<<endl;
    s1<<"SELECT Name FROM Patient WHERE Aadhar_card = ' "+username+" ' ";
    string query1 = s1.str();
    const char* q1 = query1.c_str();
    mysql_query(conn,q1);
    res = mysql_store_result(conn);
    while(row=mysql_fetch_row(res))
    {
        name = row[0];
    }
    string query = sss.str();
    const char* q = query.c_str();
    mysql_query(conn,q);
    res = mysql_store_result(conn);
    int count = mysql_num_fields(res);
    my_ulonglong x = mysql_num_rows(res);
    if(x>0)
    {
        ss<<"DELETE FROM Patient WHERE Aadhar_card = ' "+username+" ' ";
        string query = ss.str();
        const char* q = query.c_str();
        mysql_query(conn,q);
        cout<<x<<" Record of Patient "<<name<<" having Aadhar no. as "<<username<<" is found!"<<endl<<"Record found and deleted!....\n"<<endl;
    }
    else
    {
        cout<<"\nNO RECORD FOUND !!\n"<<endl;
    }
}

int main()
{
    MYSQL* conn = connectdatabase();
    int choice,n;
    cout<<endl;
    cout<<"Enter 1 for inserting new record \nEnter 2 for displaying all Patient's Medical Records \n";
    cout<<"Enter 3 for displaying all Patient's Vaccination details \n";
    cout<<"Enter 4 for displaying a particular Patient's Record\nEnter 5 for Deletion of a Particular Record\n"<<endl;
    cout<<"Enter the no. of times the operations has to be performed : ";
    cin>>n;
    cout<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"-------------------------------------------------------------\n";
        cout<<"Enter you choice : ";
        cin>>choice;
        cout<<endl;
        if(choice==1)
        {
            insertion(conn);
        }
        if(choice==2)
        {
            display(conn);
        }
        if(choice==3)
        {
            display1(conn);
        }
        if(choice==4)
        {
            display2(conn);
        }
        if(choice==5)
        {
            deletion(conn);
        }
    }
    return 0;
}
