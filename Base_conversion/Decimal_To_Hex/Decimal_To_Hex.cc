#include<iostream>
#include<iomanip>

int main(){
    // unsigned char val = 0xff; 
    unsigned char bytes[] = {0x0A, 0x1F, 0xFF, 0x00, 0x7B};
    for (unsigned char b : bytes) {
        //操纵符，只生效一次
        // std::hex: 转为十六进制
        // std::setw(2): 占位2个字符
        // std::setfill('0'): 不足2位用0填充（比如 0A 而不是 A）
        std::cout<< "0x";
        std::cout<<std::setw(4)<<std::setfill('0');
        std::cout << std::hex  <<static_cast<unsigned int>(b) << " ";
    }
    std::cout << std::endl;


    return 0;
}