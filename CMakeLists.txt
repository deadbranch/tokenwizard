cmake_minimum_required(VERSION 3.6)
project(tokenwizard)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -O0")

#list(APPEND CMAKE_MODULE_PATH "FindTBB.cmake")
#find_package(TBB COMPONENTS tbbmalloc tbbmalloc_proxy tbb_preview)

FIND_PACKAGE( Boost COMPONENTS system filesystem  REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} "/work/")
LINK_DIRECTORIES(convserv /usr/local/ssl/lib)
list(APPEND CMAKE_MODULE_PATH "")

file(GLOB SOURCE_FILES
        "*.h"
        "*.cpp"
        "*/*.h"
        "*/*.cpp"
        )

add_executable(tokenwizard ${SOURCE_FILES} ${Boost_LIBRARIES} HandlerSelector.h CommandHandler.h CommandHandlers/GetTokenCommandHandler.cpp CommandHandlers/GetTokenCommandHandler.h CommandHandlers/GenTokenCommandHandler.cpp CommandHandlers/GenTokenCommandHandler.h Worker.h serialization/PacketBuffer.h serialization/StaticPacket.h)
TARGET_LINK_LIBRARIES (tokenwizard ${Boost_LIBRARIES})