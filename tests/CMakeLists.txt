add_executable(tests_boid
    tests.cpp
)

target_include_directories(tests_boid PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
)


target_link_libraries(tests_boid
    boidlib
    sfml-graphics
    sfml-window
    sfml-system
)

add_test(
    NAME BoidTests
    COMMAND tests_boid
)