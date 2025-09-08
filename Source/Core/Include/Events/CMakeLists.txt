# Статическая библиотека ивентов
set(events_static_library "Events")

# Цель сборки - библиотека ивентов
add_library(${events_static_library} STATIC)

# Указываем какие файлы необходимо включить в цель сборки.
target_sources(${events_static_library} PRIVATE
"SceneMouseEvent.cpp"
 "LoadFileEvent.h" "SaveFileEvent.h" "UndoEvent.h" "RedoEvent.h" "ExportSVGEvent.h" "ToolChangeEvent.h")

# Указываем подключенные директории
target_include_directories(${events_static_library} PUBLIC
"${CMAKE_SOURCE_DIR}/Source/Core/Include/Events/"
)

# Указываем библиотеки для линковки
target_link_libraries(${events_static_library} PUBLIC
Geometry
)
