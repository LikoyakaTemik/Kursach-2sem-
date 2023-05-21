#include "cl_base.h"

cl_base::cl_base(cl_base* p_head_object, string s_object_name) {
	this->p_head_object = p_head_object;
	this->s_object_name = s_object_name;
	if (p_head_object) {
		p_head_object->subordinate_objects.push_back(this);
	}
}

bool cl_base::set_s_object_name(string s_object_name) {
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

string cl_base::get_s_object_name() {
	return s_object_name;
}

cl_base* cl_base::get_p_head_object() {
	return p_head_object;
}

void cl_base::print_s_object_name_tree() {
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

cl_base* cl_base::get_p_child(string child_name) {
	for (int i = 0; i < subordinate_objects.size(); ++i) {
		if (subordinate_objects[i]->get_s_object_name() == child_name) {
			return subordinate_objects[i];
		}
	}
	return nullptr;
}