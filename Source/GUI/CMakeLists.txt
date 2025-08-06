# Статическая библиотека
set(gui_static_lib_name "GUI")

# Цель сборки - статическая библиотека
add_library(${gui_static_lib_name} STATIC)

# Указываем какие файлы необходимо включить в цель сборки.
target_sources(${gui_static_lib_name} PRIVATE
"QtView.cpp" "SceneWidget.h" "SceneWidget.cpp" "PropertiesPanelWidget.h" "../Core/Include/Interfaces/StyleLine.h" "EditorToolBar.h" "EditorToolBar.cpp")

# Указываем подключенные директории
target_include_directories(${gui_static_lib_name} PUBLIC
"${CMAKE_SOURCE_DIR}/Source/GUI"
)

# Указываем библиотеки для линковки
target_link_libraries(${gui_static_lib_name} PUBLIC
Qt6::Core
Qt6::Widgets

Interfaces
)
