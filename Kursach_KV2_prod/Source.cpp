#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "cl_app.h"

int main() {

	cl_app ob_cl_app(nullptr);
	ob_cl_app.build_tree_objects();
	return ob_cl_app.exec_app();
}