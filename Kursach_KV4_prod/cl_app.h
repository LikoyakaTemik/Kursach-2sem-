#ifndef __CL_APP__H
#define __CL_APP__H
#include "cl_base.h"
class cl_app :public cl_base {
public:
	cl_app(cl_base* p_head_object);

	int build_tree_objects();

	void signal_f(std::string& command);

	void handler_f(std::string command);

	int exec_app();

	~cl_app();
};

#endif