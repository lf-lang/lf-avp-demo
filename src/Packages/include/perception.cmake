unset(BUILD_TESTING)

set(AUTOWARE_HOME $ENV{AUTOWARE_HOME})
message(STATUS "Using ${AUTOWARE_HOME} as Autoware's home directory")

find_package(euclidean_cluster_nodes REQUIRED)
find_package(off_map_obstacles_filter_nodes REQUIRED)

include_directories(${AUTOWARE_HOME}/src/perception/segmentation/euclidean_cluster_nodes/include/euclidean_cluster_nodes)
include_directories(${AUTOWARE_HOME}/src/perception/filters/off_map_obstacles_filter_nodes/include/off_map_obstacles_filter_nodes/)

ament_target_dependencies( ${LF_MAIN_TARGET} euclidean_cluster_nodes off_map_obstacles_filter_nodes)
