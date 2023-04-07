#include <iostream>
#include <vector>
#include <string>
using namespace std;

class cl_base {
protected:
	string s_object_name = "Base_object";
	cl_base* p_head_object = nullptr;
	vector <cl_base*> subordinate_objects;
	unsigned short type = 1;
	unsigned short state = 0;
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

	void set_state(int state) {
		if (is_ready_before()) {
			this->state = state;
		}
	}

	bool is_ready_before() {////äîïèñàòü

	}

	bool is_uniq_name(string name){ /////äîïèñàòü
		
	}

	string get_s_object_name() {
		return s_object_name;
	}

	cl_base* get_p_head_object() {
		return p_head_object;
	}

	string get_state() {
		if (state != 0) {
			return "is ready";
		}
		else {
			return "is not ready";
		}
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

	cl_base* get_p_from_this_hierarchy(string finding_name) {
		cl_base* ptr_child = get_p_child(finding_name);
		if (ptr_child) {
			return ptr_child;
		}
		for (int i = 0; i < subordinate_objects.size(); ++i) {
			subordinate_objects[i]->get_p_from_this_hierarchy(finding_name);
		}
		return nullptr;	
	}

	cl_base* get_p_global_hierarchy(string finding_name) {
		cl_base* pointer_object = this;
		while (pointer_object->p_head_object != nullptr) {
			pointer_object = pointer_object->p_head_object;
		}

		return pointer_object->get_p_from_this_hierarchy(finding_name);
	}

	void print_hiararchy_from_this(int lvl = 0) {
			for (int i = 0; i < subordinate_objects.size(); ++i) {
				for (int blank = 0; blank < lvl * 4; ++blank) {
					cout << ' ';
				}
				cout << subordinate_objects[i]->get_s_object_name() << '\n';
				print_hiararchy_from_this(lvl + 1);
			}
	}

	void print_hiararchy_state_from_this(int lvl = 0) {
		for (int i = 0; i < subordinate_objects.size(); ++i) {
			for (int blank = 0; blank < lvl * 4; ++blank) {
				cout << ' ';
			}
			cout << subordinate_objects[i]->get_s_object_name() << " " << subordinate_objects[i]->get_state() << '\n';
			print_hiararchy_state_from_this(lvl + 1);
		}
	}

	void print_global_hierarchy_state() {
		cl_base* pointer_object = this;
		while (pointer_object->p_head_object != nullptr) {
			pointer_object = pointer_object->p_head_object;
		}
		pointer_object->print_hiararchy_state_from_this();
	}


};

class cl_app :public cl_base {
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
			if (objects.size() != 1) {
				if (objects[0] == get_s_object_name()) {
					cl_base* ob;
					for (int i = 1; i < objects.size(); ++i) {
						if (is_uniq_name(objects[i])) {///////////////////////////////äîïèñàòü
							ob = new cl_base(this, objects[i]);
						}
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
							if (is_uniq_name(objects[i])) {////////////////////////////äîïèñàòü
								ob = new cl_base(pointer, objects[i]);
							}
						}
					}
					else {
						cl_base* ob;
						for (int i = 1; i < objects.size(); ++i) {
							if (is_uniq_name(objects[i])) {////////////////////////////äîïèñàòü
								ob = new cl_base(pointer, objects[i]);
							}
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
