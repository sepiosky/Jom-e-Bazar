#include<iostream>
#include<string>
#include<vector>
#include"bazar.h"
using namespace std;
int main()
{
    Bazar bazar;
    string line;
    while(getline(cin,line))
        cout<< bazar.handle_request(line) ;
}
