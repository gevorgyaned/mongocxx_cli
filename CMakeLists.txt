cmake_minimum_required(VERSION 3.12)
project(MyMongoCXXProject)
set(CMAKE_CXX_STANDARD 20)
find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)
add_executable(MyMongoCXXApp main.cpp db.cpp)
target_include_directories(MyMongoCXXApp PRIVATE ${MONGOCXX_INCLUDE_DIRS})
target_link_libraries(MyMongoCXXApp PRIVATE ${LIBMONGOCXX_LIBRARIES})
include_directories(${LIBMONGOCXX_INCLUDE_DIRS})
include_directories(${LIBBSONCXX_INCLUDE_DIRS})
