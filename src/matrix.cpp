//#include"stdafx.h"
#include"stdio.h"
#include"math.h"
#include<iostream>
#include"matrix.h"
using namespace std;

matrix::matrix(){
	line = 0;
	col = 0;
	elems = new double[1];
}

matrix::matrix(int l,int c){
	line = l;
	col = c;
	elems=new double [c*l];
	for (int i = 0; i < c*l; i++)
		elems[i] = 0.0;
}/* ���캯��,����ռ� */

matrix::matrix(matrix &m){
	line=m.line;col=m.col;
	elems=new double [line*col];
	for(int i = 0; i< line*col; i++)
	elems[i]=m.elems[i];
}/* ���� */

int matrix::setelems(){
	int i,j;
	for (i = 0; i < line; i++)
	for (j = 0; j < col; j++)
		cin>>elems[i*col+j];
	return 0;
}/* ��ֵ���� */

int matrix::setelems_by_array(double matarray[]){
	int i;
	for(i=0;i<line*col;i++)
	{
		elems[i]=matarray[i];
	}
	return 0;
}/* ��ֵ���� */

matrix::~matrix(){
	delete []elems;
}

 double *matrix::elem(int m,int n){
	return &elems[m*col+n];
}

int matrix::display(){
	for(int i=0;i<line;i++){
		for(int j=0;j<col;j++)
			cout<<elems[i*col+j]<<",";
		cout<<endl;
	}
		 cout<<endl;
return 0;
}

/* �Ӻ����� */
matrix operator+( matrix &a,matrix &b){
	if(a.line!=b.line||a.col!=b.col){
		cout<<"���������кŲ���"<<endl;
	    exit(0);
	}
	matrix c(a.line,a.col);
	for(int i=0;i<a.line*a.col;i++)
	c.elems[i]=a.elems[i]+b.elems[i];
	return c;
}

/* �������� */
matrix operator-(matrix &a,matrix &b){
	if(a.line!=b.line||a.col!=b.col){
		cout<<"���������кŲ���"<<endl;
	    exit(0);
	}
	matrix c(a.line,a.col);
	for(int i=0;i<a.line*a.col;i++)
	c.elems[i]=a.elems[i]-b.elems[i];
	return c;
}

/* ~����Ϊת�� */
matrix operator~(matrix &a){
	matrix c(a.col,a.line);
	for(int i=0;i<a.line;i++)
		for(int j=0;j<a.col;j++)
			c.elems[j*a.line+i]=a.elems[i*a.col+j];
	return c;
}

/* �Ⱥ� */
matrix & matrix::operator=(const matrix &m){
	line=m.line;col=m.col;
    delete [] elems;
	elems=new double [m.line*m.col];
	for(int i=0;i<m.line*m.col;i++)
	elems[i]=m.elems[i];
	return *this;
}

/* �˺����� */
matrix operator*(matrix &a,matrix &b){
	int line =a.line;
	int col=b.col;
	if(a.col!=b.line){
		cout<<"���������˷�������ǰ������������������������"<<endl;
		exit(0);
	}
	matrix c(line,col);
	for(int i=0;i<line*col;i++)
		c.elems[i]=0;
	for(int i=0;i<line;i++)
		for(int j=0;j<col;j++)
			for(int k=0;k<a.col;k++)
				c.elems[i*col+j]+=a.elems[i*a.col+k]*b.elems[k*col+j];
	return c;

}

matrix rinv(matrix &a){
	if(a.col!=a.line){
		cout<<"�þ����Ƿ��󣬲�������"<<endl;
		exit(0);
	}
	matrix c=a;
	int *is,*js,i,j,k,n,l,v,u;
	double d,p;
	n=a.line;
	js=new int [n];
	is=new int [n];
	for(k=0;k<n;k++){
		d=0.0;
		for(i=k;i<n;i++)
			for(j=k;j<n;j++){
				l=i*n+j;p=fabs(c.elems[l]);
				if(p>d){d=p;is[k]=i;js[k]=j;}
		      }
			if(d+1.0==1.0){
				delete[] js;delete[] is;
				cout<<"�þ���������"<<endl;exit(0);}
			/* �ҳ���k�ε����ֵ������¼���к� */
			if (is[k] != k){
				for (j = 0; j < n; j++) { u = k*n + j; v = is[k] * n + j; p = c.elems[u]; c.elems[u] = c.elems[v]; c.elems[v] = p; }/* �н��� */
			}
			if (js[k] != k){
				for (i = 0; i < n; i++) { u = i*n + k; v = i*n + js[k]; p = c.elems[u]; c.elems[u] = c.elems[v]; c.elems[v] = p; }/* �н��� */
			}
			l = k*n + k;
			c.elems[l] = 1.0 / c.elems[l];
			for (j = 0; j < n; j++){
				if (j != k) { u = k*n + j; c.elems[u] = c.elems[u] * c.elems[l]; }
			}
			for (i = 0; i < n; i++){
				if (i != k){
					for (j = 0; j < n; j++)
					if (j != k) { u = i*n + j; c.elems[u] = c.elems[u] - c.elems[i*n + k] * c.elems[k*n + j]; }
				}
			}
			for (i = 0; i < n; i++){
				if (i != k){ u = i*n + k; c.elems[u] = -1.0*c.elems[u] * c.elems[l]; }
			}
	}
	for(k=n-1;k>=0;k--){
		if (js[k] != k){
			for (j = 0; j < n; j++){ u = k*n + j; v = js[k] * n + j; p = c.elems[u]; c.elems[u] = c.elems[v]; c.elems[v] = p; }
		}
		if (is[k] != k){
			for (i = 0; i < n; i++){ u = i*n + k; v = i*n + is[k]; p = c.elems[u]; c.elems[u] = c.elems[v]; c.elems[v] = p; }
		}
	}
	delete [] is,js;
	return c;
}



