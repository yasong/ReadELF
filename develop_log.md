# development log

##### 2017.05.22 由于需要理解ELF文件的格式，开始考虑开发一个读取分析ELF文件格式的程序，以加深对ELF文件的理解，参考文档为：Executable and Linkable Format (ELF)，ortable Formats Specification, Version 1.1和《ELF 文件格式分析》滕启明。开始设计基本的读取思路，以及实现各种类型和结构体的定义。
##### 2017.05.23 开始设计命令以及参数的定义和实现。并能够读取解析ELF文件的头部以及程序头部表
##### 2017.05.23 开始实现读取ELF区块头部，并解析出结果。
