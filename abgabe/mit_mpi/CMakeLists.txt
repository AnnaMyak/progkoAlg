cmake_minimum_required(VERSION 2.8)
PROJECT(test)
find_package( OpenCV REQUIRED )
ADD_EXECUTABLE(test main.cpp)
SET(CMAKE_C_COMPILER mpicc)
SET(CMAKE_CXX_COMPILER mpicxx)
target_link_libraries(test mpi)
target_link_libraries(test ${OpenCV_LIBS}) 


