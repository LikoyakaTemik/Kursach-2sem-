#ifndef __CL_BASE__H
#define __CL_BASE__H
#define SIGNAL_D(signal_f) (TYPE_SIGNAL)(&signal_f)
#define HANDLER_D(handler_f) (TYPE_HANDLER)(&handler_f)
#include <iostream>
#include <vector>

class cl_base;

typedef void (cl_base::*TYPE_SIGNAL) (std::string&);	//создание типа указателя на метод сигнала
typedef void (cl_base::*TYPE_HANDLER) (std::string);	//создание типа указателя на метод обработчика

struct connect                 // Структура задания одной связи
{
	TYPE_SIGNAL  p_signal;    // Указатель на метод сигнала
	cl_base* p_target;   // Указатель на целевой объект
	TYPE_HANDLER p_handler;   // Указатель на метод обработчика
};

class cl_base {
protected:
	std::string s_object_name = "Base_object";	// Имя объекта
	cl_base* p_head_object = nullptr;	// Указатель на головной объект
	std::vector <cl_base*> subordinate_objects;		// Массив указателей на подчинённые объекты
	unsigned short state = 1;	// Состояние объекта
	unsigned short num = 1;		// Номер класса объекта
	std::vector<connect*> connects;		// Вектор структур связей объекта
public:
	cl_base(cl_base* p_head_object, std::string s_object_name = "Base_object");		// Параметризованный конструктор объекта

	bool set_s_object_name(std::string s_object_name);		// Метод изменения имени объекта

	void set_state(std::string state);		// Метод установки состояния объекта

	void set_num(int num);		// Метод установки номера класса объекта

	bool set_p_head_object(cl_base* pointer);	// Метод переопределения головного объекта

	bool delete_child(std::string name_child);		// Метод удаления подчинённого объекта из массива subordinate_objects

	bool is_state_before();		// Метод проверки состояния головного объекта

	bool is_correct_type(std::string type);		// Метод проверки корректности номера класса объекта

	bool is_uniq_name(std::string name);	// Метод проверки уникальности имени объекта среди подчинённых объектов головного объекта

	bool is_global_uniq_name(std::string name);		// Метод проверки уникальности имени объекта на всём дереве иерархии

	std::string get_s_object_name();	// Метод получения имени объекта

	cl_base* get_p_head_object();	// Метод получения указателя на головной объект

	std::string get_state();	// Метод получения состояния объекта

	int get_num();		// Метод получения номера класса объекта

	cl_base* get_p_child(std::string child_name);	// Метод получения указателя на подчинённый объект по имени

	cl_base* get_p_child(cl_base* child_obj);	// Метод получения указателя на подчинённый объект по указателю

	connect* get_p_connect(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER   p_ob_hendler);	// Метод получения указателя на связь

	std::string get_p_absolute_coordinate(std::string finding_obj);		// Метод получения абсолютной координаты текущего объекта

	cl_base* get_p_from_this_hierarchy(std::string finding_name);	// Метод получения указателя на объект по дереву вниз от текущего по имени

	cl_base* get_p_from_this_hierarchy(cl_base* finding_obj);	// Метод получения указателя на объект по дереву вниз от текущего по параметру

	cl_base* get_p_global_hierarchy(std::string finding_name);	// Метод получения указателя на объект на всём дереве по имени

	void print_s_object_name_tree();	// Метод вывод имён объектов ввиде иерархии на всём дереве(КВ1)

	void print_hiararchy_from_this(int lvl = 0);	// Метод вывод имён объектов ввиде иерархии от текущего объекта(КВ1)

	void print_hiararchy_state_from_this(int lvl = 1);		// Метод вывода имён объектов и соответствующих им состояний ввиде иерархии от текущего объекта(КВ2)

	void print_global_hierarchy_state();	// Метод вывода имён объектов и соответствующих им состояний ввиде иерархии на всём дереве(КВ2)

	void print_hiararchy(int lvl = 1);		// Метод вывода иерархии объектов от текущего объекта(КВ3-КВ4)

	void print_global_hierarchy();		// Метод вывода иерархии объектов на всём дереве(КВ3-КВ4)

	std::vector<std::string> coordinate_parse(std::string coordinate);		// Метод разбиения введённой команды на части для дальнейшей обработки

	void set_connect(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER   p_ob_handler);		// Метод установления связи с объектом на дереве иерархии

	void emit_signal(TYPE_SIGNAL p_signal, std::string& s_command);		// Метод вызова сигнала от объекта по связям

	void delete_connect(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER   p_ob_handler);		// Метод удаления связи

	~cl_base();		// Деструктор класса
};

#endif