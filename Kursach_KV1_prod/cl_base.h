#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class cl_base
{
protected:
	string s_object_name = "Base_object";
	cl_base* p_head_object = nullptr;
	vector <cl_base*> subordinate_objects;
public:
	cl_base(cl_base* p_head_object, string s_object_name = "Base_object");
	bool set_s_object_name(string s_object_name);
	string get_s_object_name();
	cl_base* get_p_head_object();
	void print_s_object_name_tree();
	cl_base* get_p_child(string child_name);	
};

