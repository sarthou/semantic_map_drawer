cmake_minimum_required(VERSION 2.8.3)
project(semantic_route_drawer)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  ontologenius
)
find_package(ontologenius 0.1.3 REQUIRED)
find_package(OpenCV REQUIRED)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES semantic_route_drawer
  CATKIN_DEPENDS ontologenius roscpp
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
 include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${ontoloGenius_lib_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(semantic_drawer_lib
  src/MapReader.cpp
  src/MapDrawer.cpp
)
 target_link_libraries(semantic_drawer_lib ${catkin_LIBRARIES})
 add_dependencies(semantic_drawer_lib ${catkin_EXPORTED_TARGETS})
 target_link_libraries(semantic_drawer_lib ${OpenCV_LIBS})
 target_link_libraries(semantic_drawer_lib ontoloGenius_lib)

add_executable(semantic_drawer src/main.cpp)
target_link_libraries(semantic_drawer ${catkin_LIBRARIES})
add_dependencies(semantic_drawer ${catkin_EXPORTED_TARGETS})
target_link_libraries(semantic_drawer semantic_drawer_lib)
