#include "cl_app.h"
#include "cl_base.h"
using namespace std;

cl_app::cl_app(cl_base* p_head_object):cl_base(p_head_object){}

void cl_app::build_tree_objects() {
	vector<string> objects;
	string command;
	getline(cin, command, '\n');
	set_s_object_name(command);
	while (true) {
		objects.clear();
		getline(cin, command, '\n');
		for (int i = 0; i < command.size(); ++i) {
			string obj_name = "";
			while (command[i] != ' ' && i < command.size()) {
				obj_name = obj_name + command[i];
				++i;
			}
			objects.push_back(obj_name);
		}
		if (objects[0] != objects[1]) {
			if (objects[0] == get_s_object_name()) {
				cl_base* ob;
				for (int i = 1; i < objects.size(); ++i) {
					ob = new cl_base(this, objects[i]);
				}
				/*for (int i = 0; i < subordinate_objects.size(); ++i) {
					cout << subordinate_objects[i]->get_s_object_name() << " ";
				}*/
				pointer = this;
			}
			else {
				if (objects[0] != pointer->get_s_object_name()) {
					pointer = pointer->get_p_child(objects[0]);
					cl_base* ob;
					for (int i = 1; i < objects.size(); ++i) {
						ob = new cl_base(pointer, objects[i]);
					}
				}
				else {
					cl_base* ob;
					for (int i = 1; i < objects.size(); ++i) {
						ob = new cl_base(pointer, objects[i]);
					}
				}
			}
		}
		else {
			return;
		}
	}
}

int cl_app::exec_app() {
	pointer->print_s_object_name_tree();
	return 0;
}