#include <iostream>
#include <string>
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    system("chcp 1251");
    system("cls");
    string str;
    getline(cin, str);
    string str1 = "";        // now word
    string str2 = "";       // max word
    string str3 = "";       // min word
    int k = 0;             // length now
    int max = 0;           // max length
    int min = 100000;     // min length

    for (int i = 0; i <= str.length(); i++) 
    {
        if (str[i] != ' ')
        {
            k++;
            str1 += str[i];
        }
        else
        {
            if (k > 0)              
            {
                if (k < min)
                {
                    min = k;
                    str3 = str1;    
                }
                if (k > max)
                {
                    max = k;
                    str2 = str1;   
                }
            }
            k = 0;              
            str1 = "";
        }
    }

    cout << "Самое короткое слово: " << str3 << '\n';
    cout << "Самое длинное слово: " << str2 << '\n';

    return 0;
}
