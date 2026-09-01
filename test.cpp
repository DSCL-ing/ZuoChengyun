#pragma once
#include<iostream>
#include<vector>
#include<typeindex>
#include<typeinfo>
#include<functional>
#include<utility>
#include<type_traits>

#include<chrono>

template<typename T,std::size_t N>
constexpr std::size_t Size(const T  (&)[N]){
    return N;
}

auto fun(const int (&a)[3]) -> void {
    int N = Size(a);
    for (int i = 0 ;i <N; ++i){
        std::cout<<a[i]<<" ";
    }
    
}



int main() {
    int a[3]{1,2,3};
    fun(a);
    return 0;
}

// int main(){
    // int a[3]{1,2,3};
    // int (*p)[3] = &a; //int[3] * p      //数组指针
    // int (&ref)[3] = a;//int[3] & ref

    // void (*f)();    //函数指针

    // void (*f1[3])(); //函数指针数组
    // int (*f2())[3];  //数组指针函数

    // std::cout<<1[a]<<"\n";

    // std::cout<<typeid(p).name()<<std::endl;
    // std::cout<<typeid(decltype(( Aa ))).name()<<std::endl;
    // std::cout<<std::is_same_v<decltype(p),int(*)[3]><<"\n";
    // std::cout<<std::size(a)<<"\n";

//     return 0;
// }