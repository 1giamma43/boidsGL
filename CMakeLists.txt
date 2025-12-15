cmake_minimum_required(VERSION 3.16)
project(progetto_b)

set(CMAKE_CXX_STANDARD 17)

# Dì a CMake dove trovare SFML (su Windows cambia il percorso)
set(SFML_DIR "C:/gianmarco_salerno884/programmazione/progetto_b/SFML")

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_executable(progetto_b main.cpp options.cpp flock.cpp boid.cpp velox.cpp options.hpp flock.hpp boid.hpp velox.hpp)

target_link_libraries(progetto_b sfml-system sfml-window sfml-graphics)
