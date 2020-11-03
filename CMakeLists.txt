
set(STARTUP_SRCS "env/init.c" "env/system_phnx02.c" "env/entry.S" "env/start.S")
file(GLOB DRIVER_SRCS "drivers/*.c")
file(GLOB STUBS  "stubs/*.c")
set(COMPONENT_SRCS ${DRIVER_SRCS} ${STARTUP_SRCS} ${STUBS})
set(COMPONENT_ADD_INCLUDEDIRS "include drivers")

register_component()

# 链接本库的依赖
target_link_directories(${COMPONENT} PUBLIC "env")
target_link_libraries(${COMPONENT} "-T phnx02_flash.lds")
