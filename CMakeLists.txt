cmake_minimum_required(VERSION 3.15)

project("RconServer")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    endstone
    GIT_REPOSITORY https://github.com/EndstoneMC/endstone.git
    GIT_TAG v0.10 
)
FetchContent_MakeAvailable(endstone)

FetchContent_Declare(
    boost
    URL https://archives.boost.io/release/1.89.0/source/boost_1_89_0.tar.gz
)
FetchContent_MakeAvailable(boost)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(nlohmann_json)

file(GLOB_RECURSE SRC_FILES
    "src/*.cpp"
    "src/*.h"
)

endstone_add_plugin(
    ${PROJECT_NAME}
    ${SRC_FILES}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${boost_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)