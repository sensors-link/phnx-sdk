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
set(PROJECT_DEFINITIONS "_DEBUG" "PHNX_DEMO")

# 最后调用project
project(app)
