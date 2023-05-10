#include "cl_base.h"
#include <iostream>
#include <vector>
#include <cmath>

cl_base::cl_base(cl_base* p_head_object, std::string s_object_name) {
	this->p_head_object = p_head_object;
	this->s_object_name = s_object_name;
	if (p_head_object) {
		p_head_object->subordinate_objects.push_back(this);
	}
}

bool cl_base::set_s_object_name(std::string s_object_name) {
	if (p_head_object) {
		for (int i = 0; i < p_head_object->subordinate_objects.size(); ++i) {
			if (p_head_object->subordinate_objects[i]->s_object_name == s_object_name) {
				return false;
			}
		}
		this->s_object_name = s_object_name;
		return true;
	}
	else {
		this->s_object_name = s_object_name;
		return true;
	}
}

void cl_base::set_state(std::string state) {
	int state_int = 0;
	for (int i = 0; i < state.size(); ++i) {
		state_int = state_int + (int(state[i]) - 48) * pow(10, state.size() - i - 1);
	}

	if (state_int == 0) {
		this->state = 0;
		for (int i = 0; i < subordinate_objects.size(); ++i) {
			subordinate_objects[i]->set_state(0);
		}
	}
	else {
		if (is_state_before()) {
			this->state = state_int;
		}
	}
}

bool cl_base::is_state_before() {
	cl_base* pointer = get_p_head_object();
	
	if (pointer != nullptr) {
		if (pointer->state != 0) {
			//cout << "test1: \n";
			return true;
		}
		else {
			return false;
		}
	}
	else{
		//std::cout << this << " test2: \n";
		return true;
	}
}

bool cl_base::is_correct_type(std::string type) {
	int type_int = 0;
	for (int i = 0; i < type.size(); ++i) {
		type_int = type_int + (int(type[i]) - 48) * pow(10, type.size() - i - 1);
	}
	if (type_int >= 2 && type_int <= 6) {
		return true;
	}
	else {
		return false;
	}
}

bool cl_base::is_uniq_name(std::string name) {
	for (int i = 0; i < subordinate_objects.size(); ++i) {
		if (subordinate_objects[i]->get_s_object_name() == name) {
			return false;
		}
		else {
			subordinate_objects[i]->is_uniq_name(name);
		}
	}
	return true;
}

bool cl_base::is_global_uniq_name(std::string name) {
	cl_base* pointer_object = this;
	while (pointer_object->get_p_head_object() != nullptr) {
		pointer_object = pointer_object->get_p_head_object();
	}

	return pointer_object->is_uniq_name(name);
}

std::string cl_base::get_s_object_name() {
	return s_object_name;
}

cl_base* cl_base::get_p_head_object() {
	return p_head_object;
}

std::string cl_base::get_state() {
	if (state != 0) {
		return "is ready";
	}
	else {
		return "is not ready";
	}
}

void cl_base::print_s_object_name_tree() {
	int lvl = 1;
	cl_base* pointer_object = this;
	std::vector <cl_base*> ordinate_objects;
	while (pointer_object->p_head_object != nullptr) {
		ordinate_objects.push_back(pointer_object);
		pointer_object = pointer_object->p_head_object;
	}

	std::cout << pointer_object->get_s_object_name() << '\n';

	while (pointer_object != this) {
		for (int i = 0; i < pointer_object->subordinate_objects.size(); ++i) {
			for (int blank = 0; blank < lvl * 4; ++blank) {
				std::cout << ' ';
			}
			std::cout << pointer_object->subordinate_objects[i]->get_s_object_name() << '\n';
		}
		pointer_object = ordinate_objects[ordinate_objects.size() - lvl];
		lvl++;
	}

	for (int i = 0; i < pointer_object->subordinate_objects.size(); ++i) {
		for (int blank = 0; blank < lvl * 4; ++blank) {
			std::cout << ' ';
		}
		std::cout << pointer_object->subordinate_objects[i]->get_s_object_name() << '\n';
	}
}

cl_base* cl_base::get_p_child(std::string child_name) {
	for (int i = 0; i < subordinate_objects.size(); ++i) {
		if (subordinate_objects[i]->get_s_object_name() == child_name) {
			return subordinate_objects[i];
		}
	}
	return nullptr;
}

cl_base* cl_base::get_p_from_this_hierarchy(std::string finding_name) {
	cl_base* ptr_child = get_p_child(finding_name);
	if (ptr_child != nullptr) {
		return ptr_child;
	}
	else {
		for (int i = 0; i < subordinate_objects.size(); ++i) {
			ptr_child = subordinate_objects[i]->get_p_from_this_hierarchy(finding_name);
			if (ptr_child != nullptr) {
				return ptr_child;
			}
		}
		return nullptr;
	}
}

cl_base* cl_base::get_p_global_hierarchy(std::string finding_name) {
	cl_base* pointer_object = this;
	while (pointer_object->get_p_head_object() != nullptr) {
		pointer_object = pointer_object->get_p_head_object();
	}
	return pointer_object->get_p_from_this_hierarchy(finding_name);
}

void cl_base::print_hiararchy_from_this(int lvl) {
	for (int i = 0; i < subordinate_objects.size(); ++i) {
		for (int blank = 0; blank < lvl * 4; ++blank) {
			std::cout << ' ';
		}
		std::cout << subordinate_objects[i]->get_s_object_name() << '\n';
		print_hiararchy_from_this(lvl + 1);
	}
}

void cl_base::print_hiararchy_state_from_this(int lvl) {
	for (int i = 0; i < subordinate_objects.size(); ++i) {
		for (int blank = 0; blank < lvl * 4; ++blank) {
			std::cout << ' ';
		}
		std::cout << subordinate_objects[i]->get_s_object_name() << " " << subordinate_objects[i]->get_state() << '\n';
		subordinate_objects[i]->print_hiararchy_state_from_this(lvl + 1);
	}
}

void cl_base::print_global_hierarchy_state() {
	cl_base* pointer_object = this;
	while (pointer_object->p_head_object != nullptr) {
		pointer_object = pointer_object->get_p_head_object();
	}
	std::cout << pointer_object->get_s_object_name() << " " << pointer_object->get_state() << '\n';
	pointer_object->print_hiararchy_state_from_this();
}

void cl_base::print_hiararchy(int lvl) {
	for (int i = 0; i < subordinate_objects.size(); ++i) {
		for (int blank = 0; blank < lvl * 4; ++blank) {
			std::cout << ' ';
		}
	std::cout << subordinate_objects[i]->get_s_object_name() << '\n';
		//<< " " << subordinate_objects[i] << '\n';
		subordinate_objects[i]->print_hiararchy(lvl + 1);
	}
}

void cl_base::print_global_hierarchy() {
	cl_base* pointer_object = this;
	while (pointer_object->p_head_object != nullptr) {
		pointer_object = pointer_object->get_p_head_object();
	}
	std::cout << pointer_object->get_s_object_name() << '\n';
	pointer_object->print_hiararchy();
}

cl_base::~cl_base(){}