#ifndef __CL_APP__H
#define __CL_APP__H
#include "cl_base.h"


class cl_app :public cl_base {

public:
	cl_app(cl_base* p_head_object);		// Параметризованный конструктор класса с параметром указателя на головной объект

	int build_tree_objects();	// Метод построения дерева иерархии объектов(КВ1-КВ3) и связей между объектами(КВ4)

	void signal_f(std::string& command);	// Метод сигнала головного объекта

	void handler_f(std::string command);	// Метод обработчика сигнала головного объекта

	int exec_app();		// Метод обработчика команд системы

	~cl_app();		// Деструктор системы
};

#endif