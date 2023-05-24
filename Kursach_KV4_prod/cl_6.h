#ifndef __CL_6__H
#define __CL_6__H
#include "cl_base.h"
#include <iostream>
class cl_6 :public cl_base {
public:
	cl_6(cl_base* p_head_object, std::string s_object_name = "Base_object");	// Параметризованный конструктор объекта
	void signal_f(std::string& command);	// Метод сигнала объекта
	void handler_f(std::string command);	// Метод обработчика сигнала объекта
	~cl_6();	// Деструктор объекта
};

#endif
