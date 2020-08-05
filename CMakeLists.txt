cmake_minimum_required(VERSION 3.16)
project(PointCloud)

set(CMAKE_CXX_STANDARD 14)

add_executable(PointCloud main.cpp)

#eigen3
include_directories(/usr/include/eigen3)

#pcl
find_package(PCL REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

#laslib
include_directories(/home/zzw/opt/lastools/LASlib/inc /home/zzw/opt/lastools/LASzip/src)
link_directories(/home/zzw/opt/lastools/LASlib/lib/)
#link_directories(${LASLIB_LIBRARY_DIRS})

target_link_libraries(PointCloud ${PCL_LIBRARIES} ${LASLIB_LIBRARIES} /home/zzw/opt/lastools/LASlib/lib/liblas.a)

