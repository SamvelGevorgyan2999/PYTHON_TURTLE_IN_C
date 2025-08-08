cmake_minimum_required(VERSION 3.10)
project(PYTHON_TURTLE_IN_C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(myturtle
    main.c
    turtle.c
)

target_link_libraries(myturtle ${SDL2_LIBRARIES})
