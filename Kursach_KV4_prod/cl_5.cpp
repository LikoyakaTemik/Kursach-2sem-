#include "cl_base.h"
#include "cl_5.h"
#include <iostream>

/*
!!!Описания методов смотреть в cl_5.h!!!
*/

cl_5::cl_5(cl_base* p_head_object, std::string s_object_name) :cl_base(p_head_object, s_object_name) {}

void cl_5::signal_f(std::string& command) {
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

void cl_5::handler_f(std::string command) {
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

cl_5::~cl_5() {}