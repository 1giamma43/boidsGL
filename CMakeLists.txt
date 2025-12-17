cmake_minimum_required(VERSION 3.16)
project(progetto_boid)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =========================
# Libreria
# =========================
add_library(boidlib
    src/boid.cpp
    src/flock.cpp
    src/velox.cpp
    src/options.cpp
)

target_include_directories(boidlib PUBLIC src)

# =========================
# Eseguibile
# =========================
add_executable(progetto_b
    src/main.cpp
)

target_link_libraries(progetto_b PRIVATE boidlib)

# =========================
# SFML
# =========================
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

target_link_libraries(progetto_b
    PRIVATE
        sfml-system
        sfml-window
        sfml-graphics
)

# =========================
# Test
# =========================
enable_testing()
add_subdirectory(tests)