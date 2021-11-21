#include<iostream>
#include<fstream>
#include<math.h>
#include<string>
#include"Function.h"
using namespace std;
void file_read(string filename,double arraylist[])
{
    ifstream readfile;
    double XYZ[3];
    int i=0;
    readfile.open(filename);
    if(readfile.fail())
    {
        cout<<"File open error"<<endl;
    }
    string str;
    while(getline(readfile,str))
    {
        string_split(str,",",XYZ);
        for(int j=0;j<3;j++)
        {
            arraylist[i*3+j]=XYZ[j];
        }
        i++;
    }
}

void string_split(std::string str,const char* sign,double XYZ[])
{
    int len,i,j;
    len=str.length();
    string Xstr,Ystr,Zstr="";
    j=0;
    for(i=0;i<len;i++)
    {
        if(j==1&&str[i]!=*sign)
        {
            Xstr+=str[i];
        }
        else if (j==2&&str[i]!=*sign)
        {
            Ystr+=str[i];
        }
        else if (j==3&&str[i]!=*sign)
        {
            Zstr+=str[i];
        }
        
        if(str[i]==*sign)
        {
            j++;
        }
    }
    XYZ[0]=atof(Xstr.c_str());
    XYZ[1]=atof(Ystr.c_str());
    XYZ[2]=atof(Zstr.c_str());
}