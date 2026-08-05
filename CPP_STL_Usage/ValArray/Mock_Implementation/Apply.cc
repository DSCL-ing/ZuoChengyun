// 伪代码：展示 apply 的底层原理
template<class T>
class valarray {
    T* data_;      // 指向堆内存的指针
    size_t size_;  // 数组大小

public:
    // Func 是传入的 Lambda 或函数对象
    //Func的功能是对一个数的运算，经过遍历后实现每个valarray元素都经过Func运算；
    template<class Func>
    valarray<T> apply(Func func) const //const: 这个函数承诺绝对不会修改当前对象（this）的任何内部数据。
    {
        // 1. 创建一个全新的、大小相同的临时 valarray 对象
        valarray<T> result(size_); 
        
        // 2. 遍历原数组，对每个元素应用传入的函数
        for (size_t i = 0; i < size_; ++i) {
            result.data_[i] = func(data_[i]); 
        }
        
        // 3. 返回这个新对象（在现代 C++ 中，这里通常会触发移动语义或 RVO 优化）
        return result;
    }
};

/*
为什么它比手写 for 循环更好？
除了代码更简洁，apply 还有两个隐藏优势：
1. 编译器自动向量化（Auto-vectorization）：因为 apply 内部的循环逻辑极其简单（纯粹的线性遍历 + 独立计算，没有任何分支跳转），
现代编译器（如 GCC/Clang 开启 -O2 时）极容易将其识别并转化为 SIMD 指令（如 AVX/SSE），
让 CPU 在一个时钟周期内同时处理 4 个或 8 个数字。
2.表达式模板（Expression Templates）：
部分高级 C++ 库在实现 valarray 时，apply 甚至不会立即执行循环，而是返回一个“表达式代理对象”。
只有当这个结果被真正赋值给另一个 valarray 时，才会触发一次合并后的循环，进一步减少内存访问。
(直白说就是，标准库实现的更容易被优化，一个硬件执行优化，另一个编译执行优化)
*/