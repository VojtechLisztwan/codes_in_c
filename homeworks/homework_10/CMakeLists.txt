cmake_minimum_required(VERSION 3.4)

project(snowflake)

# Nastavení C standardu na C99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Přidání přepínačů překladače
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")

add_executable(snowflakes main.c sdl.c dynamic_array.c)

target_link_libraries(snowflakes SDL2 SDL2_image)
