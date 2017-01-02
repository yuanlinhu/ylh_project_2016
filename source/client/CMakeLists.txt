#CMAKE_MINIMUN_REQUIRED(VERSION 2.8)
PROJECT(Hello)

SET(SRC_LIST server.cpp)

#SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/module${CMAKE_MODULE_PATH})

link_libraries(event)

add_executable(libevent_s ${SRC_LIST})

#ADD_SUBDIRECTORY(src)
