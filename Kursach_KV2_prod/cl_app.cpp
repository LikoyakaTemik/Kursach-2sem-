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

void cl_app::build_tree_objects() {
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
			if (objects[0] == get_s_object_name()) {
				cl_base* ob;
				pointer = this;
				if (is_global_uniq_name(objects[1]) && is_correct_type(objects[2])) {
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
				if (objects[0] != pointer->get_s_object_name() && is_global_uniq_name(objects[1]) && is_correct_type(objects[2])) {
					pointer = pointer->get_p_global_hierarchy(objects[0]);
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
					if (is_global_uniq_name(objects[1]) && is_correct_type(objects[2])) {
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
			}
		}
		else {
			break;
		}
	}

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

			
		/*for (int i = 0; i < objects.size(); ++i) {
			std::cout << objects[i] << " ";
		}*/

		if (objects.size() == 2) {
			if (objects[0] != get_s_object_name()) {
				get_p_from_this_hierarchy(objects[0])->set_state(objects[1]);
			}
			else {
				set_state(objects[1]);
			}
		}
		else {
			return;
		}
	}
}

int cl_app::exec_app() {
	std::cout << "Object tree\n";
	print_global_hierarchy();
	std::cout << "The tree of objects and their readiness\n";
	print_global_hierarchy_state();
	return 0;
}

cl_app::~cl_app(){}