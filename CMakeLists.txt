cmake_minimum_required(VERSION 3.9)
project(aquarius)

set(CMAKE_CXX_STANDARD 11)

set(BOOST_ROOT /usr/local/Cellar/boost/1.66.0)

find_package(Boost REQUIRED COMPONENTS thread)
#if (${Boost_FOUND})
#    message(${Boost_LIBRARY_DIRS})
#    message(${Boost_INCLUDE_DIRS})
#endif()
# find a list of Python's versions base on 3.6
set(Python_ADDITIONAL_VERSIONS 3.6)
find_package(PythonLibs 3 REQUIRED)
#if (${PythonLibs_FOUND})
#    message(${PYTHON_LIBRARIES})
#    message(${PYTHON_INCLUDE_DIR})
#endif()
include_directories(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIR})
add_executable(aquarius
        main.cpp)
add_executable(mojo mojo.cc)
target_link_libraries(aquarius ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})