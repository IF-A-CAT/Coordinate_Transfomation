#include"Function.h"
#include<iostream>
#include<string>
#include<math.h>
#include"matrix.h"
using namespace std;
int main()
{
    double arrayorg[18],arraychg[18];//number of arguments
    string stro,strc;
    double Z00,Y00,X00;
    stro="XYZ_origin_2.xyz";
    strc="XYZ_target_2.xyz";
    file_read(stro,arrayorg);
    file_read(strc,arraychg);
    matrix L(18,1);
    matrix L0(18,1);
    matrix B(18,7);
    matrix Btran(7,18);
    matrix NBB(7,7);
    matrix l(18,1);
    matrix NBBinv(7,7);
    matrix W(7,1);
    matrix x(7,1);
    matrix X0(7,1);
    matrix X(7,1);
    L.setelems_by_array(arraychg);
    double Barray[126];
    double sumelems=1;
    double X0ori[7]={0,0,0,0,0,0,1};
    X0.setelems_by_array(X0ori);
    for(int i=0;i<6;i++)
    {
        X00=arrayorg[3*i];
        Y00=arrayorg[3*i+1];
        Z00=arrayorg[3*i+2];
        Barray[21*i+1]=Barray[21*i+2]=Barray[21*i+3]=Barray[21*i+7]=Barray[21*i+9]=
        Barray[21*i+11]=Barray[21*i+14]=Barray[21*i+15]=Barray[21*i+19]=0;
        Barray[21*i]=Barray[21*i+8]=Barray[21*i+16]=1;
        Barray[21*i+18]=Barray[21*i+6]=X00;
        Barray[21*i+5]=Barray[21*i+13]=Y00;
        Barray[21*i+10]=Barray[21*i+20]=Z00;
        Barray[21*i+4]=-Z00;
        Barray[21*i+12]=-X00;
        Barray[21*i+17]=-Y00;
    }
    B.setelems_by_array(Barray);
    while(sumelems>1e-10)
    {
    l=L-L0;
    Btran=~B;
    NBB=Btran*B;
    NBBinv=rinv(NBB);
    W=Btran*l;
    x=NBBinv*W;
    sumelems=0;
    for(int j=0;j<x.line;j++)
    {
        sumelems+=x.elems[j];
    }
    X=x+X0;
    X0=X;
    L0=B*X0;
    }
    
    for(int i=0;i<6;i++)
    {
        X00=arrayorg[3*i];
        Y00=arrayorg[3*i+1];
        Z00=arrayorg[3*i+2];
        Barray[21*i+1]=Barray[21*i+2]=Barray[21*i+3]=Barray[21*i+7]=Barray[21*i+9]=
        Barray[21*i+11]=Barray[21*i+14]=Barray[21*i+15]=Barray[21*i+19]=0;
        Barray[21*i]=Barray[21*i+8]=Barray[21*i+16]=1;
        Barray[21*i+18]=Barray[21*i+6]=X00;
        Barray[21*i+5]=Barray[21*i+13]=Y00;
        Barray[21*i+10]=Barray[21*i+20]=Z00;
        Barray[21*i+4]=-Z00;
        Barray[21*i+12]=-X00;
        Barray[21*i+17]=-Y00;
    }
    return 0;
} 
