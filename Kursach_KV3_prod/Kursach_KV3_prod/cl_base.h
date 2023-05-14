#ifndef __CL_BASE__H
#define __CL_BASE__H
#include <iostream>
#include <vector>

class cl_base {
protected:
	std::string s_object_name = "Base_object";
	cl_base* p_head_object = nullptr;
	std::vector <cl_base*> subordinate_objects;
	unsigned short state = 0;
public:
	cl_base(cl_base* p_head_object, std::string s_object_name = "Base_object");

	bool set_s_object_name(std::string s_object_name);

	void set_state(std::string state);

	bool set_p_head_object(cl_base* pointer);

	bool delete_child(std::string name_child);

	bool is_state_before();

	bool is_correct_type(std::string type);

	bool is_uniq_name(std::string name);

	bool is_global_uniq_name(std::string name);

	std::string get_s_object_name();

	cl_base* get_p_head_object();

	std::string get_state();

	void print_s_object_name_tree();

	cl_base* get_p_child(std::string child_name);

	cl_base* get_p_child(cl_base* child_obj);

	std::string get_p_absolute_coordinate(std::string finding_obj);

	cl_base* get_p_from_this_hierarchy(std::string finding_name);

	cl_base* get_p_from_this_hierarchy(cl_base* finding_obj);

	cl_base* get_p_global_hierarchy(std::string finding_name);

	void print_hiararchy_from_this(int lvl = 0);

	void print_hiararchy_state_from_this(int lvl = 1);

	void print_global_hierarchy_state();

	void print_hiararchy(int lvl = 1);

	void print_global_hierarchy();

	std::vector<std::string> coordinate_parse(std::string coordinate);

	~cl_base();
};

#endif