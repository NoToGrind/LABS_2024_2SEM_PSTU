#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <string.h>
#include <cstdlib>
using namespace std;

int main()
{
	string str;
	ifstream myf1("F1.txt");
	fstream myf2("F2.txt");
	if (!myf2.is_open())
	{
		cout << "error" << endl;
	}

	while (getline(myf1, str))
	{
		if (str[0] == 'A')
		{
			myf2 << str << endl;
		}
	}
	myf1.close();
	myf2.close();
	string ch;
	ifstream myf("F2.txt");

	int k = 0;
	while (getline(myf, ch))
	{
		k++;
	}
	myf.close();
	

	cout << k << endl;
	return 0;
}