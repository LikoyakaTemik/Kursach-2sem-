#include "cl_base.h"
#ifndef __CL_PROD__H
#define __CL_PROD__H
#include <iostream>
class cl_prod :public cl_base {
public:
	cl_prod(cl_base* p_head_object, std::string s_object_name = "Base_object");
	~cl_prod();
};

#endif
