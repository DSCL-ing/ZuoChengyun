#include <cmath>
#include <iostream>
#include <valarray>
#include <vector>
#define WIN32_LEAN_AND_MEAN  
#define NOMINMAX             
#include <windows.h>



void Print(const std::valarray<int> &valArr);

/*
valarray = value
array（值数组），它是一个专门用来存储数值（Value），并且对这些数值进行元素级数学运算的数组。
即封装了计算功能的vector

valarray内部自动维护了一个vector，可RAII，无须手动释放

*/

/* apply */
/*
基本功能：创建一个新的valarray，然后执行用户提供的方法来对各个元素执行相同的操作/变换
参数：一个对一个数进行运算的函数对象。(提供给apply对每个元素都实现相同的func变换/运算)
返回值：一个新的valarray
*/
/// @brief 属于 MemberFunction，不过比较独特，单独取出来验证
void Test_Apply() {
    std::cout << "\n" << " Apply:\n";
    std::valarray<int> valArr1 = {1, 2, 3};
    Print(valArr1);

    // 移动赋值
    valArr1 = valArr1.apply([](int n) -> int { return n * 10; });

    Print(valArr1);
}

void Test_MemberFunction() {
    std::cout << "\n Math:\n";
    std::valarray<int> valArr1 = {1, 2, 3};
    Print(valArr1);
    std::cout << "最大值:" << valArr1.max() <<"\n";
    std::cout << "最小值:" << valArr1.min() <<"\n";
    std::cout << "求和：" << valArr1.sum() << "\n";

    std::cout << "数组整体左移1位，超出丢弃，缺的补0" <<"\n" << "\t";
    Print(valArr1.shift(1));

    std::cout << "数组整体右移1位(左移-1位)，超出丢弃，缺的补0" << "\n" << "\t";
    Print(valArr1.shift(-1));
    std::cout << "数组循环左移1位\n" << "\t";
    Print(valArr1.cshift(1));
    
}

/// @brief <CMath>的数学函数也针对valarray做了重载。
void Test_CMathOverload(){
    std::cout << "每个元素都做绝对值:";
    int arr[] = {1, -2, 3, -4, 5};
    for (int i = 0; i < 5; i++) {
        std::cout<<arr[i]<<"\n";
    }
    std::cout<<"\n";
    std::valarray<int> va = std::abs(std::valarray<int> {arr,5});
    Print(va);
}

void Test_Operator() {
    // valarray operators example

    int init[] = {10, 20, 30, 40};
                                            //     foo:           bar:
    std::valarray<int> foo(init, 4);        //  10 20 30 40
    std::valarray<int> bar(25, 4);          //  10 20 30 40    25 25 25 25

    bar += foo;                             //  10 20 30 40    35 45 55 65

    foo = bar + 10;                         //  45 55 65 75    35 45 55 65

    foo -= 10;                              //  35 45 55 65    35 45 55 65

    std::valarray<bool> comp = (foo == bar);
    if (comp.min() == true)
        std::cout << "foo and bar are equal.\n";
    else
        std::cout << "foo and bar are not equal.\n";

}

void Print(const std::valarray<int> &valArr) {
    std::cout << "valarray数组：";
    for (auto &e : valArr) {
        std::cout << e << " ";
    }
    std::cout << "\n";
}

int main() {
    std::ios::sync_with_stdio(false); //同步stdio吗，不同步
    std::cin.tie(nullptr);             //同步cout吗，不同步
    system("chcp 65001");

    // GTest命名法，google test
    // 动宾命名
    // 动_宾 或 主_动宾 命名，内部结合大驼峰命名。
    Test_MemberFunction();
    Test_CMathOverload();
    Test_Apply();
    Test_Operator();

    return 0;
}