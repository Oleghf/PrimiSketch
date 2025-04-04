# Подпроект со статической библиотекой

# Чтобы избежать дублирования и упростить потенциальное переименование создаем
# переменную с названием цели сборки и одновременно с названием исполняемого
# файла, так как оно не задано явно. Расширение будет добавлено автоматически.
set(geometry_target_name "Geometry")

# Создаем цель сборки - статическая библиотека
add_library(${geometry_target_name} STATIC)

# Указываем какие файлы необходимо включить в цель сборки. PRIVATE - относится
# только к текущей цели для сборки.
target_sources(${geometry_target_name} PRIVATE "IFigure.h" "Point.h" "Point.cpp" "Vector.h" "Vector.cpp" "LineSegment.h" "LineSegment.cpp" "MathUtils.h" "Rectangle.h" "Rectangle.cpp" "BrokenLine.h" "BrokenLine.cpp" "Box.h" "Box.cpp" "MathUtils.cpp")

# Указываем подключаемые директории - директория с текущим CMakeLists. PUBLIC -
# директория будет подключена к данной цели сборки и ко всем, которые подключают
# эту библиотеку.
target_include_directories(${geometry_target_name}
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
