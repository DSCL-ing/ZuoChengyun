#include<iostream>
#include<limits>


int main(){
    int i = 1;
    char c = 'a';
    long l = 1;
    decltype(c) ch = 1;
    std::cout<<std::numeric_limits<decltype(i)>().max()<<"\n";
    std::cout<<std::numeric_limits<int>().min()<<"\n";
    // std::cout<<std::numeric_limits<char>().max()<<"\n";
    // std::cout<<std::numeric_limits<char>().min()<<"\n";
    std::cout<<std::numeric_limits<long long>().max()<<"\n";
    std::cout<<std::numeric_limits<long long>().min()<<"\n";

    std::cout<<alignof(int)<<std::endl; //对齐字节数

    return 0;
}