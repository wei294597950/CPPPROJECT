aux_source_directory(. DIRS)

#生成链接库
add_library(Mathlink ${DIRS})

#制定 Mathlink 库的安装路径
install(TARGETS Mathlink DESTINATION bin)
install(TARGETS Mathlink DESTINATION include)


