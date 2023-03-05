project(cpp_db)
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(${PROJECT_SOURCE_DIR}/external/nlohmann_json)

file(GLOB SOURCES sources/*.cpp)
file(GLOB HEADERS headers/*.hpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
