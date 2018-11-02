#include <iostream>
#include<fstream>
long long const mod = 18000000007L;
int main()
{
    long long int n;
    std::ofstream fOut("input.txt");
    std::cout<<"n1=";
    std::cin>>n;
    for(int i=0;i<n;i++)
    {
        fOut<<rand()%mod<<" "<<rand()%mod<<std::endl;
    }
    fOut.close();
}