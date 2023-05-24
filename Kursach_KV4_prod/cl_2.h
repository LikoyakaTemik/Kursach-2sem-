#ifndef __CL_2__H
#define __CL_2__H
#include "cl_base.h"
#include <iostream>
class cl_2 :public cl_base {
public:
	cl_2(cl_base* p_head_object, std::string s_object_name = "Base_object");	// Параметризованный конструктор объекта
	void signal_f(std::string& command);	// Метод сигнала объекта
	void handler_f(std::string command);	// Метод обработчика сигнала объекта
	~cl_2();	// Деструктор объекта
};

#endif
