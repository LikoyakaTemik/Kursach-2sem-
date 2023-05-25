#include "cl_app.h"
#include "cl_2.h"
#include "cl_3.h"
#include "cl_4.h"
#include "cl_5.h"
#include "cl_6.h"
#include "cl_base.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

/*
!!!!Описание методов смотреть в cl_app.h!!!!
*/

cl_app::cl_app(cl_base* p_head_object) :cl_base(p_head_object) {}

int cl_app::build_tree_objects() {
	cl_base* pointer = this;	// Указатель на текущий объект при построении
	std::vector<std::string> objects;	// Массив частей команды для дальнейшей обработки
	std::string command;	// Введённая команда
	std::map<int, TYPE_SIGNAL> type_signals_ptr;	// Массив указателей на методы сигнала классов
	type_signals_ptr[1] = SIGNAL_D(cl_app::signal_f);
	type_signals_ptr[2] = SIGNAL_D(cl_2::signal_f);
	type_signals_ptr[3] = SIGNAL_D(cl_3::signal_f);
	type_signals_ptr[4] = SIGNAL_D(cl_4::signal_f);
	type_signals_ptr[5] = SIGNAL_D(cl_5::signal_f);
	type_signals_ptr[6] = SIGNAL_D(cl_6::signal_f);

	std::map<int, TYPE_HANDLER> type_handlers_ptr;	// Массив указателей на методы обработчиков классов
	type_handlers_ptr[1] = HANDLER_D(cl_app::handler_f);
	type_handlers_ptr[2] = HANDLER_D(cl_2::handler_f);
	type_handlers_ptr[3] = HANDLER_D(cl_3::handler_f);
	type_handlers_ptr[4] = HANDLER_D(cl_4::handler_f);
	type_handlers_ptr[5] = HANDLER_D(cl_5::handler_f);
	type_handlers_ptr[6] = HANDLER_D(cl_6::handler_f);

	//Построение дерева
	std::getline(std::cin, command, '\n');
	set_s_object_name(command);
	while (true) {
		objects.clear();
		std::getline(std::cin, command, '\n');
		for (int i = 0; i < command.size(); ++i) {	// Цикл разбиения команды на части
			std::string obj_name = "";
			while (command[i] != ' ' && i < command.size()) {
				obj_name = obj_name + command[i];
				++i;
			}
			objects.push_back(obj_name);
		}
		if (objects.size() != 1) {
			if (get_p_global_hierarchy(objects[0]) == this) {
				cl_base* ob;
				pointer = this;
				if (!get_p_child(objects[1]) && is_correct_type(objects[2])) {
					int type = int(objects[2][0]) - 48;
					switch (type)
					{
					default:
						ob = new cl_base(pointer, objects[1]);
						break;
					case 2:
						ob = new cl_2(pointer, objects[1]);
						ob->set_num(2);
						break;
					case 3:
						ob = new cl_3(pointer, objects[1]);
						ob->set_num(3);
						break;
					case 4:
						ob = new cl_4(pointer, objects[1]);
						ob->set_num(4);
						break;
					case 5:
						ob = new cl_5(pointer, objects[1]);
						ob->set_num(5);
						break;
					case 6:
						ob = new cl_6(pointer, objects[1]);
						ob->set_num(6);
						break;
					}
				}
				else {
					if (get_p_child(objects[1])) {
						std::cout << objects[0] << "     Dubbing the names of subordinate objects\n";
					}
				}
			}
			else {
				if (get_p_global_hierarchy(objects[0]) != nullptr) {
					if (get_p_global_hierarchy(objects[0]) != pointer) {
						pointer = get_p_global_hierarchy(objects[0]);
						if (!(pointer->get_p_child(objects[1])) && is_correct_type(objects[2])) {
							if (pointer) {
								cl_base* ob;
								int type = int(objects[2][0]) - 48;
								switch (type)
								{
								default:
									ob = new cl_base(pointer, objects[1]);
									break;
								case 2:
									ob = new cl_2(pointer, objects[1]);
									ob->set_num(2);
									break;
								case 3:
									ob = new cl_3(pointer, objects[1]);
									ob->set_num(3);
									break;
								case 4:
									ob = new cl_4(pointer, objects[1]);
									ob->set_num(4);
									break;
								case 5:
									ob = new cl_5(pointer, objects[1]);
									ob->set_num(5);
									break;
								case 6:
									ob = new cl_6(pointer, objects[1]);
									ob->set_num(6);
									break;
								}
							}
						}
						else {
							if (pointer->get_p_child(objects[1])) {
								std::cout << objects[0] << "     Dubbing the names of subordinate objects\n";
							}
						}
					}
					else {
						if (!(pointer->get_p_child(objects[1])) && is_correct_type(objects[2])) {
							cl_base* ob;
							int type = int(objects[2][0]) - 48;
							switch (type)
							{
							default:
								ob = new cl_base(pointer, objects[1]);
								break;
							case 2:
								ob = new cl_2(pointer, objects[1]);
								ob->set_num(2);
								break;
							case 3:
								ob = new cl_3(pointer, objects[1]);
								ob->set_num(3);
								break;
							case 4:
								ob = new cl_4(pointer, objects[1]);
								ob->set_num(4);
								break;
							case 5:
								ob = new cl_5(pointer, objects[1]);
								ob->set_num(5);
								break;
							case 6:
								ob = new cl_6(pointer, objects[1]);
								ob->set_num(6);
								break;
							}
						}
						else {
							if (pointer->get_p_child(objects[1])) {
								std::cout << objects[0] << "     Dubbing the names of subordinate objects\n";
							}
						}
					}
				}
				else {
					std::cout << "Object tree\n";
					print_global_hierarchy();
					std::cout << "The head object " << objects[0] << " is not found";
					return 1;
				}
			}
		}
		else {
			break;
		}
	}
	std::cout << "Object tree\n";
	print_global_hierarchy();
	
	//Построение связей
	while (true) {
		objects.clear();
		std::getline(std::cin, command, '\n');
		for (int i = 0; i < command.size(); ++i) {	// Цикл разбиения команды на части
			std::string obj_name = "";
			while (command[i] != ' ' && i < command.size()) {
				obj_name = obj_name + command[i];
				++i;
			}
			objects.push_back(obj_name);
		}

		if (objects[0] == "end_of_connections") {
			break;
		}
		else{
			cl_base* sender = get_p_global_hierarchy(objects[0]);
			cl_base* getter = get_p_global_hierarchy(objects[1]);
			if (sender && getter) {
				int i_sender = sender->get_num();
				int i_getter = getter->get_num();
				sender->set_connect(type_signals_ptr[i_sender], getter, type_handlers_ptr[i_getter]);
			}
			else if (!sender) {
				std::cout << "Object " << objects[0] << " not found\n";
			}
			else {
				std::cout << "Handler object " << objects[1] << " not found\n";
			}
		}
	}
}

