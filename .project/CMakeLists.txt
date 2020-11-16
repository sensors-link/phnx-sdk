# 不要修改此部分
cmake_minimum_required(VERSION 3.5)
set(TARGET fdm32vs10x)
include("$ENV{PHNX_SDF}/tools/cmake/project.cmake")

# 为工程添加文件，
# 可以使用通配符和文件列表指定方式, 也可混合使用
# 注意：添加/删除工程文件后，修改一下本文件才会重新扫描通配符指定的文件
file(GLOB_RECURSE PROJECT_SRCS "*.c") # 通配文件，递归
# set(PROJECT_SRCS "1.c" "2.c") # 文件列表指定
# set(PROJECT_SRCS ${PROJECT_SRCS} "1.S") # 混合使用

# 编译宏 -D XXX列表
set(PROJECT_DEFINITIONS "_DEBUG")

# 其他高级用法
# PROJECT_REQUIRES: 本工程依赖的通用组件
# set(PROJECT_REQUIRES "freertos")
# PROJECT_INCLUDEDIRS: 本工程依赖的通用组件
# set(PROJECT_INCLUDEDIRS "porting")
# PROJECT_LDSCRIPT: 自定义LDSCRIPT
# set(PROJECT_LDSCRIPT "flash.lds")
# CMAKE_C_FLAGS: 特别的编译参数CFLAGS
# set(CMAKE_C_FLAGS "-fPIE -pie")

# 最后调用project
project(app)
