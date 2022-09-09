
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(evolutionary_algorithms src/main.cpp src/hill_climber.cpp src/benchmark_functions.cpp src/evolution_interface.cpp)

target_link_libraries(evolutionary_algorithms ${SDL2_LIBRARIES})
