# ####  多个源文件   #####

# #最低版本
# cmake_minimum_required(VERSION 2.8)

# #项目名称    
# project(Demo1)

# #查找当前目录下的所有源文件
# #并将名称保存到 DIR_SRCS
# aux_source_directory(. DIR_SRCS)

# #生成可执行文件demo
# add_executable(Demo ${DIR_SRCS})


###   多文件 多目录   ###
#最低版本
cmake_minimum_required(VERSION 2.8)

#项目名称    
project(Demo3)

#查找当前目录下的所有源文件
#并将名称保存到 DIR_SRCS
aux_source_directory(. DIR_SRCS)

#添加math子目录
add_subdirectory(math)

#生成可执行文件demo
add_executable(Demo ${DIR_SRCS})

#添加链接库
target_link_libraries(Demo Mathlink)

#支持gdb
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")