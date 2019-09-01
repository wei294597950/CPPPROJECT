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
# cmake_minimum_required(VERSION 2.8)

# #项目名称    
# project(Demo3)

# #查找当前目录下的所有源文件
# #并将名称保存到 DIR_SRCS
# aux_source_directory(. DIR_SRCS)

# #添加math子目录
# add_subdirectory(math)

# #生成可执行文件demo
# add_executable(Demo ${DIR_SRCS})

# #加入一个配置头文件，用于处理cmake  对源码的设置
# configure_file(
#     "${PROJECT_SOURCE_DIR}/config.h.in"
#     "${PROJECT_BINARY_DIR}/config.h"
# )


# #添加链接库
# target_link_libraries(Demo Mathlink)

# #支持gdb
# set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
# set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")



### 自定义编译选项 ###
cmake_minimum_required(VERSION 2.8)

#项目名称    
project(Demo3)



#加入一个配置头文件，用于处理cmake  对源码的设置
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)

#是否使用自己的math power库
option(USE_MYMATH
        "use provided math implementation" ON)


if(USE_MYMATH)
    include_directories("${PROJECT_SOURCE_DIR}/math")
    add_subdirectory(math)
    set(EXTRA_LIBS ${EXTRA_LIBS} Mathlink)  
endif(USE_MYMATH)

#支持gdb
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")


#查找当前目录下的所有源文件
#并将名称保存到 DIR_SRCS
aux_source_directory(. DIR_SRCS)

#生成可执行文件demo
add_executable(Demo ${DIR_SRCS})

target_link_libraries(Demo ${EXTRA_LIBS})

#指定安装路径
install(TARGETS Demo DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include)


#启用测试
enable_testing()

#测试程序是否成功运行
add_test(test_run Demo 5 2)

# #测试帮助信息是否可以正常提示
# add_test(test_usage Demo)
# set_tests_properties(test_usage 
#     PROPERTIES PASS_REGULAR_EXPRESSION "Usage : .* base exponent") 

# 测试 5 的平方
add_test(test_5_2 Demo 5 2)
set_tests_properties (test_5_2
 PROPERTIES PASS_REGULAR_EXPRESSION "is 25")

# 测试 10 的 5 次方
add_test(test_10_5 Demo 10 5)
set_tests_properties (test_10_5
 PROPERTIES PASS_REGULAR_EXPRESSION "is 100000")

# 测试 2 的 10 次方
add_test(test_2_10 Demo 2 10)
set_tests_properties (test_2_10
 PROPERTIES PASS_REGULAR_EXPRESSION "is 1024")

 # 构建一个 CPack 安装包
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE
  "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${Demo_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Demo_VERSION_MINOR}")
include(CPack)
# 生成二进制安装包：
# cpack -C CPackConfig.cmake

# 生成源码安装包
# cpack -C CPackSourceConfig.cmake

#sh Demo3-1.0.1-Linux.sh
