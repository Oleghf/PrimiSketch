cmake_minimum_required(VERSION 3.10)

project(PrimiSketch LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(CMAKE_GENERATOR Ninja)

if (WIN32)
  set(QT_INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/qt-6.4-win/6.4.1/msvc2019_64")
  set(CMAKE_PREFIX_PATH ${QT_INSTALL_DIR})
  set(CMAKE_MAKE_PROGRAM "${CMAKE_CURRENT_SOURCE_DIR}/Tools/ninja.exe")
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

add_subdirectory("Source/Core/Include/Interfaces")
add_subdirectory("Source/GUI/")

set(main_target ${PROJECT_NAME})

add_executable(${main_target})

target_sources(${main_target}
  PRIVATE
    "Source/Main.cpp"
)

target_include_directories(${main_target} PRIVATE "Source")
target_link_libraries(${main_target}
  PRIVATE
    Qt6::Core
    Qt6::Widgets

    GUI
)

if (WIN32)
  set_target_properties(${main_target} PROPERTIES WIN32_EXECUTABLE TRUE)

  add_custom_command(TARGET ${main_target} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E chdir 
            $<TARGET_FILE_DIR:${main_target}> 
            "${QT_INSTALL_DIR}/bin/windeployqt.exe" 
            $<TARGET_FILE:${main_target}>
  )
  
  add_custom_target(DeployQtLibs ALL DEPENDS ${main_target})
endif()
