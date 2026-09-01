#include<iostream>
#include<vector>
#include<typeindex>
// #include<typeinfo>
#include<functional>
#include<utility>
#include<unordered_map>
#include<cstdlib>



//RTD: Runtime type dispatch运行时类型分发/配

using Handle = std::function<void()>;

/// @brief 运行时类型分发
int main(){
    system("chcp 65001 > nul");
    //vector版本
    //用途，少量，固定的类型
    std::vector<std::pair<std::type_index,Handle>> type_map;
    type_map.emplace_back(typeid(int),[](){ ;});

    //unordered_map方案
    //用途：大量，无序，频繁插入，常用
    std::unordered_map<std::type_index,Handle> type_dispatch;
    type_map.emplace_back(typeid(int),[](){ ;});

    return 0;
}

//typeid，输出退化后的类型。（去掉const，引用等）
