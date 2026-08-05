#include<iostream>
#include<stdio.h>
#include<type_traits>
#define WIN32_LEAN_AND_MEAN  // 排除非核心模块，加快编译
#define NOMINMAX             // 保护 std::min 和 std::max
#include<windows.h>



template <class T>
void DecToBinary(T num)
{
    // 00000000 0000000 0000000 0000000 //不算符号位
    // 01000000 0000000 0000000 0000000 //1左移31位
    T i;
    if (std::is_same<T, char>::value)
    {
        i = 7;
    }
    else
    {
        i = 31;
    }
    for (; i >= 0; i--)
    {
        printf("%c", (num & (1U << i)) == 0 ? '0' : '1'); // 直接字符
        // printf("%d",(num&(1<<i))==0?0:1);   //间接数字
    }
    printf("\n");
}

int main()
{
#ifdef _WIN32

    SetConsoleOutputCP(65001); // 设置控制台输出编码为 UTF-8
    SetConsoleCP(65001);       // 设置控制台输入编码为 UTF-8
#endif



    // system("chcp 65001");
    char a = -1;
    char b = 10;
    DecToBinary<char>(a);
    DecToBinary<char>(b);
    DecToBinary<char>(a - b);


    //常见特数数
    // DecToBinary<char>(-1);
    // std::cout<<(-1^(1<<31))<<std::endl;//有符号最大值
    // std::cout<<(unsigned)-1<<std::endl;//无符号最大值
    // std::cout<<(0^(1<<31))<<std::endl;//负数最小值

    // //求相反数
    std::cout<<5<<std::endl;
    std::cout<<-5<<std::endl;
    std::cout<<~5+1<<std::endl;//求补码的补码，通用法

    //验证按位取反+1 = 求相反数
    // 按位取反+1
    std::cout << std::endl;
    std::cout << "按位取反+1" << std::endl;
    DecToBinary<char>(-b);
    DecToBinary<char>(~-b);
    DecToBinary<char>(~-b + 1);

    // 全1-任意数+1 //按位取反的原理
    std::cout << std::endl;
    std::cout << "全1-任意数+1" << std::endl;
    DecToBinary<char>(a);
    DecToBinary<char>(-b);
    DecToBinary<char>(a - (-b)); //
    DecToBinary<char>(a - (-b) + 1);


    std::cout<<std::endl;
    // char c = 127;
    // DecToBinary<char>(c);
    printf("%hhd\n",(char)(0^(1<<7))); //hh：half of half
    printf("%hhd\n",~((char)(0^(1<<7)))+1); //hh：half of half




    fflush(0);
    return 0;
}

// 复盘
// 1. 符号优先级== > & ，记不住，所以一定要用（）括起来
// 2. %c是‘单引号字符’，最常用最通用。
// 3. 涉及位运算，就要想得到位运算操作符了。封装整形直接计算较难处理
// 4. 左移是未定义行为（符号位被移除），因此可以先将有符号转化成无符号。












/*
在 C/C++ 语言中，格式说明符（Format Specifiers）是 printf() 和 scanf() 等函数的核心。为了方便记忆，我将它们按照数据类型进行了分类，并附上了英文全称和记忆技巧。
1. 整数类型 (Integers)
%d：Decimal（十进制）。
记忆：Decimal 的首字母，用于打印有符号的十进制整数。
%i：Integer（整数）。
记忆：Integer 的首字母。在 scanf 中，它能自动识别十进制、八进制（0开头）和十六进制（0x开头）。
%u：Unsigned（无符号）。
记忆：Unsigned 的首字母，用于打印无符号十进制整数。
%o：Octal（八进制）。
记忆：Octal 的首字母（注意是字母 o，不是数字 0）。
%x / %X：Hexadecimal（十六进制）。
记忆：取 Hexadecimal 中间的 x。小写 %x 输出 a-f，大写 %X 输出 A-F。
2. 浮点类型 (Floating-Point)
%f：Float / Fixed-point（浮点数 / 定点数）。
记忆：Float 的首字母，以十进制小数形式输出。
%e / %E：Exponent（指数）。
记忆：Exponent 的首字母，以科学计数法输出（如 1.23e+04）。
%g / %G：General（通用格式）。
记忆：General 的首字母。它会根据数值大小，自动在 %f 和 %e 之间选择更紧凑、更短的一种格式，并去除末尾多余的 0。
%a / %A：Hexadecimal float（十六进制浮点数）。
记忆：C99 标准引入，取 Hexadecimal 的 a，以 0x 开头的十六进制格式输出浮点数。
3. 字符与字符串 (Characters & Strings)
%c：Character（字符）。
记忆：Character 的首字母，用于输出单个字符。
%s：String（字符串）。
记忆：String 的首字母，用于输出以 \0 结尾的字符数组（字符串）。
4. 指针与特殊类型 (Pointers & Special)
%p：Pointer（指针）。
记忆：Pointer 的首字母，以十六进制形式输出内存地址。
%n：Number of chars（已输出的字符数）。
记忆：Number 的首字母。它不打印任何内容，而是将到目前为止已经打印的字符总数，存入对应的指针变量中。
%%：Percent（百分号）。
记忆：转义字符，用于在屏幕上打印出一个真实的 % 符号。
5. 长度修饰符 (Length Modifiers)
这些修饰符通常放在 % 和类型字母之间，用来告诉编译器变量的实际长度：
hh：Half of half（半半 / 字节）。
记忆：表示 signed char 或 unsigned char（如 %hhd）。
h：Half（半字）。
记忆：表示 short int（如 %hd）。
l：Long（长）。
记忆：表示 long int 或 double（如 %ld, %lf）。
ll：Long long（长长）。
记忆：表示 long long int（如 %lld）。
L：Long double（长双精度）。
记忆：大写 L 专门用于 long double（如 %Lf）。
z：Size_t（大小类型）。
记忆：取自 sizeof 返回的类型 size_t（如 %zd, %zu）。

*/