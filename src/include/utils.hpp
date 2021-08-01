#ifndef XRONOS_UTILS_HPP
#define XRONOS_UTILS_HPP

#include "rclcpp/parameter_map.hpp"
#include "rcl_yaml_param_parser/parser.h"

inline rclcpp::NodeOptions get_node_options_from_yaml(string path, string root_name) {
	// Use a try - catch for now so that if the rclcpp context is already initialized,
	// ROS doesn't throw a tantrum.
	try {
		rclcpp::init(0, NULL);
	} catch (...) { /*  Ignore */ }
	rclcpp::NodeOptions nodeOptions;
	rcl_params_t* params = rcl_yaml_node_struct_init(rcl_get_default_allocator());
	bool out = rcl_parse_yaml_file(
		path,
		params
	);

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

inline rclcpp::NodeOptions get_node_options_from_yaml(string path, string root_name, int argc, char *argv[]) {
	try {
		rclcpp::init(argc, argv);
	} catch (...) { /*  Ignore */ }
	return get_node_options_from_yaml(path, root_name);
}

#endif // XRONOS_UTILS_HPP
