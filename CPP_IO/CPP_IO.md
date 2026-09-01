### std::ios_base::openmode_mode

- std::ios::out：以输出方式打开（注：默认的ofstream，是out|trunc）
- std::ios::in： 以读入方式打开
- ate(at end)：以'起始位置位于文件末尾'的方式打开
- app(append)：以追加的方式打开，文件指针只能在文件末尾，不可改变
- trunc(truncate)：以清空文件内容的方式打开文件，即清空文件
- binary；不是真的二进制(C++11不直接支持二进制)，而是不改变文件内容，以原始方式打开。如在windows系统中打开文件会把\n变成\n\r，使用binary就不会。

### 明确的打开方式

1. ifstream（只读）
   - in ----------------- 只读
2. ofstream（要么清空要么追加）
   - out或out|trunc ---  清空再输出
   - out|app ----------- 追加输出
3. fstream（读写 或 清空重新写）
   - in|out ------------ 可读可写
   - int|out|trunc ----- 清空再读写
4. 附加标记
   - ate --------------- 初始文件指针位置位于结尾
   - binary ------------ 禁止系统转换

### std::ios_base和std::ios::out？

- std::ios_base是IO流的基类。
- std::base_ios == std::ios，ios是base_ios的别名。
- std::ios_base::openmode_mode是一个位掩码类型（BitmaskType）的数据
- std::ios::out等系列是某个具体的常量，0x01或0x02等
- std::ios::out也可以写成std::ios_base::out（直接从基类中取）

### ios流内的缓存

1. 所有io流，内部都维护两块缓存，读缓存和写缓存，分别维护对应的指针，

   - Get Area（读缓冲区）：维护三个指针：eback()（读区起点）、gptr()（当前读指针）、egptr()（读区终点）。
   - Put Area（写缓冲区）：维护pbase()（写区起点）、pptr()（当前写指针）、epptr()（写区终点）。
2. 其缓存大小是固定的，不会扩容，为8KB或其他系统推荐大小，BUFSIZ。
   可手动使用pubsetbuf()接管
   `file.rdbuf()->pubsetbuf(my_buffer, sizeof(my_buffer));`
   缓存会在读取或写入时向系统申请
3. C++ 标准强制规定：在同一个流上切换读写方向前，必须执行一次 seek 操作（或者 flush）。
   切换方向，即切换读写缓存
4. 为什么要 seek：因为 C++ 流为了性能使用了延迟写入和预读取，而seek 充当了“同步屏障”，强制把内存缓冲区里的脏数据落盘，并重置缓冲区的状态，从而保证两套独立指针背后的数据在物理层面是一致的。
5. 当你调用 seekg() 或 seekp() 时，底层 streambuf 会执行以下关键动作：

   - 强制刷新（Flush）：把 Put Area 里所有未决的写入数据，强制通过系统调用写入到真实的物理文件中。
   - 清空/重置：将 Get Area 和 Put Area 的状态重置，或者重新对齐指针，确保下一次操作时，流知道必须重新从物理文件获取最新数据，或者知道缓冲区已经失效。

### CPP本身无法判断文件是否被打开

CPP内部：必须使用互斥锁，或者close后再打开
外部：可以根据平台特性判断

### ofstream 和 ifstream 是 fstream 的语法糖/特定实现版本。

它们通过预置默认模式和限制接口访问权限，让代码变得更简洁、更安全、更易读。在实际开发中，除非你确实需要在一个流对象上频繁交替进行读写操作，否则永远应该优先使用 ifstream 或 ofstream

1. istream 特有：

   - 只暴露了 >>（提取运算符）、get()、getline()、read()、seekg()（Get 指针定位）等。它没有任何写入相关的公开接口。
   - istream 在读取时，如果遇到了文件末尾，会特有地设置 eofbit；如果读取的数据类型不匹配（比如要求读整数却读到了字母），会设置 failbit。
2. ostream 特有：

   - 只暴露了 <<（插入运算符）、put()、write()、flush()、seekp()（Put 指针定位）等。它没有任何读取相关的公开接口。
   - ostream 在写入时，如果底层设备（如磁盘）满了写不进去，会设置 badbit。
3. 还有默认绑定的cout，cin等
