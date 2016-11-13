cmake_minimum_required(VERSION 3.6)
project(tokenwizard)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -O0")

FIND_PACKAGE( Boost COMPONENTS system filesystem  REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
LINK_DIRECTORIES(convserv /usr/local/ssl/lib)
list(APPEND CMAKE_MODULE_PATH "")

file(GLOB SOURCE_FILES
        "*.h"
        "*.cpp"
        "*/*.h"
        "*/*.cpp"
        )

add_executable(tokenwizard ${SOURCE_FILES} ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES (tokenwizard ${Boost_LIBRARIES})