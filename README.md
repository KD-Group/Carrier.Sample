# Carrier.Sample

[![Build status](https://ci.appveyor.com/api/projects/status/b5bhppulnj3kiyhq?svg=true)](https://ci.appveyor.com/project/Wingsgo/carrier-sample-ll7i4)


High speed acquisition card program for carrier && single && highlight 

## Pre-requiests
thrift依赖boost库(required)，openssl库(option)与libevent库(option)，对于libthrift只依赖于boost库, libthriftnb则均依赖，因此在编译libthrift时，要将TSSLSocker.h/cpp排除出项目, 

## 编译步骤, 以下文件均放在C:\为例
1. 下载[thrift0.10.0](https://github.com/apache/thrift/releases/tag/0.10.0)
2. 下载[boost_1.53.0](https://sourceforge.net/projects/boost/files/boost/1.53.0/)
3. 下载[openssl_1.0.2](https://sourceforge.net/projects/openssl/)
3. 编译boost, 进入C:\boost_1_53_0 运行bootstrap.bat批处理文件, 生成编译工具b2.exe与bjam.exe
4. 编译boost指定组件，`bjam.exe --toolset=msvc-10.0 architecture=x86 address-model=64 link=static --build-type=complete --with-system --with-thread --with-date_time --with-filesystem --with-serialization --with-atomic --with-chrono` 编译生成的头文件与库文件目录分别为`C:\boost`与`C:\stage`
5. 打开`C:\thrift-0.10.0\lib\cpp\thrift.sln`文件，进入visual studio 2010
6. 打开libthrift项目->属性->C/C++->常规->附加包含目录, 添加头文件路径`C:\boost_1_53_0`与`C:\openssl-1.0.2c-x86\include`
7. 开始执行编译，生成后的库文件在`C"\thrift-0.10.0\lib\cpp\x64\Release\libthrift.lib`
8. 将thrift文件夹与boost_1_53_0放置在`C:\Carrier.Sample\include`文件夹中, 将libthrift.lib放置在`C:\Carrier.Sample\lib`中，并在SConstruct中指定头文件与库文件路径, 执行scons命令，完成编译
