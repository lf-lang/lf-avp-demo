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

template <typename ServiceT, typename ValueT>
auto create_future_from_service(std::shared_ptr<ValueT> ros_service_msg) {
    // The following is how ROS 2 creates a future for a client of a service
    using SharedResponse = typename ServiceT::Response::SharedPtr;
    using Promise = std::promise<SharedResponse>;
    using SharedPromise = std::shared_ptr<Promise>;
    using SharedFuture = std::shared_future<SharedResponse>;
    SharedPromise promise = std::make_shared<Promise>();
    SharedFuture future(promise->get_future());
    SharedResponse response = std::make_shared<typename ServiceT::Response>();
    response->map = *ros_service_msg.get();
    promise->set_value(response);
    return future;
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

template <typename T>
void* spin_node(void* args) {
	auto node_shared_ptr_ptr = static_cast<T*>(args);
	auto node_shared_ptr = *node_shared_ptr_ptr;
	while (rclcpp::ok()) {
		rclcpp::spin(node_shared_ptr);
	}
	delete node_shared_ptr_ptr;
	return 0;
}

#endif // XRONOS_UTILS_HPP
