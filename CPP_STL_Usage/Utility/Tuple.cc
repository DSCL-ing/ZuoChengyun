#include <iostream>
#include <string>
#include <tuple>
#include <utility>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // 定义
    std::tuple<int, double, std::string> t1;                //空定义
    std::tuple<int, double, std::string> t2(1, 1.1, "111"); //圆括号
    std::tuple<int, double, std::string> t3{2, 2.2, "222"}; //花括号
    std::tuple<int, double, std::string> t4(t2);            // 拷贝构造
    t1 = t2;                                                // 拷贝赋值
    std::tuple<int, double, std::string> t0{0, 0.0, "000"};
    t1 = std::move(t0);                                 // 移动赋值,t0不能再访问，除非重新赋值（类指针操作）
    t0 = t1;                                                // 重新赋值，可重新使用（仅适合底层代替指针）
    auto t5 = std::make_tuple(3, 3.3, "333");   //make_tuple快速构造元组
    auto t6 = std::exchange(t1, t3);              //exchange接收新值，返回旧值

    // 提取、解包
    auto tp = std::make_tuple<>(1, 1.1, "111");
    int i = 0;
    double d = 0.0;
    std::string str;
    i = std::get<0>(tp);    //get解包
    d = std::get<1>(tp);
    str = std::get<2>(tp);
    std::cout << "i:" << i << " ,d:" << d << " ,str:" << str << "\n";

        //tie解包
    std::tie(i, d, str) = t1; // 函数本质是函数值，即返回值，所以tie可以看作是tuple模板，然后走其构造...
    std::cout << "i:" << i << " ,d:" << d << " ,str:" << str << "\n";
    std::tie(i, std::ignore, str) = tp;
    std::cout << "i:" << i << " ,d:" << d << " ,str:" << str << "\n";

        //结构化绑定解包
    auto [a, b, c] = tp; // 结构化绑定
    auto ttp = std::tuple_cat(t1, tp);

    //<tuple>apply 应用
    // apply顾名思义，应用.将元组（包括数组，pair等）各个元素应用相同的方案
       std::apply(
        [](auto &&...args) { // 这里就是可变参数包
            // 折叠表达式：对每一个参数执行打印
            ((std::cout << args << " "), ...);
        },
        ttp);
       std::apply([](auto &&...args) { ((std::cout << args << " "), ...); }, ttp); // 对ttp运用逗号折叠表达式
       return 0;
}
