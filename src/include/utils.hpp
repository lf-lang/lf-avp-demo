#ifndef XRONOS_UTILS_HPP
#define XRONOS_UTILS_HPP

#include "rclcpp/parameter_map.hpp"
#include "rcl_yaml_param_parser/parser.h"
#include <string>
#include <cstdlib>

inline rclcpp::NodeOptions get_node_options_from_yaml(const char* path, const char* root_name) {
	// Use a try - catch for now so that if the rclcpp context is already initialized,
	// ROS doesn't throw a tantrum.
	try {
		rclcpp::init(0, NULL);
	} catch (...) { /*  Ignore */ }
	rclcpp::NodeOptions nodeOptions;
	rcl_params_t* params = rcl_yaml_node_struct_init(rcl_get_default_allocator());
	bool out = rcl_parse_yaml_file(path,params);
	if (!out) {
		error_print_and_exit("Failed to load the yaml file.");
	}

	auto options = rclcpp::parameter_map_from(params);
	for (std::pair<const std::__cxx11::basic_string<char>, std::vector<rclcpp::Parameter> > option : options) {
		// std::cout << option.first << std::endl;
		// std::cout << option.second << std::endl;
		if (option.first == root_name) {
			nodeOptions.parameter_overrides() = option.second;
		}
	}

	return nodeOptions;
}

inline rclcpp::NodeOptions get_node_options_from_yaml(const char* path, const char* root_name, int argc, char *argv[]) {
	try {
		rclcpp::init(argc, argv);
	} catch (...) { /*  Ignore */ }
	return get_node_options_from_yaml(path, root_name);
}

std::string get_autoware_home() {
	const char* autoware_home = std::getenv("AUTOWARE_HOME");
	if (!autoware_home) {
		error_print_and_exit("ERROR: Environment variable $AUTOWARE_HOME is not declared.");
	}
	return std::string(autoware_home);
}

std::string get_xronos_home() {
	const char* xronos_home = std::getenv("XRONOS_HOME");
	if (!xronos_home) {
		error_print_and_exit("ERROR: Environment variable $XRONOS_HOME is not declared.");
	}
	return std::string(xronos_home);
}

#endif // XRONOS_UTILS_HPP
