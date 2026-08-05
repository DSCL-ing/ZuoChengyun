

#include <iostream>
#include <stdexcept> // 包含标准异常头文件
#include <thread>
/* 异常的主要用途

- 可挽回的错误：提示异常信息并尝试重新运行(外部while)
- 不可挽回的错误：及时备份，记录日志，保存现场等挽救工作
*/


/* 异常语法和关键字

无异常声明：
- noexcept  //告诉开发者和编译器这个代码绝对无异常
- throw() //C++11及以前，很垃圾，且语义易混淆。本意：抛出一个空异常，即无异常
- noexcept(表达式) //模板元编程... 暂时略
    - eg. noexcept(std::is_nothrow_move_constructible_v<MyClass>) //是否是不抛异常的，可移动的，构造函数

捕获异常：
- try：尝试捕获区
- catch:捕获配置组件，逻辑上和try并行而不是再其后
    - catch(...){}          //捕获任意异常
    - catch(exception& e)   //捕获标准异常

嵌套异常
- throw_with_nested(新异常) //抛出嵌套异常：先构建一个新异常，这个新异常里会被自动嵌套当前捕获的旧异常
- rethrow_if_nested(异常)   //如果是嵌套则复活异常


抛出异常：
- throw;：原封不动地传递，保留一切信息，适用于“只做善后，不做转换”的场景。
- throw (新异常);：改变异常的类型，适用于“转换语义”，但代价是丢失旧信息。
- throw_with_nested(新异常);：改变异常的类型，同时保留旧信息，适用于“既要转换，又要保留案发现场”。


跨线程处理：
- exception_ptr             //异常指针变量,搭配<future>使用 ，可以被主线程或其他线程提取
- current_exception()       //返回当前线程的指针,配合exception_ptr使用
- rethrow_exception()       //将异常复活，用于把其他线程的exception_ptr复活出来
最佳实践：在实际开发中，跨线程传递异常通常配合 std::promise / std::future 使用。
promise 内部是线程安全的，它天生就支持把 exception_ptr 安全地传递给主线程。


*/



/*  异常执行流：
Throw：中断当前流，开始栈展开（自动析构局部对象）。
Unwinding：一层层往上退，只要不在 try 里，就继续析构、继续退。
Catch：找到 try 且类型匹配，停止后退，执行救援代码。
Terminate：退到 main 之外还没人管，直接 std::terminate() 枪毙程序。

与手动错误码执行流类似，错误码需要手动且有限，而异常纯自动（自动跨越栈传递，自动RAII等）。
核心用途区别，性能开销及语义
语义：
- 常规控制流：错误码
- 预料之外或外部条件异常：异常 //若性能不满足，可回退到错误码
 */


//嵌套异常例子
// 这是一个通用的“异常解包器” 
void print_exceptions(const std::exception& e, int level = 0) {
    // 1. 打印当前层的异常
    std::cerr << std::string(level * 2, ' ') << "异常: " << e.what() << std::endl;

    // 2. 尝试提取下一层嵌套的异常
    try {
        std::rethrow_if_nested(e); // 如果没有嵌套，这里会直接跳过
    } catch (const std::exception& inner_e) {
        // 3. 如果有嵌套，递归调用自己，层数 +1
        print_exceptions(inner_e, level + 1);
    } catch (...) {
        // 处理非标准异常
        std::cerr << std::string((level + 1) * 2, ' ') << "未知异常" << std::endl;
    }
}

/*跨线程例子*/
std::exception_ptr global_exception_ptr = nullptr;  //不推荐，简化用。推荐<future>
void worker_thread() {
    try {
        // 模拟子线程中发生的致命错误
        throw std::runtime_error("子线程内存溢出！");
    } catch (...) {
        // 【关键步骤 1】：在子线程的 catch 块中，给当前异常拍个“X光片”
        global_exception_ptr = std::current_exception();
    }
}

/* 单线程例子 */
void doSomething() {
    if (1) {
        // 抛出标准运行时异常
        throw std::runtime_error("除数不能为零！"); 
    }
    if(2){
         // 【核心】：把当前的异常保留，并抛出一个新的异常
        std::throw_with_nested(std::logic_error("上层错误：配置文件加载失败"));
    }
}

int main() {

    //单线程例子
    //while{} //业务上，实现循环重启
    try {
        doSomething();
    }
    // 1. 优先捕获具体的、能处理的异常
    catch (const std::out_of_range &e) {
        std::cerr << "数据越界，使用默认值: " << e.what() << std::endl;
    } catch (const std::system_error &e) {
        std::cerr << "系统错误，准备重试: " << e.what() << std::endl;
    }
    // 2. 捕获其他标准异常
    catch (const std::exception &e) {
        print_exceptions(e);    
        std::cerr << "发生标准异常: " << e.what() << std::endl;
    }
    // 3. 终极兜底（必须放在最后！）
    catch (...) {
        std::cerr << "发生了完全未知的灾难性错误，程序即将安全退出。" << std::endl;
    }


    //跨线程例子
    std::thread t(worker_thread);
    t.join(); // 等待子线程结束
        // 【关键步骤 2】：在主线程中检查是否捕获到了异常快照
    if (global_exception_ptr) {
        try {
            // 【关键步骤 3】：在主线程的上下文中，让异常“复活”
            std::rethrow_exception(global_exception_ptr);
        } catch (const std::exception& e) {
            // 主线程成功捕获并处理了原本属于子线程的异常！
            std::cerr << "主线程收到子线程异常: " << e.what() << std::endl;
        }
    }    // 【关键步骤 2】：在主线程中检查是否捕获到了异常快照

    return 0;
}

/*
Exception分支
分支一：std::logic_error（逻辑错误）
本意：这类错误是程序员的锅。它通常是因为代码逻辑写错了，在程序运行前或运行初期就能通过检查代码发现的。
常见子类：
- std::invalid_argument：传入了非法的参数（比如给 std::bitset 传了非 0/1 的字符串）。
- std::out_of_range：越界访问（比如 std::vector::at() 越界时抛出）。
- std::length_error：试图创建一个超过最大允许长度的容器。

分支二：std::runtime_error（运行时错误）
本意：这类错误是运行环境的锅。代码逻辑可能完全没问题，但在运行时遭遇了不可预见的外部灾难。
常见子类：
- std::range_error：内部计算时发生了范围错误（如浮点数下溢）。
- std::overflow_error：算术运算溢出。
- std::system_error：就是我们之前聊过的，封装了底层操作系统或 C 语言 API 的错误码（如文件打不开、网络断开）。

3. 其他“独立”或“特殊”的异常
- std::bad_alloc（内存分配失败）：
  定义在 <new> 中。当 new 操作符申请不到内存时抛出。它直接继承自 std::exception，不属于上面两大分支。
- std::bad_cast（错误的类型转换）：
  定义在 <typeinfo> 中。当我们用 dynamic_cast 对引用（Reference）进行向下转型，但实际类型不匹配时抛出。
 （注意：如果是对指针进行 dynamic_cast，失败只会返回 nullptr，不会抛异常）。
- std::bad_exception（意外的异常）：
  这是一个非常冷门的异常。当函数抛出了一个不在其异常规范（旧式 throw(...)）中的异常，
  且也没有被 catch(...) 捕获时，就会抛出这个异常。现在有了 noexcept，它基本已经被时代淘汰了。
 */