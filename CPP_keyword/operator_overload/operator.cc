#include<iostream>

/* 运算符重载仅限四种参数类型 */
int operator "" _s(unsigned long long m){   //整形
// int operator "" _s(long double m){       //浮点
// int operator "" _s(const char* m){       //字符串
// int operator "" _s(char m){              //字符
    return m*60;
}


int main(){
    int s = 2_s;
    return 0;
}