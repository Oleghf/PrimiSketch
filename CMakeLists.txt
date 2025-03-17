# Явно устанавливаем нужную версию cmake для совместимости
cmake_minimum_required(VERSION 3.22)

# Указываем название проекта
project("StudentInternship" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20) # Задаем глобально стандарт С++
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Запрещаем автоматически снижать стандарт
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Экспорт команд компиляции для некоторых
                                      # IDE

# Подключаем другие CMakeLists
add_subdirectory("Source/Geometry")
add_subdirectory("Source/Application")
