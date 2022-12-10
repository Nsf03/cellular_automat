cmake_minimum_required(VERSION 3.23)
project(cellular_automata)
set(CMAKE_CXX_STANDARD 14)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(MY_LIB Grid.h SFML_export.h lib.cpp)
set(SOURCE main.cpp)
add_library(rules STATIC ${MY_LIB})
add_executable(main ${SOURCE})



set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
include_directories(C:/SFML/include)
target_link_libraries(main sfml-system sfml-window sfml-graphics sfml-audio rules)


#В библиотеки грид и клетку и все сверху
#Оформить main который сравнивает результат с эталоном - является приложением среди библиотек будет main