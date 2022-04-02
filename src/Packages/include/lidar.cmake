unset(BUILD_TESTING)

set(CMAKE_BUILD_TYPE Debug)

set(AUTOWARE_HOME $ENV{AUTOWARE_HOME})
message(STATUS "Using ${AUTOWARE_HOME} as Autoware's home directory")

find_package(autoware_auto_msgs REQUIRED)
find_package(lidar_utils REQUIRED)
find_package(yaml_cpp_vendor REQUIRED)
find_package(tf2 REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(point_cloud_filter_transform_nodes REQUIRED)
find_package(point_cloud_fusion_nodes REQUIRED)
find_package(voxel_grid_nodes REQUIRED)
find_package(ray_ground_classifier_nodes REQUIRED)

include_directories(${AUTOWARE_HOME}/src/perception/filters/point_cloud_filter_transform_nodes/include/point_cloud_filter_transform_nodes)
include_directories(${AUTOWARE_HOME}/src/common/lidar_utils/include/)
include_directories(${AUTOWARE_HOME}/src/common/autoware_auto_common/include)
include_directories(${AUTOWARE_HOME}/src/common/autoware_auto_geometry/include)
include_directories(${AUTOWARE_HOME}/src/perception/filters/point_cloud_filter_transform_nodes/include/)
include_directories(${AUTOWARE_HOME}/src/perception/filters/point_cloud_fusion_nodes/include/point_cloud_fusion_nodes)
include_directories(${AUTOWARE_HOME}/src/perception/filters/voxel_grid_nodes/include/voxel_grid_nodes)
include_directories(${AUTOWARE_HOME}/src/perception/filters/ray_ground_classifier_nodes/include/ray_ground_classifier_nodes)

ament_target_dependencies( ${LF_MAIN_TARGET} std_msgs sensor_msgs point_cloud_filter_transform_nodes point_cloud_fusion_nodes voxel_grid_nodes ray_ground_classifier_nodes)
