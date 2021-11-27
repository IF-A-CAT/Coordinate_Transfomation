#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	double Bmin=10, Bmax=21;
	double Lmax=103, Lmin=93;
	int Bn, Ln;
	Bn = int((Bmax - Bmin) / 0.5);
	Ln = int((Lmax - Lmin) / 0.5);
	string filename = "data/grid.dat";
	ofstream file;
	file.open(filename);

	for (int i = 0; i <= Bn; i++)
	{
		for (int j = 0; j <= Ln; j++)
		{
			file << Bmin + 0.5*i << " " << Lmin + 0.5*j<<endl;
		}
	}
	file.close();
    return 0;
}


