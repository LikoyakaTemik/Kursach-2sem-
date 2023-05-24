#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "cl_app.h"

int main() {

	cl_app ob_cl_app(nullptr);	//Создание объекта-приложения
	if (ob_cl_app.build_tree_objects() == 1) {		// Вызов метода построения дерева объекта с проверкой корректности его завершения(КВ3)
		return 1;
	}
	return ob_cl_app.exec_app();	// Вызов метода обработчика приложения
}