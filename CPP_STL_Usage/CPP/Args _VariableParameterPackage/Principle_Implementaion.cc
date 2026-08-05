// 原理实现
#include <iostream>

template <typename Tuple, std::size_t N = 0>
void process_tuple(const Tuple &t) {
    if constexpr (N < std::tuple_size<Tuple>::value) {
        // 处理第 N 个元素
        do_something(std::get<N>(t));
        // 递归处理下一个元素
        process_tuple<Tuple, N + 1>(t);
    }
}

/* 可变参数包  */
/* 递归-逐元素提取 法 */

// 类型... 类型名A ：名字为A的可变参数类型
// A... arg ：类型为可变参数A类型的变量arg，且...是告诉编译器这是可变参数类型
//arg...    ：对arg进行解包，如何解就看接收/递归函数的参数(非可变参数的那个）了

/// @brief 递归终止条件
void Show(){
    //接受空元素=解包完毕，然后去掉递归函数=终止递归。
}


template <typename T, typename... Args>
void Show(T t, Args... args) {
    std::cout << t << " ";
    Show(args...);
}

//*********************************** */
/*整体处理法*/

template<typename ... Args>
void Print(Args&&... args) {   
    //  ( std::cout<<...<<args )<<" "; //纯二元折叠表达式，效果不好
    ((std::cout<<args<<" " ), ...); //逗号折叠表达式:C++17
}

template<typename T>
void Print(T&& t){
    std::cout<<t<<" ";
}

template<typename T>
T&& get(T&& t) {   
    return std::forward<T> (t);
}


template<typename... Args>
void test(Args... args){
    // Print(get(args)...);
    // Show(get(args)...);
    // int dummy[] = {(Print(args),0)...}; //C++11 逗号表达式+包展开 dummy:傀儡，占位符,即没啥用的东西
    (Print(args),...);  //表达式,... C++17逗号折叠表达式
}

int main() {
    // Show(1, 'c', "hello");
    test(1,'c',"hello");
    return 0;
}
