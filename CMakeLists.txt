SET(PROJECT_NAME image_node)
cmake_minimum_required(VERSION 2.8.3)
project(${PROJECT_NAME})
SET(CMAKE_BUILD_TYPE Release) # Release, RelWithDebInfo

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
  std_msgs
  tf
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")


find_package(OpenCV 3.4 REQUIRED)
find_package(Eigen3 3 REQUIRED)

set(LIBS
        ${OpenCV_LIBS}
        ${EIGEN3_LIBS}
        ${catkin_LIBRARIES}
        )

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES imagePublisher
  CATKIN_DEPENDS cv_bridge image_transport  roscpp sensor_msgs std_msgs tf

)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable(publisher src/main_pub.cpp)
target_link_libraries(publisher
        ${LIBS}
#        ${catkin_LIBRARIES}
        )


add_executable(subscriber src/main_sub.cpp)
target_link_libraries(subscriber
        ${LIBS}
        #        ${catkin_LIBRARIES}
        )