void cl_app::signal_f(std::string& command) {
	std::string absolute_coordinate;
	if (get_p_head_object()) {
		absolute_coordinate = get_p_head_object()->get_p_absolute_coordinate(get_s_object_name());
	}
	else {
		absolute_coordinate = "/" + get_s_object_name();
	}
	std::cout << "Signal from " << absolute_coordinate << '\n';
	command = command + " (class: " + char(get_num() + 48) + ')';
	return;
}

void cl_app::handler_f(std::string command) {
	std::string absolute_coordinate;
	if (get_p_head_object()) {
		absolute_coordinate = get_p_head_object()->get_p_absolute_coordinate(get_s_object_name());
	}
	else {
		absolute_coordinate = "/";
	}
	std::cout << "Signal to " << absolute_coordinate << " Text:  " << command << '\n';
	return;
}

int cl_app::exec_app() {
	cl_base* pointer = this;	// Указатель на текущий объект
	std::vector<std::string> objects;	// Массив частей команды для дальнешей обработки
	std::string command;	// Введённая команда
	std::map<int, TYPE_SIGNAL> type_signals_ptr;	// Массив указателей на методы сигнала классов
	type_signals_ptr[1] = SIGNAL_D(cl_app::signal_f);
	type_signals_ptr[2] = SIGNAL_D(cl_2::signal_f);
	type_signals_ptr[3] = SIGNAL_D(cl_3::signal_f);
	type_signals_ptr[4] = SIGNAL_D(cl_4::signal_f);
	type_signals_ptr[5] = SIGNAL_D(cl_5::signal_f);
	type_signals_ptr[6] = SIGNAL_D(cl_6::signal_f);

	std::map<int, TYPE_HANDLER> type_handlers_ptr;	// Массив указателей на методы обработчиков классов
	type_handlers_ptr[1] = HANDLER_D(cl_app::handler_f);
	type_handlers_ptr[2] = HANDLER_D(cl_2::handler_f);
	type_handlers_ptr[3] = HANDLER_D(cl_3::handler_f);
	type_handlers_ptr[4] = HANDLER_D(cl_4::handler_f);
	type_handlers_ptr[5] = HANDLER_D(cl_5::handler_f);
	type_handlers_ptr[6] = HANDLER_D(cl_6::handler_f);
	while (true) {
		objects.clear();
		std::getline(std::cin, command, '\n');
		for (int i = 0; i < command.size(); ++i) {
			std::string obj_name = "";
			while (command[i] != ' ' && i < command.size()) {
				obj_name = obj_name + command[i];
				++i;
			}
			objects.push_back(obj_name);
		}

		if (objects[0] == "SET") {
			if (objects[1][0] == '/') {
				pointer = get_p_global_hierarchy(objects[1]);
			}
			else {
				pointer = pointer->get_p_global_hierarchy(objects[1]);
			}
			if (pointer) {
				std::cout << "Object is set: " << pointer->get_s_object_name() << '\n';
			}
			else {
				std::cout << "The object was not found at the specified coordinate:  " << objects[1] << '\n';
			}
		}
		else if (objects[0] == "FIND") {
			cl_base* finding_pointer = pointer->get_p_global_hierarchy(objects[1]);
			if (finding_pointer) {
				std::cout << objects[1] << "     Object name: " << finding_pointer->get_s_object_name() << '\n';
			}
			else {
				std::cout << objects[1] << "     Object is not found\n";
			}
		}
		else if (objects[0] == "MOVE") {
			cl_base* cur_pointer = this;
			if (objects[1][0] == '/') {
				cur_pointer = get_p_global_hierarchy(objects[1]);
			}
			else {
				cur_pointer = pointer->get_p_global_hierarchy(objects[1]);
			}
			if (cur_pointer) {
				if (!(pointer->get_p_from_this_hierarchy(cur_pointer))) {
					if (!(cur_pointer->get_p_child(pointer->get_s_object_name()))) {
						pointer->set_p_head_object(cur_pointer) << '\n';
						std::cout << "New head object: " << cur_pointer->get_s_object_name() << '\n';
					}
					else {
						std::cout << objects[1] << "     Dubbing the names of subordinate objects\n";
					}
				}
				else {
					std::cout << objects[1] << "     Redefining the head object failed\n";
				}
			}
			else {
				std::cout << objects[1] << "     Head object is not found\n";
			}
		}
		else if (objects[0] == "DELETE") {
			std::string absolute_coordinate = pointer->get_p_absolute_coordinate(objects[1]);
			if (pointer->delete_child(objects[1])) {
				std::cout << "The object " << absolute_coordinate << " has been deleted\n";
			}
		}
		else if (objects[0] == "EMIT") {

			std::string message = "";

			for (int i = 2; i < objects.size(); ++i) {
				if (i + 1 < objects.size()) {
					message = message + objects[i] + ' ';
				}
				else {
					message = message + objects[i];
				}
			}
			cl_base* ob = get_p_global_hierarchy(objects[1]);
			if (ob) {
				int i_ob = ob->get_num();
				ob->emit_signal(type_signals_ptr[i_ob], message);
			}
			else {
				std::cout << "Object " << objects[1] << " not found\n";
			}
		}
		else if (objects[0] == "SET_CONNECT") {
			cl_base* sender = get_p_global_hierarchy(objects[1]);
			cl_base* getter = get_p_global_hierarchy(objects[2]);
			if (sender && getter) {
				int i_sender = sender->get_num();
				int i_getter = getter->get_num();
				sender->set_connect(type_signals_ptr[i_sender], getter, type_handlers_ptr[i_getter]);
			}
			else if (!sender) {
				std::cout << "Object " << objects[1] << " not found\n";
			}
			else {
				std::cout << "Handler object " << objects[2] << " not found\n";
			}
		}
		else if (objects[0] == "DELETE_CONNECT") {
			cl_base* sender = get_p_global_hierarchy(objects[1]);
			cl_base* getter = get_p_global_hierarchy(objects[2]);
			if (sender && getter) {
				int i_sender = sender->get_num();
				int i_getter = getter->get_num();
				sender->delete_connect(type_signals_ptr[i_sender], getter, type_handlers_ptr[i_getter]);
			}
			else if (!sender) {
				std::cout << "Object " << objects[1] << " not found\n";
			}
			else {
				std::cout << "Handler object " << objects[2] << " not found\n";
			}
		}
		else if (objects[0] == "SET_CONDITION") {
			cl_base* obj = get_p_global_hierarchy(objects[1]);
			if (obj) {
				obj->set_state(objects[2]);
			}
			else {
				std::cout << "Object " << objects[1] << " not found\n";
			}
		}
		else if (objects[0] == "END") {
			return 0;
		}
	}
	return 0;
}

cl_app::~cl_app() {}