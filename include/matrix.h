/* ������� */
#pragma once
class matrix 
/* ������������ */
{friend matrix operator+(matrix &a,matrix &b); 
 friend matrix operator-(matrix &a,matrix &b);
 friend matrix operator*(matrix &a,matrix &b);
 friend matrix operator~(matrix &a);
 friend matrix rinv(matrix &a); 

public: matrix(int l,int c);
		matrix(matrix &m);
		matrix();
		~matrix();
		int setelems_by_array(double array[]);
		int setelems();
		double *elem(int m,int n);
		int display();	
		matrix & operator=(const matrix &m);
        int col,line;
	    double *elems;		
};