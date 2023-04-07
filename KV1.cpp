#include <iostream>
#include <vector>
#include <string>
using namespace std;

class cl_base {
protected:
	string s_object_name = "Base_object";
	cl_base* p_head_object = nullptr;
	vector <cl_base*> subordinate_objects;
public:
	cl_base(cl_base* p_head_object, string s_object_name = "Base_object") {
		this->p_head_object = p_head_object;
		this->s_object_name = s_object_name;
		if (p_head_object) {
			p_head_object->subordinate_objects.push_back(this);
		}
	}

	bool set_s_object_name(string s_object_name) {
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

	string get_s_object_name() {
		return s_object_name;
	}

	cl_base* get_p_head_object() {
		return p_head_object;
	}

	void print_s_object_name_tree() {
		int lvl = 1;
		cl_base* pointer_object = this;
		vector <cl_base*> ordinate_objects;
		while (pointer_object->p_head_object != nullptr) {
			ordinate_objects.push_back(pointer_object);
			pointer_object = pointer_object->p_head_object;
		}
		
		cout << pointer_object->get_s_object_name() << '\n';

		while (pointer_object != this) {
			for (int i = 0; i < pointer_object->subordinate_objects.size(); ++i) {
				for (int blank = 0; blank < lvl * 4; ++blank) {
					cout << ' ';
				}
				cout << pointer_object->subordinate_objects[i]->get_s_object_name() << '\n';
			}
			pointer_object = ordinate_objects[ordinate_objects.size() - lvl];
			lvl++;
		}

		for (int i = 0; i < pointer_object->subordinate_objects.size(); ++i) {
			for (int blank = 0; blank < lvl * 4; ++blank) {
				cout << ' ';
			}
			cout << pointer_object->subordinate_objects[i]->get_s_object_name() << '\n';
		}
	}

	cl_base* get_p_child(string child_name) {
		for (int i = 0; i < subordinate_objects.size(); ++i) {
			if (subordinate_objects[i]->get_s_object_name() == child_name) {
				return subordinate_objects[i];
			}
		}
		return nullptr;
	}
};

class cl_app:public cl_base{
private: 
	cl_base* pointer;
public:
	cl_app(cl_base* p_head_object) :cl_base(p_head_object) {}

	void build_tree_objects() {
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

	int exec_app() {
		pointer->print_s_object_name_tree();
		return 0;
	}
};

int main() {

	cl_app ob_cl_app(nullptr);
	ob_cl_app.build_tree_objects();
	return ob_cl_app.exec_app();
}