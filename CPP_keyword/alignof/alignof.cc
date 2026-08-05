#include<iostream>


int main(){

    std::cout<<alignof(int)<<std::endl; //对齐字节数
    std::cout<<alignof(char)<<std::endl; //对齐字节数

    return 0;
}