#pragma once
#include<string>
#include"matrix.h"

void file_read(std::string filename,double arraylist[]);
void string_split(std::string str,const char* sign,double []);
matrix get_B_matrix(matrix A,matrix X0,double K,matrix *N);
matrix get_C_matrix(matrix A);
