# Библиотека интерфейсов
set(interface_static_lib_name "Interfaces")

# Цель сборки - библиотека интерфейсов
add_library(${interface_static_lib_name} STATIC)

# Указываем подключенные директории
target_include_directories(${interface_static_lib_name} PUBLIC
"${CMAKE_SOURCE_DIR}/Source/Core/Include/Interfaces"
)