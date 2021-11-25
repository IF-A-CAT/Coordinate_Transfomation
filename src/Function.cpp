#include<iostream>
#include<fstream>
#include<math.h>
#include<string>
#include"matrix.h"
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

matrix get_B_matrix(matrix A,matrix X0,double K,matrix *B1)//for ThirteenArguments
{
    matrix B(X0.line,13);
    double a,b,c;
    double Barray[(X0.line)*13];
    for(int i=0;i<X0.line*13;i++)
    {
        Barray[i]=0;
    }
    for(int j=0;j<X0.line/3;j++)
    {
    for(int i=0;i<39;i++)
    {
        Barray[i+j*39]=0;
    }
    Barray[0+j*39]=Barray[14+j*39]=Barray[28+j*39]=1;
    Barray[3+j*39]=A.elems[0]*X0.elems[0+3*j]+A.elems[1]*X0.elems[1+j*3]+A.elems[2]*X0.elems[2+j*3];
    Barray[16+j*39]=A.elems[3]*X0.elems[0+j*3]+A.elems[4]*X0.elems[1+j*3]+A.elems[5]*X0.elems[2+j*3];
    Barray[29+j*39]=A.elems[6]*X0.elems[0+j*3]+A.elems[7]*X0.elems[1+j*3]+A.elems[8]*X0.elems[2+j*3];
    Barray[4+j*39]=Barray[20+j*39]=Barray[36+j*39]=K*X0.elems[0+3*j];
    Barray[5+j*39]=Barray[21+j*39]=Barray[37+j*39]=K*X0.elems[1+3*j];
    Barray[6+j*39]=Barray[22+j*39]=Barray[38+j*39]=K*X0.elems[2+3*j];
    }
    for(int i=0;i<X0.line/3;i++)
    {
        a=K*X0.elems[i*3];
        b=K*X0.elems[i*3+1];
        c=K*X0.elems[i*3+2];
        for(int j=0;j<36;j++)
        {
            B1->elems[0+36*i]=B1->elems[13+36*i]=B1->elems[36*i+26]=1;
            B1->elems[3+36*i]=B1->elems[18+36*i]=B1->elems[33+36*i]=a;
            B1->elems[4+36*i]=B1->elems[19+36*i]=B1->elems[34+36*i]=b;
            B1->elems[5+36*i]=B1->elems[20+36*i]=B1->elems[35+36*i]=c;

        }
    }
    B.setelems_by_array(Barray);
    return B;
}

matrix get_C_matrix(matrix A)
{
    matrix C(6,13);
    for(int i=0;i<3;i++)
    {
        C.elems[4+16*i]=2*A.elems[3*i];
        C.elems[5+16*i]=2*A.elems[3*i+1];
        C.elems[6+16*i]=2*A.elems[3*i+2];
    }
    C.elems[43]=A.elems[3];
    C.elems[44]=A.elems[0];
    C.elems[46]=A.elems[4];
    C.elems[47]=A.elems[3];
    C.elems[49]=A.elems[7];
    C.elems[50]=A.elems[6];
    C.elems[56]=A.elems[2];
    C.elems[58]=A.elems[0];
    C.elems[59]=A.elems[5];
    C.elems[61]=A.elems[3];
    C.elems[62]=A.elems[8];
    C.elems[64]=A.elems[6];
    C.elems[70]=A.elems[2];
    C.elems[71]=A.elems[1];
    C.elems[73]=A.elems[5];
    C.elems[74]=A.elems[4];
    C.elems[76]=A.elems[8];
    C.elems[77]=A.elems[7];
    return C;
}

void XYZ2BLH(double XYZ[],double BLH[])
{
    double a=6378137;
    double b=6356752.3142451795;
    double e=sqrt(a*a-b*b)/a;
    double TanB=0,B,L,H,Btemp=1;
    while(abs(Btemp-TanB)>1e-6)
    {
        Btemp=TanB;
        TanB=(1/sqrt(XYZ[0]*XYZ[0]+XYZ[1]*XYZ[1]))*(XYZ[2]+(a*e*e*TanB)/sqrt(1+TanB*TanB-e*e*TanB*TanB));
    }
    L=atan(XYZ[1]/XYZ[0]);
    B=atan(TanB);
    H=sqrt(XYZ[0]*XYZ[0]+XYZ[1]*XYZ[1])/cos(B)-a/sqrt(1-e*e*sin(B)*sin(B));
    BLH[0]=B;
    BLH[1]=L;
    BLH[2]=H;

}