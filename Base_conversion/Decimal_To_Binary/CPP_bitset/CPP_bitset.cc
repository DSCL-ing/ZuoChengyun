#include<iostream>
#include<bitset>

template<typename T, size_t N>
constexpr size_t Size(const T (&)[N]){  //接收一个支持方括号的容器的引用
    return N;
}

int main(){
    int num  = 65; //0100 0001 = 64+1 = 2^(7-1) +1 = 第七位1，第一位1
    //小端是低位个位先存储，即小，小端先存
    //计算机一般都是小端（电路设计简单，从小算起）.人是大端（从高位写起）
    //所以num = 1000 0010 ...
    std::bitset<32> bitarr{static_cast<unsigned int>(num)};
    
   
    //Method 1      方法1，法1      M1
    //Approach 1    思路1（学术）   App.1
    //solution 1    解法1           Sol.1
    //example 1     例1             Ex.1
    //case 1        条件/情况1      
    //way 1         通用，口语
    //Instance 1    实例1
    for (size_t i = 0, N = bitarr.size(); i < N; i++) {
        //0 31 ; 31= 32-1 => N-i-1
        std::cout<<bitarr[N-i-1];
    }
    std::cout<<std::endl;

    //Method 2
    //cast 2
    //Approach 2
    std::cout<<bitarr.to_string()<<std::endl;

    return 0;
}