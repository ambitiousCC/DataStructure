#include <iostream>
using namespace std;
int main()
{
    string input;
    cin>>input;
    char ch;
    for(int i=0;i<input.length();i++)
    {
        ch = input[i];
        cout<<ch<<" "<<i<<endl;
    }
    return 0;
}
