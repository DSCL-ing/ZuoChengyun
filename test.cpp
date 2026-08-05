#include<iostream>
#include<vector>
#include<typeindex>
#include<typeinfo>
#include<functional>
#include<utility>
#include<type_traits>

struct A{
    int _a;
};

#define N 1

int main(){
    int a = 0;
    int b = 1;
    int arr[5]{0} ;
    A aa;
    std::cout<<std::is_same_v<decltype((a)),int&><<std::endl;
    std::cout<<std::is_same_v<decltype(N),int><<std::endl;
    std::cout<<std::is_same_v<decltype(arr[0]),int&><<std::endl;
    std::cout<<std::is_same_v<decltype(a == 0?a:b),int&><<std::endl;
    return 0;
}