cmake_minimum_required(VERSION 3.25)
project(CPP_POOL)

set(CMAKE_CXX_STANDARD 14)
set(SFML_DIR "${CMAKE_SOURCE_DIR}/libs/sfml")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_subdirectory(libs/sfml)
include_directories(libs/sfml/include)

include_directories(
        include
        src/game
        src/system
        src/common
        src/common/Components
        src/common/Components/Utils
)

file(GLOB_RECURSE SOURCES
        "src/*.cpp"
        "src/game/*.cpp"
        "src/system/*.cpp"
        "src/common/**/*.cpp"
)

add_executable(game
        ${SOURCES}
)

add_library(CommonLib STATIC ${SOURCES})

target_include_directories(game PRIVATE
        include
        src/system
        src/common
        src/game
)

target_link_libraries(game PRIVATE CommonLib)
target_link_libraries(game PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
