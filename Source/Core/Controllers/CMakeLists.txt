# Статическая библиотека контроллеров
set(controllers_static_lib_name "Controllers")

# Цель сборки - статическая библиотека
add_library(${controllers_static_lib_name} STATIC)

# Указываем какие файлы необходимо включить в цель сборки.
target_sources(${controllers_static_lib_name} PRIVATE
"CommandManager.cpp"
"MainController.cpp"
 "CreateLineSegmentState.h" "CreateLineSegmentState.cpp" "CreateFigureCommand.h" "CreateFigureCommand.cpp" "DefaultState.h" "DefaultState.cpp" "PaintController.h" "PaintController.cpp"  )

# Указываем подключенные директории
target_include_directories(${controllers_static_lib_name} PUBLIC
"${CMAKE_SOURCE_DIR}/Source/Core/Controllers/"
)

# Указываем библиотеки для линковки
target_link_libraries(${controllers_static_lib_name} PUBLIC
Interfaces
Events
)