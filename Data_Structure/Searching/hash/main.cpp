#include <iostream>
using namespace std;
const double pi=3.1415926;
int main( )
{
    float r,a;
    cout<<"����뾶��"<<endl;
    cin>>r;
    a=pi*r*r;
    cout<<"��������";
    cout<<a<<endl;
    return 0;
}

float volume(float h,float r)
{
    return pi*r*r*h;
}


