#include "cl_base.h"

class cl_app:public cl_base {
private:
	cl_base* pointer;
public:
	cl_app(cl_base* p_head_object);
	void build_tree_objects();
	int exec_app();
};	