#ifndef __CL_6__H
#define __CL_6__H
#include "cl_base.h"
#include <iostream>
class cl_6 :public cl_base {
public:
	cl_6(cl_base* p_head_object, std::string s_object_name = "Base_object");
	void signal_f(std::string& command);
	void handler_f(std::string command);
	~cl_6();
};

#endif
