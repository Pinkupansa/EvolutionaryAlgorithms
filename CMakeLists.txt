
project(EvolutionaryAlgorithms)
cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 11)

# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cmake/matplotplusplus)
# Add all c source files under the src directory
file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# Add all headers files under the include directory
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Add SDL2 library
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Main)

# Add SDL2_image library
#find_package(SDL2_image REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::Image)

# Add SDL2_ttf library
find_package(SDL2_ttf REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::TTF)

# Add SDL2_net library
#find_package(SDL2_net REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::Net)

# Add SDL2_mixer library
#find_package(SDL2_mixer REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::Mixer)

# Add SDL2_gfx library
find_package(SDL2_gfx REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::GFX)

target_link_libraries(${PROJECT_NAME} matplot)

#boost graph
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS graph) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()

#compile a library called EAL
add_library(EAL STATIC ${SOURCES})

#remove main.cpp
set_target_properties(EAL PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(EAL PUBLIC include)
target_link_libraries(EAL matplot)
target_link_libraries(EAL SDL2::Main)
target_link_libraries(EAL SDL2::TTF)
target_link_libraries(EAL SDL2::GFX)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(EAL ${Boost_LIBRARIES})
endif()

#add compiler optimization flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

#add a test executable for xoroshiro
add_executable(xoroshiro_test test/xoroshiro_test.cpp src/xoroshiro_generator.cpp)
target_include_directories(xoroshiro_test PUBLIC include)
target_link_libraries(xoroshiro_test matplot)