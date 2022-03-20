#ifndef XRONOS_CONSTANTS_HPP
#define XRONOS_CONSTANTS_HPP

#include <string>

// Paths within the AUTOWARE_HOME directory
const std::string LAUNCH_PARAM_PATH = "src/launch/autoware_auto_launch/param";
const std::string AVP_DEMO_PARAM_PATH = "src/tools/autoware_auto_avp_demo/param/";

// Launch parameters
const std::string PC_FILTER_TRANSFORM_PARAM = "point_cloud_filter_transform.param.yaml";
const std::string MPC_CONTROLLER_PARAM = "mpc_sim.param.yaml";
const std::string BEHAVIOR_PLANNER_PARAM = "behavior_planner.param.yaml";

// AVP Demo parameters
const std::string EUCLIDEAN_CLUSTER_DETECTOR_PARAM = "euclidean_cluster.param.yaml";
const std::string LANE_PLANNER_PARAM = "lane_planner.param.yaml";
const std::string LANELET2_MAP_PROVIDER_PARAM = "lanelet2_map_provider.param.yaml";
const std::string NDT_LOCALIZER_PARAM = "ndt_localizer.param.yaml";
const std::string NDT_MAP_PUBLISHER_PARAM = "map_publisher.param.yaml";
const std::string OFF_MAP_OBSTACLES_FILTER_PARAM = "off_map_obstacles_filter.param.yaml";
const std::string OBJ_COLLISION_EST_PARAM = "object_collision_estimator.param.yaml";


#endif // XRONOS_CONSTANTS_HPP