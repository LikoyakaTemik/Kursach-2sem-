﻿#include "cl_base.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

/*
!!!!!Описания методов смотреть в cl_base.h!!!!!
*/
cl_base::cl_base(cl_base* p_head_object, std::string s_object_name) {
	this->p_head_object = p_head_object;
	this->s_object_name = s_object_name;
	if (p_head_object) {
		p_head_object->subordinate_objects.push_back(this);
	}
}

bool cl_base::set_s_object_name(std::string s_object_name) {
	if (p_head_object) {	// Проверка на то, является ли текущий головной объект корнем дерева
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

void cl_base::set_num(int num) {
	this->num = num;
}

bool cl_base::set_p_head_object(cl_base* pointer) {
	if (!pointer) {
		return false;
	}
	else {
		if (this->get_p_head_object() && !get_p_from_this_hierarchy(pointer)) {
			get_p_head_object()->delete_child(get_s_object_name());
			p_head_object = pointer;
			pointer->subordinate_objects.push_back(this);
			return true;
		}
		else {
			return false;
		}
	}
}

bool cl_base::delete_child(std::string name_child) {
	if (get_p_child(name_child)) {
		subordinate_objects.erase(find(subordinate_objects.begin(), subordinate_objects.end(), get_p_child(name_child)));
		return true;
	}
	else {
		return false;
	}

}

bool cl_base::is_state_before() {
	cl_base* pointer = get_p_head_object();

	if (pointer != nullptr) {
		if (pointer->state != 0) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
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

	for (int i = 0; i < name.size(); ++i) {
		if (name[i] == '/' || name[i] == '.') {
			return false;
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

int cl_base::get_num() {
	return num;
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

cl_base* cl_base::get_p_child(cl_base* child_obj) {
	for (int i = 0; i < subordinate_objects.size(); ++i) {
		if (subordinate_objects[i] == child_obj) {
			return subordinate_objects[i];
		}
	}
	return nullptr;
}

connect* cl_base::get_p_connect(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER   p_ob_hendler){
	for (int i = 0; i < connects.size(); ++i) {
		if (connects[i]->p_signal == p_signal &&
			connects[i]->p_target == p_target &&
			connects[i]->p_handler == p_ob_hendler) {
			return connects[i];
		}
	}
	return nullptr;
}

std::string cl_base::get_p_absolute_coordinate(std::string finding_child) {
	if (get_p_child(finding_child)) {
		std::vector<cl_base*>coordinate_from_head;
		cl_base* pointer = get_p_child(finding_child);
		while (pointer->get_p_head_object() != nullptr) {
			coordinate_from_head.push_back(pointer);
			pointer = pointer->get_p_head_object();
		}
		std::string coordinate = "/";
		for (int i = 0; i < coordinate_from_head.size(); ++i) {
			coordinate += coordinate_from_head[coordinate_from_head.size() - i - 1]->get_s_object_name();
			if (i + 1 != coordinate_from_head.size()) {
				coordinate += '/';
			}
		}
		return coordinate;
	}
	else {
		return "null";
	}
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

cl_base* cl_base::get_p_from_this_hierarchy(cl_base* finding_obj) {
	cl_base* ptr_child = get_p_child(finding_obj);
	if (ptr_child != nullptr) {
		return ptr_child;
	}
	else {
		for (int i = 0; i < subordinate_objects.size(); ++i) {
			ptr_child = subordinate_objects[i]->get_p_from_this_hierarchy(finding_obj);
			if (ptr_child != nullptr) {
				return ptr_child;
			}
		}
		return nullptr;
	}
}

cl_base* cl_base::get_p_global_hierarchy(std::string coordinate) {
	cl_base* pointer_object = this;
	std::vector<std::string> objs = coordinate_parse(coordinate);
	for (int cor = 0; cor < objs.size(); ++cor) {
		if (objs[cor].size() == 1 && objs.size() == 1) {
			if (objs[0] == "/" || objs[0] == "//") {
				while (pointer_object->get_p_head_object() != nullptr) {
					pointer_object = pointer_object->get_p_head_object();
				}
				return pointer_object;
			}
			else if (objs[cor] == ".") {
				return this;
			}
		}
		if (objs[cor][0] == '/' && objs[cor][1] == '/') {
			std::string finding_name = "";
			for (int i = 2; i < objs[cor].size(); ++i) {
				finding_name += objs[cor][i];
			}
			if (finding_name == "") {
				return nullptr;
			}
			while (pointer_object->get_p_head_object() != nullptr) {
				pointer_object = pointer_object->get_p_head_object();
			}
			pointer_object = pointer_object->get_p_child(finding_name);
		}
		else if (objs[cor][0] == '.') {
			std::string finding_name = "";
			for (int i = 1; i < objs[cor].size(); ++i) {
				finding_name += objs[cor][i];
			}
			if (finding_name == "") {
				return nullptr;
			}
			pointer_object = get_p_from_this_hierarchy(finding_name);
		}
		else if (objs[cor][0] == '/') {
			std::string finding_name = "";
			for (int i = 1; i < objs[cor].size(); ++i) {
				finding_name += objs[cor][i];
			}
			if (finding_name == "") {
				return nullptr;
			}
			if (cor == 0) {
				while (pointer_object->get_p_head_object() != nullptr) {
					pointer_object = pointer_object->get_p_head_object();
				}
				pointer_object = pointer_object->get_p_child(finding_name);
			}
			else {
				pointer_object = pointer_object->get_p_child(finding_name);
			}
		}
		else {
			std::string finding_name = "";
			for (int i = 0; i < objs[cor].size(); ++i) {
				finding_name += objs[cor][i];
			}
			if (finding_name == "") {
				return nullptr;
			}
			pointer_object = get_p_child(finding_name);
		}
	}
	return pointer_object;
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

std::vector<std::string> cl_base::coordinate_parse(std::string coordinate) {
	std::vector<std::string>command;
	std::string str = "";
	for (int i = 0; i < coordinate.size(); ++i) {
		if (coordinate[i] != '/' && coordinate[i] != '.') {
			str = str + coordinate[i];
		}
		else {
			if (str.size() == 0) {
				str = str + coordinate[i];
			}
			else if (coordinate[i - 1] == '/' && coordinate[i] == '/') {
				str = str + coordinate[i];
			}
			else {
				command.push_back(str);
				str = coordinate[i];
			}
		}
	}
	command.push_back(str);
	return command;
}

void cl_base::set_connect(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER   p_ob_handler){
	connect* p_value;
	//--------------------------------------------------------
	// Цикл для исключения повторного установления связи
	for (int i = 0; i < connects.size(); i++)
	{
		if (connects[i]->p_signal == p_signal &&
			connects[i]->p_target == p_target &&
			connects[i]->p_handler == p_ob_handler)
		{
			return;
		}
	}

	p_value = new connect();                 // создание объекта структуры для
											 // хранения информации о новой связи
	p_value->p_signal = p_signal;
	p_value->p_target = p_target;
	p_value->p_handler = p_ob_handler;

	connects.push_back(p_value);          // добавление новой связи  
}

void cl_base::emit_signal(TYPE_SIGNAL p_signal, std::string& s_command){
	if (this->get_state() == "is ready") {
		(this->*p_signal)(s_command);  // вызов метода сигнала
		for (int i = 0; i < connects.size(); i++) // цикл по всем обработчикам
		{
			if (connects[i]->p_signal == p_signal)      // определение допустимого обработчика
			{
				if (connects[i]->p_target->get_state() == "is ready") {
					cl_base* p_target = connects[i]->p_target;      // вызов метода обработчика
					(p_target->*(connects[i]->p_handler))(s_command);
				}
			}
		}
	}
}

void cl_base::delete_connect(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER   p_ob_handler){
	connects.erase(find(connects.begin(), connects.end(), get_p_connect(p_signal, p_target, p_ob_handler)));
}

cl_base::~cl_base() {}