#include "cl_app.h"
#include "cl_2.h"
#include "cl_3.h"
#include "cl_4.h"
#include "cl_5.h"
#include "cl_6.h"
#include "cl_base.h"
#include <iostream>
#include <vector>
#include <string>
cl_app::cl_app(cl_base* p_head_object) :cl_base(p_head_object) {}

int cl_app::build_tree_objects() {
	cl_base* pointer = this;
	std::vector<std::string> objects;
	std::string command;
	std::getline(std::cin, command, '\n');
	set_s_object_name(command);
	while (true) {
		objects.clear();
		std::getline(std::cin, command, '\n');
		for (int i = 0; i < command.size(); ++i) {
			std::string obj_name = "";
			while (command[i] != ' ' && i < command.size()) {
				obj_name = obj_name + command[i];
				++i;
			}
			objects.push_back(obj_name);
		}
		if (objects.size() != 1) {
			if (get_p_global_hierarchy(objects[0]) == this) {
				//std::cout << "get>>" << get_p_global_hierarchy(objects[0]) << " should_be>>" << this << '\n';
				cl_base* ob;
				pointer = this;
				if (!get_p_child(objects[1]) && is_correct_type(objects[2])) {
					int type = int(objects[2][0]) - 48;
					switch (type)
					{
					default:
						ob = new cl_base(pointer, objects[1]);
						break;
					case 2:
						ob = new cl_2(pointer, objects[1]);
						break;
					case 3:
						ob = new cl_3(pointer, objects[1]);
						break;
					case 4:
						ob = new cl_4(pointer, objects[1]);
						break;
					case 5:
						ob = new cl_5(pointer, objects[1]);
						break;
					case 6:
						ob = new cl_6(pointer, objects[1]);
						break;
					}
				}
				else {
					if (get_p_child(objects[1])) {
						std::cout << objects[0] << "     Dubbing the names of subordinate objects\n";
					}
				}
			}
			else {
				if (get_p_global_hierarchy(objects[0]) != nullptr) {
					if (get_p_global_hierarchy(objects[0]) != pointer) {
						pointer = get_p_global_hierarchy(objects[0]);
						//std::cout << "get>>" << get_p_global_hierarchy(objects[0]) << " name: " << pointer->get_s_object_name() << '\n';
						if (!(pointer->get_p_child(objects[1])) && is_correct_type(objects[2])) {
							if (pointer) {
								cl_base* ob;
								int type = int(objects[2][0]) - 48;
								switch (type)
								{
								default:
									ob = new cl_base(pointer, objects[1]);
									break;
								case 2:
									ob = new cl_2(pointer, objects[1]);
									break;
								case 3:
									ob = new cl_3(pointer, objects[1]);
									break;
								case 4:
									ob = new cl_4(pointer, objects[1]);
									break;
								case 5:
									ob = new cl_5(pointer, objects[1]);
									break;
								case 6:
									ob = new cl_6(pointer, objects[1]);
									break;
								}
							}
						}
						else {
							if (pointer->get_p_child(objects[1])) {
								std::cout << objects[0] << "     Dubbing the names of subordinate objects\n";
							}
						}
					}
					else {
						if (!(pointer->get_p_child(objects[1])) && is_correct_type(objects[2])) {
							cl_base* ob;
							int type = int(objects[2][0]) - 48;
							switch (type)
							{
							default:
								ob = new cl_base(pointer, objects[1]);
								break;
							case 2:
								ob = new cl_2(pointer, objects[1]);
								break;
							case 3:
								ob = new cl_3(pointer, objects[1]);
								break;
							case 4:
								ob = new cl_4(pointer, objects[1]);
								break;
							case 5:
								ob = new cl_5(pointer, objects[1]);
								break;
							case 6:
								ob = new cl_6(pointer, objects[1]);
								break;
							}
						}
						else {
							if (pointer->get_p_child(objects[1])) {
								std::cout << objects[0] << "     Dubbing the names of subordinate objects\n";
							}
						}
					}
				}
				else {
					std::cout << "Object tree\n";
					print_global_hierarchy();
					std::cout << "The head object " << objects[1] << " is not found";
					return 1;
				}
			}
		}
		else {
			break;
		}
	}
	std::cout << "Object tree\n";
	print_global_hierarchy();
	pointer = this;
	while (true) {
		objects.clear();
		std::getline(std::cin, command, '\n');
		for (int i = 0; i < command.size(); ++i) {
			std::string obj_name = "";
			while (command[i] != ' ' && i < command.size()) {
				obj_name = obj_name + command[i];
				++i;
			}
			objects.push_back(obj_name);
		}
		
		if (objects[0] == "SET") {
			if (objects[1][0] == '/') {
				pointer = get_p_global_hierarchy(objects[1]);
			}
			else {
				pointer = pointer->get_p_global_hierarchy(objects[1]);
			}
			if (pointer) {
				std::cout << "Object is set: " << pointer->get_s_object_name() << '\n';
			}
			else {
				std::cout << "The object was not found at the specified coordinate:  " << objects[1] << '\n';
			}
		}
		else if (objects[0] == "FIND") {
			//std::cout << "\n>>" << objects[1] << '\n';
			//std::cout << "\n>>" << pointer << " name: "<< pointer->get_s_object_name() << '\n';
			cl_base* finding_pointer = pointer->get_p_global_hierarchy(objects[1]);
			if (finding_pointer) {
				std::cout << objects[1] << "     Object name: " << finding_pointer->get_s_object_name() << '\n';
			}
			else {
				std::cout << objects[1] << "     Object is not found\n";
			}
		}
		else if (objects[0] == "MOVE") {
			cl_base* cur_pointer = this;
			if (objects[1][0] == '/') {
				cur_pointer = get_p_global_hierarchy(objects[1]);
			}
			else {
				cur_pointer = pointer->get_p_global_hierarchy(objects[1]);
			}
			if (cur_pointer) {//Проверка на существование головного объекта
				if (!(pointer->get_p_from_this_hierarchy(cur_pointer))) {//проверка, не является ли новый головной объект потомком текущего
					if (!(cur_pointer->get_p_child(pointer->get_s_object_name()))) {//проверка на дубликаты имён для головного объекта
						pointer->set_p_head_object(cur_pointer);
						std::cout << "New head object : " << cur_pointer->get_s_object_name() << '\n';
					}
					else {
						std::cout << objects[1] << "     Dubbing the names of subordinate objects\n";
					}
				}
				else {
					std::cout << objects[1] << "      Redefining the head object failed\n";
				}
			}
			else {
				std::cout << objects[1] << "     Head object is not found\n";
			}
		}
		else if (objects[0] == "DELETE") {
			std::string absolute_coordinate = pointer->get_p_absolute_coordinate(objects[1]);
			if (pointer->delete_child(objects[1])) {
				std::cout << "The object " << absolute_coordinate << " has been deleted\n";
			}
		}
		else if (objects[0] == "END") {
			return 0;
		}
	}
}

int cl_app::exec_app() {
	std::cout << "Current object hierarchy tree\n";
	print_global_hierarchy();
	return 0;
}

cl_app::~cl_app() {}