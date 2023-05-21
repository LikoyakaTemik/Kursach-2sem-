#include <iostream>
#include <vector>
#include <string>
#include "cl_base.h"
#include "cl_app.h"
using namespace std;

int main() {

	cl_app ob_cl_app(nullptr);
	ob_cl_app.build_tree_objects();
	return ob_cl_app.exec_app();
}	