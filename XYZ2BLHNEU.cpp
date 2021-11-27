#include<iostream>
#include"matrix.h"
#include"Function.h"
#include<cmath>
#include<string>
using namespace std;

int main()
{
    double XYZarray[14435*3];
    double BLH[3];
    double dX,dY,dZ;
    file_read("data/XYZ2BLHNEU.xyz",XYZarray);
    double XYZ[3]={XYZarray[0],XYZarray[1],XYZarray[2]};
    double XYZresult[14435*3];
    XYZ2BLH(XYZ,BLH);
    for(int i=0;i<14435;i++)
    {
        if(i==0)
             XYZresult[0]=XYZresult[1]=XYZresult[2]=0;
        else
            dX=XYZarray[i*3]-XYZarray[0];
            dY=XYZarray[i*3+1]-XYZarray[1];
            dZ=XYZarray[i*3+2]-XYZarray[2];
            XYZresult[i*3]=-dX*sin(BLH[0])*cos(BLH[1])-dY*sin(BLH[0]*sin(BLH[1])+dZ*cos(BLH[0]));
            XYZresult[i*3+1]=-sin(BLH[1])*dX+cos(BLH[1])*dY;
            XYZresult[i*3+2]=cos(BLH[0])*cos(BLH[1])*dX+cos(BLH[0])*sin(BLH[1])*dY+sin(BLH[0])*dZ;
    }
    for(int i=0;i<14435;i++)
    {
            cout<<i+1<<","<<XYZresult[i*3]<<","<<XYZresult[i*3+1]<<","<<XYZresult[i*3+2]<<endl;
    }
    return 0;
}