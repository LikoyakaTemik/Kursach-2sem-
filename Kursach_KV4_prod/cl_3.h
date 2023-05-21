#ifndef __CL_3__H
#define __CL_3__H
#include "cl_base.h"
#include <iostream>
class cl_3 :public cl_base {
public:
	cl_3(cl_base* p_head_object, std::string s_object_name = "Base_object");
	void signal_f(std::string& command);
	void handler_f(std::string command);
	~cl_3();
};

#endif
