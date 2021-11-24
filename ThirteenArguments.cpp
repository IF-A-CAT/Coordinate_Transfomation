#include<iostream>
#include"matrix.h"
#include"Function.h"
#include<cmath>
#include<string>
using namespace std;


int main()
{
    double pointsorg[51],pointschg[51],pointsorgBefore[33],pointschgBefore[33];
    double pointsorgPost[18],pointschgPost[18];
    double CoefArray[19*19];
    double K=1;
    double n=0;
    double X0array[13]={0,0,0,1,1,0,0,0,1,0,0,0,1};
    double R0[9]={1,0,0,0,1,0,0,0,1};
    double Wkarray[6]={1,1,1,0,0,0};
    double Xchg=1;
    double X00array[12];
    file_read("data/XYZ_origin_3.xyz",pointsorg);
    file_read("data/XYZ_target_3.xyz",pointschg);
    for(int i=0;i<51;i++)
    {
        if(i<33)
        {
            pointsorgBefore[i]=pointsorg[i];
            pointschgBefore[i]=pointschg[i];
        }
        else
        {
            pointsorgPost[i-33]=pointsorg[i];
            pointschgPost[i-33]=pointschg[i];
        }
    }
    matrix invcoef(19,19);
    matrix Wk(6,1);
    matrix wk(6,1);
    matrix xK(19,1);
    matrix XYZO(33,1);
    matrix XYZ(33,1);
    matrix X0(13,1);
    matrix x(13,1);
    matrix R(3,3);
    matrix coef(19,19);
    matrix B(33,13);
    matrix Btran(13,33);
    matrix C(6,13);
    matrix Ctran(13,6);
    matrix Wl(13,1);
    matrix Wkstd(6,1);
    matrix W(19,1);
    matrix Nbb(13,13);
    matrix XYZ00(13,1);
    matrix B1(33,12);
    matrix X00(12,1);
    //matrix Ncc(6,6);
    //matrix Nccinv(6,6);
    //matrix Nbbinv(13,13);
    //matrix First(1,1);
    //matrix Second(1,1);
    XYZ.setelems_by_array(pointschgBefore);
    Wkstd.setelems_by_array(Wkarray);
    XYZO.setelems_by_array(pointsorgBefore);
    while(Xchg>1e-8)
    {
    R.setelems_by_array(R0);
    B=get_B_matrix(R,XYZO,K,&B1);
    X0.setelems_by_array(X0array);
    for(int i=0;i<12;i++)
    {   if(i<3)
            X00array[i]=X0array[i];
        else
            X00array[i]=X0array[i+1];
    }
    X00.setelems_by_array(X00array);
    C=get_C_matrix(R);
    Ctran=~C;
    Btran=~B;
    XYZ00=B1*X00;
    Wl=XYZ-XYZ00;
    Wl=Btran*Wl;
    Nbb=Btran*B;
    //Nbbinv=rinv(Nbb);
    //Ncc=C*Nbbinv;
    //Ncc=Ncc*Ctran;
    //Nccinv=rinv(Ncc);
    //Second=Nbbinv*Ctran;
    //Second=Second*Nccinv;
    wk.elems[0]=X0.elems[4]*X0.elems[4]+X0.elems[5]*X0.elems[5]+X0.elems[6]*X0.elems[6];
    wk.elems[1]=X0.elems[7]*X0.elems[7]+X0.elems[8]*X0.elems[8]+X0.elems[9]*X0.elems[9];
    wk.elems[2]=X0.elems[10]*X0.elems[10]+X0.elems[11]*X0.elems[11]+X0.elems[12]*X0.elems[12];
    wk.elems[3]=X0.elems[4]*X0.elems[5]+X0.elems[7]*X0.elems[8]+X0.elems[10]*X0.elems[11];
    wk.elems[4]=X0.elems[4]*X0.elems[6]+X0.elems[7]*X0.elems[9]+X0.elems[10]*X0.elems[12];
    wk.elems[5]=X0.elems[5]*X0.elems[6]+X0.elems[8]*X0.elems[9]+X0.elems[11]*X0.elems[12];    
    Wk=Wkstd-wk;
    // Second=Second*Wk;
    // First=Nbbinv*Ctran;
    // First=First*Nccinv;
    // First=First*C;
    // First=First*Nbbinv;
    // First=Nbbinv-First;
    // First=First*Wl;
    // x=First-Second;
    for(int i=0;i<19;i++)
    {
        for(int j=0;j<19;j++)
        {   if(j<13)
                if(i<13)
                    CoefArray[j+i*19]=*(Nbb.elem(i,j));
                else
                    CoefArray[j+i*19]=*(C.elem(i-13,j));
            else
                if(i<13)
                    CoefArray[j+i*19]=*(Ctran.elem(i,j-13));
                else
                    CoefArray[j+i*19]=0;
        }
    }
    coef.setelems_by_array(CoefArray);
    //Wl.display();
    for(int i=0;i<19;i++)
    {
        if(i<13)
            W.elems[i]=Wl.elems[i];
        else
            W.elems[i]=Wk.elems[i-13];
    }
    //W.display();
    //X0.display();
    //Wk.display();
    invcoef=rinv(coef);
    xK=invcoef*W;
    Xchg=0;
    for(int i=0;i<13;i++)
    {
        Xchg+=abs(xK.elems[i]);
        X0array[i]=X0array[i]+xK.elems[i];
        if(i>3)
        {
            R0[i-4]=X0array[i];
        }
    }
    K=K+xK.elems[3];
    n+=1;
    }
    XYZ00.display();
    //(XYZ-XYZ00).display();
    cout<<n<<endl;
    return 0;
}