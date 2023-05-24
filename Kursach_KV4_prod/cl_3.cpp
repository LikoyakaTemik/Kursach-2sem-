#include "cl_base.h"
#include "cl_3.h"
#include <iostream>
cl_3::cl_3(cl_base* p_head_object, std::string s_object_name) :cl_base(p_head_object, s_object_name) {}

void cl_3::signal_f(std::string& command) {
	std::string absolute_coordinate;
	if (get_p_head_object()) {
		absolute_coordinate = get_p_head_object()->get_p_absolute_coordinate(get_s_object_name());
	}
	else {
		absolute_coordinate = "/" + get_s_object_name();
	}
	std::cout << "Signal from " << absolute_coordinate << '\n';
	command = command + " (class: " + char(get_num() + 48) + ')';
	return;
}

void cl_3::handler_f(std::string command) {
	std::string absolute_coordinate;
	if (get_p_head_object()) {
		absolute_coordinate = get_p_head_object()->get_p_absolute_coordinate(get_s_object_name());
	}
	else {
		absolute_coordinate = "/" + get_s_object_name();
	}
	std::cout << "Signal to " << absolute_coordinate << " Text:  " << command << '\n';
	return;
}

cl_3::~cl_3() {}