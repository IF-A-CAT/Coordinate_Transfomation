#include"Function.h"
#include<iostream>
#include<string>
#include<math.h>
#include"matrix.h"
using namespace std;
int main()
{
    double ArrayOrg[18],ArrayChg[18];//number of arguments
    double ArrayOrgBefore[12],ArrayChgBefore[12];
    double ArrayOrgPost[6],ArrayChgPost[6];
    double BParray[42];
    string stro,strc;
    double Z00,Y00,X00;
    stro="XYZ_origin_2.xyz";
    strc="XYZ_target_2.xyz";
    file_read(stro,ArrayOrg);
    file_read(strc,ArrayChg);
    for(int n=0;n<18;n++)
    {
        if(n<12)
        {
            ArrayOrgBefore[n]=ArrayOrg[n];
            ArrayChgBefore[n]=ArrayChg[n];
        }
        else
        {
            ArrayOrgPost[n-12]=ArrayOrg[n];
            ArrayChgPost[n-12]=ArrayChg[n];
        }
    }
    double corr;
    matrix LP(6,1);
    matrix BP(6,7);
    matrix Lsq(6,1);
    matrix vpost(6,1);
    matrix L(12,1);
    matrix L0(12,1);
    matrix B(12,7);
    matrix Btran(7,12);
    matrix NBB(7,7);
    matrix l(12,1);
    matrix NBBinv(7,7);
    matrix W(7,1);
    matrix x(7,1);
    matrix X0(7,1);
    matrix v(12,1);
    matrix vtran(12,1);
    matrix residual(12,1);
    matrix X(7,1);
    L.setelems_by_array(ArrayChgBefore);
    double Barray[84];
    double sumelems=1;
    double X0ori[7]={0,0,0,0,0,0,1};
    X0.setelems_by_array(X0ori);
    for(int i=0;i<4;i++)
    {
        X00=ArrayOrgBefore[3*i];
        Y00=ArrayOrgBefore[3*i+1];
        Z00=ArrayOrgBefore[3*i+2];
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
    v=L0-L;
    vtran=~v;
    corr=sqrt((vtran*v).elems[0]/(12-7));
    residual=L-L0;
    for(int i=0;i<2;i++)
    {
        X00=ArrayOrgPost[3*i];
        Y00=ArrayOrgPost[3*i+1];
        Z00=ArrayOrgPost[3*i+2];
        BParray[21*i+1]=BParray[21*i+2]=BParray[21*i+3]=BParray[21*i+7]=BParray[21*i+9]=
        BParray[21*i+11]=BParray[21*i+14]=BParray[21*i+15]=BParray[21*i+19]=0;
        BParray[21*i]=BParray[21*i+8]=BParray[21*i+16]=1;
        BParray[21*i+18]=BParray[21*i+6]=X00;
        BParray[21*i+5]=BParray[21*i+13]=Y00;
        BParray[21*i+10]=BParray[21*i+20]=Z00;
        BParray[21*i+4]=-Z00;
        BParray[21*i+12]=-X00;
        BParray[21*i+17]=-Y00;
    }
    BP.setelems_by_array(BParray);
    LP.setelems_by_array(ArrayChgPost);
    Lsq=BP*X;
    vpost=LP-Lsq;
    //result disply
    cout<<"--------------------"<<"Result Display"<<"--------------------"<<endl;
    cout<<"七参数最优估计值:"<<endl;
    X.display();
    cout<<"-------------------------------------------------------------"<<endl;
    cout<<"条件数n:"<<"12"<<endl;
    cout<<"-------------------------------------------------------------"<<endl;
    cout<<"冗余度r:"<<"5"<<endl;
    cout<<"-------------------------------------------------------------"<<endl;
    cout<<"验后单位权中误差:"<<corr<<endl;
    cout<<"-------------------------------------------------------------"<<endl;
    cout<<"每个公共点坐标残差:"<<endl;
    cout<<"point\t\t"<<"dX\t\t"<<"dY\t\t"<<"dZ\t\t"<<endl;
    cout<<"1\t"<<residual.elems[0]<<"\t"<<residual.elems[1]<<"\t"<<residual.elems[2]<<endl;
    cout<<"2\t"<<residual.elems[3]<<"\t"<<residual.elems[4]<<"\t"<<residual.elems[5]<<endl;
    cout<<"3\t"<<residual.elems[6]<<"\t"<<residual.elems[7]<<"\t"<<residual.elems[8]<<endl;
    cout<<"4\t"<<residual.elems[9]<<"\t"<<residual.elems[10]<<"\t"<<residual.elems[11]<<endl;
    cout<<"-------------------------------------------------------------"<<endl;
    cout<<"每个检核点坐标残差:"<<endl;
    cout<<"point\t\t"<<"dX\t\t"<<"dY\t\t"<<"dZ\t\t"<<endl;
    cout<<"5\t"<<vpost.elems[0]<<"\t"<<vpost.elems[1]<<"\t"<<vpost.elems[2]<<endl;
    cout<<"6\t"<<vpost.elems[3]<<"\t"<<vpost.elems[4]<<"\t"<<vpost.elems[5]<<endl;
    return 0;
} 
