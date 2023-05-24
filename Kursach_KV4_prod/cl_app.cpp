﻿#include "cl_app.h"
#include "cl_2.h"
#include "cl_3.h"
#include "cl_4.h"
#include "cl_5.h"
#include "cl_6.h"
#include "cl_base.h"
#include <iostream>
#include <vector>
#include <string>

cl_app::cl_app(cl_base* p_head_object) :cl_base(p_head_object) {}

int cl_app::build_tree_objects() {
	cl_base* pointer = this;
	std::vector<std::string> objects;
	std::string command;
	//Построение дерева
	std::getline(std::cin, command, '\n');
	set_s_object_name(command);
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
		if (objects.size() != 1) {
			if (get_p_global_hierarchy(objects[0]) == this) {
				//std::cout << "get>>" << get_p_global_hierarchy(objects[0]) << " should_be>>" << this << '\n';
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
						//std::cout << "get>>" << get_p_global_hierarchy(objects[0]) << " name: " << pointer->get_s_object_name() << '\n';
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
		for (int i = 0; i < command.size(); ++i) {
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
			//std::cout << getter->get_s_object_name() << "<<<<<\n";
			if (sender && getter) {
				int i_sender = sender->get_num();
				int i_getter = getter->get_num();
				//std::cout << i_getter << "<<<<<\n";
				switch (i_sender)
				{
				default:
					break;
				case 1:
					switch (i_getter)
					{
					default:
						break;
					case 1:
						sender->set_connect(SIGNAL_D(cl_app::signal_f), getter, HANDLER_D(cl_app::handler_f));
						break;
					case 2:
						sender->set_connect(SIGNAL_D(cl_app::signal_f), getter, HANDLER_D(cl_2::handler_f));
						break;
					case 3:
						sender->set_connect(SIGNAL_D(cl_app::signal_f), getter, HANDLER_D(cl_3::handler_f));
						break;
					case 4:
						sender->set_connect(SIGNAL_D(cl_app::signal_f), getter, HANDLER_D(cl_4::handler_f));
						break;
					case 5:
						sender->set_connect(SIGNAL_D(cl_app::signal_f), getter, HANDLER_D(cl_5::handler_f));
						break;
					case 6:
						sender->set_connect(SIGNAL_D(cl_app::signal_f), getter, HANDLER_D(cl_6::handler_f));
						break;
					}
				case 2:
					switch (i_getter)
					{
					default:
						break;
					case 1:
						sender->set_connect(SIGNAL_D(cl_2::signal_f), getter, HANDLER_D(cl_app::handler_f));
						break;
					case 2:
						sender->set_connect(SIGNAL_D(cl_2::signal_f), getter, HANDLER_D(cl_2::handler_f));
						break;
					case 3:
						sender->set_connect(SIGNAL_D(cl_2::signal_f), getter, HANDLER_D(cl_3::handler_f));
						break;
					case 4:
						sender->set_connect(SIGNAL_D(cl_2::signal_f), getter, HANDLER_D(cl_4::handler_f));
						break;
					case 5:
						sender->set_connect(SIGNAL_D(cl_2::signal_f), getter, HANDLER_D(cl_5::handler_f));
						break;
					case 6:
						sender->set_connect(SIGNAL_D(cl_2::signal_f), getter, HANDLER_D(cl_6::handler_f));
						break;
					}
				case 3:
					switch (i_getter)
					{
					default:
						break;
					case 1:
						sender->set_connect(SIGNAL_D(cl_3::signal_f), getter, HANDLER_D(cl_app::handler_f));
						break;
					case 2:
						sender->set_connect(SIGNAL_D(cl_3::signal_f), getter, HANDLER_D(cl_2::handler_f));
						break;
					case 3:
						sender->set_connect(SIGNAL_D(cl_3::signal_f), getter, HANDLER_D(cl_3::handler_f));
						break;
					case 4:
						sender->set_connect(SIGNAL_D(cl_3::signal_f), getter, HANDLER_D(cl_4::handler_f));
						break;
					case 5:
						sender->set_connect(SIGNAL_D(cl_3::signal_f), getter, HANDLER_D(cl_5::handler_f));
						break;
					case 6:
						sender->set_connect(SIGNAL_D(cl_3::signal_f), getter, HANDLER_D(cl_6::handler_f));
						break;
					}
				case 4:
					switch (i_getter)
					{
					default:
						break;
					case 1:
						sender->set_connect(SIGNAL_D(cl_4::signal_f), getter, HANDLER_D(cl_app::handler_f));
						break;
					case 2:
						sender->set_connect(SIGNAL_D(cl_4::signal_f), getter, HANDLER_D(cl_2::handler_f));
						break;
					case 3:
						sender->set_connect(SIGNAL_D(cl_4::signal_f), getter, HANDLER_D(cl_3::handler_f));
						break;
					case 4:
						sender->set_connect(SIGNAL_D(cl_4::signal_f), getter, HANDLER_D(cl_4::handler_f));
						break;
					case 5:
						sender->set_connect(SIGNAL_D(cl_4::signal_f), getter, HANDLER_D(cl_5::handler_f));
						break;
					case 6:
						sender->set_connect(SIGNAL_D(cl_4::signal_f), getter, HANDLER_D(cl_6::handler_f));
						break;
					}
				case 5:
					switch (i_getter)
					{
					default:
						break;
					case 1:
						sender->set_connect(SIGNAL_D(cl_5::signal_f), getter, HANDLER_D(cl_app::handler_f));
						break;
					case 2:
						sender->set_connect(SIGNAL_D(cl_5::signal_f), getter, HANDLER_D(cl_2::handler_f));
						break;
					case 3:
						sender->set_connect(SIGNAL_D(cl_5::signal_f), getter, HANDLER_D(cl_3::handler_f));
						break;
					case 4:
						sender->set_connect(SIGNAL_D(cl_5::signal_f), getter, HANDLER_D(cl_4::handler_f));
						break;
					case 5:
						sender->set_connect(SIGNAL_D(cl_5::signal_f), getter, HANDLER_D(cl_5::handler_f));
						break;
					case 6:
						sender->set_connect(SIGNAL_D(cl_5::signal_f), getter, HANDLER_D(cl_6::handler_f));
						break;
					}
				case 6:
					switch (i_getter)
					{
					default:
						break;
					case 1:
						sender->set_connect(SIGNAL_D(cl_6::signal_f), getter, HANDLER_D(cl_app::handler_f));
						break;
					case 2:
						sender->set_connect(SIGNAL_D(cl_6::signal_f), getter, HANDLER_D(cl_2::handler_f));
						break;
					case 3:
						sender->set_connect(SIGNAL_D(cl_6::signal_f), getter, HANDLER_D(cl_3::handler_f));
						break;
					case 4:
						sender->set_connect(SIGNAL_D(cl_6::signal_f), getter, HANDLER_D(cl_4::handler_f));
						break;
					case 5:
						sender->set_connect(SIGNAL_D(cl_6::signal_f), getter, HANDLER_D(cl_5::handler_f));
						break;
					case 6:
						sender->set_connect(SIGNAL_D(cl_6::signal_f), getter, HANDLER_D(cl_6::handler_f));
						break;
					}
				}
			}
			else if (!sender) {
				std::cout << "Object " << objects[0] << " not found\n";
			}
			else {
				std::cout << "Handler object " << objects[1] << " not found\n";
			}
		}
	}

	//Отработка системы
	pointer = this;
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
			//std::cout << "\n>>" << objects[1] << '\n';
			//std::cout << "\n>>" << pointer << " name: "<< pointer->get_s_object_name() << '\n';
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
			//std::cout << ">>" << pointer << '\n';
			if (objects[1][0] == '/') {
				cur_pointer = get_p_global_hierarchy(objects[1]);
			}
			else {
				cur_pointer = pointer->get_p_global_hierarchy(objects[1]);
			}
			if (cur_pointer) {//Ïðîâåðêà íà ñóùåñòâîâàíèå ãîëîâíîãî îáúåêòà
				if (!(pointer->get_p_from_this_hierarchy(cur_pointer))) {//ïðîâåðêà, íå ÿâëÿåòñÿ ëè íîâûé ãîëîâíîé îáúåêò ïîòîìêîì òåêóùåãî
					if (!(cur_pointer->get_p_child(pointer->get_s_object_name()))) {//ïðîâåðêà íà äóáëèêàòû èì¸í äëÿ ãîëîâíîãî îáúåêòà
						pointer->set_p_head_object(cur_pointer) << '\n';
						//std::cout << ">>" << pointer->get_p_head_object() << '\n';
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
			//std::cout << "\n>>" << message << "<<\n";
			cl_base* ob = get_p_global_hierarchy(objects[1]);
			if (ob) {
				int i_ob = ob->get_num();
				switch (i_ob)
				{
				default:
					break;
				case 1:
					ob->emit_signal(SIGNAL_D(cl_app::signal_f), message);
					break;
				case 2:
					ob->emit_signal(SIGNAL_D(cl_2::signal_f), message);
					break;
				case 3:
					ob->emit_signal(SIGNAL_D(cl_3::signal_f), message);
					break;
				case 4:
					ob->emit_signal(SIGNAL_D(cl_4::signal_f), message);
					break;
				case 5:
					ob->emit_signal(SIGNAL_D(cl_5::signal_f), message);
					break;
				case 6:
					ob->emit_signal(SIGNAL_D(cl_6::signal_f), message);
					break;
				}
			}
			else {
				std::cout << "Object " << objects[1] << " not found\n";
			}
		}
		else if (objects[0] == "SET_CONNECT") {
			cl_base* sender = get_p_global_hierarchy(objects[1]);
			cl_base* getter = get_p_global_hierarchy(objects[2]);
			//std::cout << getter->get_s_object_name() << "<<<<<";
			if (sender && getter) {
				int i_sender = sender->get_num();
				int i_getter = getter->get_num();
				switch (i_sender)
				{
				default:
					break;
				case 1:
					switch (i_getter)
					{
					default:
						break;
					case 1:
						sender->set_connect(SIGNAL_D(cl_app::signal_f), getter, HANDLER_D(cl_app::handler_f));
						break;
					case 2:
						sender->set_connect(SIGNAL_D(cl_app::signal_f), getter, HANDLER_D(cl_2::handler_f));
						break;
					case 3:
						sender->set_connect(SIGNAL_D(cl_app::signal_f), getter, HANDLER_D(cl_3::handler_f));
						break;
					case 4:
						sender->set_connect(SIGNAL_D(cl_app::signal_f), getter, HANDLER_D(cl_4::handler_f));
						break;
					case 5:
						sender->set_connect(SIGNAL_D(cl_app::signal_f), getter, HANDLER_D(cl_5::handler_f));
						break;
					case 6:
						sender->set_connect(SIGNAL_D(cl_app::signal_f), getter, HANDLER_D(cl_6::handler_f));
						break;
					}
				case 2:
					switch (i_getter)
					{
					default:
						break;
					case 1:
						sender->set_connect(SIGNAL_D(cl_2::signal_f), getter, HANDLER_D(cl_app::handler_f));
						break;
					case 2:
						sender->set_connect(SIGNAL_D(cl_2::signal_f), getter, HANDLER_D(cl_2::handler_f));
						break;
					case 3:
						sender->set_connect(SIGNAL_D(cl_2::signal_f), getter, HANDLER_D(cl_3::handler_f));
						break;
					case 4:
						sender->set_connect(SIGNAL_D(cl_2::signal_f), getter, HANDLER_D(cl_4::handler_f));
						break;
					case 5:
						sender->set_connect(SIGNAL_D(cl_2::signal_f), getter, HANDLER_D(cl_5::handler_f));
						break;
					case 6:
						sender->set_connect(SIGNAL_D(cl_2::signal_f), getter, HANDLER_D(cl_6::handler_f));
						break;
					}
				case 3:
					switch (i_getter)
					{
					default:
						break;
					case 1:
						sender->set_connect(SIGNAL_D(cl_3::signal_f), getter, HANDLER_D(cl_app::handler_f));
						break;
					case 2:
						sender->set_connect(SIGNAL_D(cl_3::signal_f), getter, HANDLER_D(cl_2::handler_f));
						break;
					case 3:
						sender->set_connect(SIGNAL_D(cl_3::signal_f), getter, HANDLER_D(cl_3::handler_f));
						break;
					case 4:
						sender->set_connect(SIGNAL_D(cl_3::signal_f), getter, HANDLER_D(cl_4::handler_f));
						break;
					case 5:
						sender->set_connect(SIGNAL_D(cl_3::signal_f), getter, HANDLER_D(cl_5::handler_f));
						break;
					case 6:
						sender->set_connect(SIGNAL_D(cl_3::signal_f), getter, HANDLER_D(cl_6::handler_f));
						break;
					}
				case 4:
					switch (i_getter)
					{
					default:
						break;
					case 1:
						sender->set_connect(SIGNAL_D(cl_4::signal_f), getter, HANDLER_D(cl_app::handler_f));
						break;
					case 2:
						sender->set_connect(SIGNAL_D(cl_4::signal_f), getter, HANDLER_D(cl_2::handler_f));
						break;
					case 3:
						sender->set_connect(SIGNAL_D(cl_4::signal_f), getter, HANDLER_D(cl_3::handler_f));
						break;
					case 4:
						sender->set_connect(SIGNAL_D(cl_4::signal_f), getter, HANDLER_D(cl_4::handler_f));
						break;
					case 5:
						sender->set_connect(SIGNAL_D(cl_4::signal_f), getter, HANDLER_D(cl_5::handler_f));
						break;
					case 6:
						sender->set_connect(SIGNAL_D(cl_4::signal_f), getter, HANDLER_D(cl_6::handler_f));
						break;
					}
				case 5:
					switch (i_getter)
					{
					default:
						break;
					case 1:
						sender->set_connect(SIGNAL_D(cl_5::signal_f), getter, HANDLER_D(cl_app::handler_f));
						break;
					case 2:
						sender->set_connect(SIGNAL_D(cl_5::signal_f), getter, HANDLER_D(cl_2::handler_f));
						break;
					case 3:
						sender->set_connect(SIGNAL_D(cl_5::signal_f), getter, HANDLER_D(cl_3::handler_f));
						break;
					case 4:
						sender->set_connect(SIGNAL_D(cl_5::signal_f), getter, HANDLER_D(cl_4::handler_f));
						break;
					case 5:
						sender->set_connect(SIGNAL_D(cl_5::signal_f), getter, HANDLER_D(cl_5::handler_f));
						break;
					case 6:
						sender->set_connect(SIGNAL_D(cl_5::signal_f), getter, HANDLER_D(cl_6::handler_f));
						break;
					}
				case 6:
					switch (i_getter)
					{
					default:
						break;
					case 1:
						sender->set_connect(SIGNAL_D(cl_6::signal_f), getter, HANDLER_D(cl_app::handler_f));
						break;
					case 2:
						sender->set_connect(SIGNAL_D(cl_6::signal_f), getter, HANDLER_D(cl_2::handler_f));
						break;
					case 3:
						sender->set_connect(SIGNAL_D(cl_6::signal_f), getter, HANDLER_D(cl_3::handler_f));
						break;
					case 4:
						sender->set_connect(SIGNAL_D(cl_6::signal_f), getter, HANDLER_D(cl_4::handler_f));
						break;
					case 5:
						sender->set_connect(SIGNAL_D(cl_6::signal_f), getter, HANDLER_D(cl_5::handler_f));
						break;
					case 6:
						sender->set_connect(SIGNAL_D(cl_6::signal_f), getter, HANDLER_D(cl_6::handler_f));
						break;
					}
				}
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
				switch (i_sender)
				{
				default:
					break;
				case 1:
					switch (i_getter)
					{
					default:
						break;
					case 1:
						sender->delete_connect(SIGNAL_D(cl_app::signal_f), getter, HANDLER_D(cl_app::handler_f));
						break;
					case 2:
						sender->delete_connect(SIGNAL_D(cl_app::signal_f), getter, HANDLER_D(cl_2::handler_f));
						break;
					case 3:
						sender->delete_connect(SIGNAL_D(cl_app::signal_f), getter, HANDLER_D(cl_3::handler_f));
						break;
					case 4:
						sender->delete_connect(SIGNAL_D(cl_app::signal_f), getter, HANDLER_D(cl_4::handler_f));
						break;
					case 5:
						sender->delete_connect(SIGNAL_D(cl_app::signal_f), getter, HANDLER_D(cl_5::handler_f));
						break;
					case 6:
						sender->delete_connect(SIGNAL_D(cl_app::signal_f), getter, HANDLER_D(cl_6::handler_f));
						break;
					}
				case 2:
					switch (i_getter)
					{
					default:
						break;
					case 1:
						sender->delete_connect(SIGNAL_D(cl_2::signal_f), getter, HANDLER_D(cl_app::handler_f));
						break;
					case 2:
						sender->delete_connect(SIGNAL_D(cl_2::signal_f), getter, HANDLER_D(cl_2::handler_f));
						break;
					case 3:
						sender->delete_connect(SIGNAL_D(cl_2::signal_f), getter, HANDLER_D(cl_3::handler_f));
						break;
					case 4:
						sender->delete_connect(SIGNAL_D(cl_2::signal_f), getter, HANDLER_D(cl_4::handler_f));
						break;
					case 5:
						sender->delete_connect(SIGNAL_D(cl_2::signal_f), getter, HANDLER_D(cl_5::handler_f));
						break;
					case 6:
						sender->delete_connect(SIGNAL_D(cl_2::signal_f), getter, HANDLER_D(cl_6::handler_f));
						break;
					}
				case 3:
					switch (i_getter)
					{
					default:
						break;
					case 1:
						sender->delete_connect(SIGNAL_D(cl_3::signal_f), getter, HANDLER_D(cl_app::handler_f));
						break;
					case 2:
						sender->delete_connect(SIGNAL_D(cl_3::signal_f), getter, HANDLER_D(cl_2::handler_f));
						break;
					case 3:
						sender->delete_connect(SIGNAL_D(cl_3::signal_f), getter, HANDLER_D(cl_3::handler_f));
						break;
					case 4:
						sender->delete_connect(SIGNAL_D(cl_3::signal_f), getter, HANDLER_D(cl_4::handler_f));
						break;
					case 5:
						sender->delete_connect(SIGNAL_D(cl_3::signal_f), getter, HANDLER_D(cl_5::handler_f));
						break;
					case 6:
						sender->delete_connect(SIGNAL_D(cl_3::signal_f), getter, HANDLER_D(cl_6::handler_f));
						break;
					}
				case 4:
					switch (i_getter)
					{
					default:
						break;
					case 1:
						sender->delete_connect(SIGNAL_D(cl_4::signal_f), getter, HANDLER_D(cl_app::handler_f));
						break;
					case 2:
						sender->delete_connect(SIGNAL_D(cl_4::signal_f), getter, HANDLER_D(cl_2::handler_f));
						break;
					case 3:
						sender->delete_connect(SIGNAL_D(cl_4::signal_f), getter, HANDLER_D(cl_3::handler_f));
						break;
					case 4:
						sender->delete_connect(SIGNAL_D(cl_4::signal_f), getter, HANDLER_D(cl_4::handler_f));
						break;
					case 5:
						sender->delete_connect(SIGNAL_D(cl_4::signal_f), getter, HANDLER_D(cl_5::handler_f));
						break;
					case 6:
						sender->delete_connect(SIGNAL_D(cl_4::signal_f), getter, HANDLER_D(cl_6::handler_f));
						break;
					}
				case 5:
					switch (i_getter)
					{
					default:
						break;
					case 1:
						sender->delete_connect(SIGNAL_D(cl_5::signal_f), getter, HANDLER_D(cl_app::handler_f));
						break;
					case 2:
						sender->delete_connect(SIGNAL_D(cl_5::signal_f), getter, HANDLER_D(cl_2::handler_f));
						break;
					case 3:
						sender->delete_connect(SIGNAL_D(cl_5::signal_f), getter, HANDLER_D(cl_3::handler_f));
						break;
					case 4:
						sender->delete_connect(SIGNAL_D(cl_5::signal_f), getter, HANDLER_D(cl_4::handler_f));
						break;
					case 5:
						sender->delete_connect(SIGNAL_D(cl_5::signal_f), getter, HANDLER_D(cl_5::handler_f));
						break;
					case 6:
						sender->delete_connect(SIGNAL_D(cl_5::signal_f), getter, HANDLER_D(cl_6::handler_f));
						break;
					}
				case 6:
					switch (i_getter)
					{
					default:
						break;
					case 1:
						sender->delete_connect(SIGNAL_D(cl_6::signal_f), getter, HANDLER_D(cl_app::handler_f));
						break;
					case 2:
						sender->delete_connect(SIGNAL_D(cl_6::signal_f), getter, HANDLER_D(cl_2::handler_f));
						break;
					case 3:
						sender->delete_connect(SIGNAL_D(cl_6::signal_f), getter, HANDLER_D(cl_3::handler_f));
						break;
					case 4:
						sender->delete_connect(SIGNAL_D(cl_6::signal_f), getter, HANDLER_D(cl_4::handler_f));
						break;
					case 5:
						sender->delete_connect(SIGNAL_D(cl_6::signal_f), getter, HANDLER_D(cl_5::handler_f));
						break;
					case 6:
						sender->delete_connect(SIGNAL_D(cl_6::signal_f), getter, HANDLER_D(cl_6::handler_f));
						break;
					}
				}
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
	//std::cout << "Current object hierarchy tree\n";
	//print_global_hierarchy();
	return 0;

	/*
	cl_base* p_obj;
	cl_base* p_target;
	TYPE_SIGNAL signal = SIGNAL_D(cl_2::signal_f);
	p_obj->set_connect(SIGNAL_D(cl_2::signal_f), p_target, HANDLER_D(cl_2::handler_f));
	*/
}

cl_app::~cl_app() {}