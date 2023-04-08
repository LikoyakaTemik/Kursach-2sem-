#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class cl_base {
protected:
	string s_object_name = "Base_object";
	cl_base* p_head_object = nullptr;
	vector <cl_base*> subordinate_objects;
	unsigned short type = 1;
	unsigned short state = 0;
public:
	cl_base(cl_base* p_head_object, string s_object_name = "Base_object") {
		this->p_head_object = p_head_object;
		this->s_object_name = s_object_name;
		if (p_head_object) {
			p_head_object->subordinate_objects.push_back(this);
		}
	}

	bool set_s_object_name(string s_object_name) {
		if (p_head_object) {
			for (int i = 0; i < p_head_object->subordinate_objects.size(); ++i) {
				if (p_head_object->subordinate_objects[i]->s_object_name == s_object_name) {
					return false;
				}
			}
			this->s_object_name = s_object_name;
			return true;
		}
		else {
			this->s_object_name = s_object_name;
			return true;
		}
	}

	void set_state(string state) {
		int state_int = 0;
		for (int i = 0; i < state.size(); ++i) {
			state_int = state_int + (int(state[i]) - 48) * pow(10, state.size() - i - 1);
		}

		if (state_int == 0) {
			this->state = 0;
			for (int i = 0; i < subordinate_objects.size(); ++i) {
				subordinate_objects[i]->set_state(0);
			}
		}
		else {
			if (is_state_before()) {
				this->state = state_int;
			}
		}
	}

	void set_type(string type) {
		int type_int = 0;
		for (int i = 0; i < type.size(); ++i) {
			type_int = type_int + (int(type[i]) - 48) * pow(10, type.size() - i - 1);
		}

		this->type = type_int;
	}

	bool set_p_head_object(cl_base* pointer) {
							/*Метод переопределения головного объекта для
							текущего в дереве иерархии. Метод должен иметь
							один параметр, указатель на объект базового класса,
							содержащий указатель на новый головной объект.
							Переопределение головного объект для корневого
							объекта недопустимо. Недопустимо создать второй
							корневой объект. Недопустимо при переопределении,
							чтобы у нового головного появились два подчиненных
							объекта с одинаковым наименованием. Новый головной
							объект не должен принадлежать к объектам из ветки
							текущего. Если переопределение выполнено, метод возвращает значение «истина», иначе «ложь»;*/
		if (pointer->get_p_head_object() != nullptr && this->get_p_head_object() != nullptr && !get_p_from_this_hierarchy(pointer->get_p_head_object()->get_s_object_name())) {
			get_p_head_object()->delete_child(get_s_object_name());
			this->p_head_object = pointer->get_p_head_object();
			return true;
		}
		else {
			return false;
		}
	}						

	bool delete_child(string name_child) {/*Метод удаления подчиненного объекта по наименованию.
											Если объект не найден, то метод завершает работу.
											Один параметр строкового типа, содержит наименование удаляемого подчиненного объекта;*/
		if (get_p_child(name_child) != nullptr) {
			subordinate_objects.erase(find(subordinate_objects.begin(), subordinate_objects.end(), get_p_child(name_child)));
			return true;
			
		}
		else {
			return false;
		}
			
	}

	bool is_state_before() {
		if (get_p_head_object() != nullptr && get_p_head_object()->state != 0) {
			return true;
		}
		else if (get_p_head_object() == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	bool is_correct_type(string type) {
		int type_int = 0;
		for (int i = 0; i < type.size(); ++i) {
			type_int = type_int + (int(type[i]) - 48) * pow(10, type.size() - i - 1);
		}
		if (type_int >= 2 && type_int <= 6) {
			return true;
		}
		else {
			return false;
		}
	}

	bool is_uniq_name(string name) {
		for (int i = 0; i < subordinate_objects.size(); ++i) {
			if (subordinate_objects[i]->get_s_object_name() == name) {
				return false;
			}
			else {
				subordinate_objects[i]->is_uniq_name(name);
			}
		}
		return true;
	}

	bool is_global_uniq_name(string name) {
		if (find(name.begin(), name.end(), '/') == name.end() && find(name.begin(), name.end(), '.') == name.end()) {

			cl_base* pointer_object = this;
			while (pointer_object->p_head_object != nullptr) {
				pointer_object = pointer_object->p_head_object;
			}
			return pointer_object->is_uniq_name(name);
		}
		else {
			return false;
		}
	}

	string get_s_object_name() {
		return s_object_name;
	}

	cl_base* get_p_head_object() {
		return p_head_object;
	}

	string get_state() {
		if (state != 0) {
			return "is ready";
		}
		else {
			return "is not ready";
		}
	}

	void print_s_object_name_tree() {
		int lvl = 1;
		cl_base* pointer_object = this;
		vector <cl_base*> ordinate_objects;
		while (pointer_object->p_head_object != nullptr) {
			ordinate_objects.push_back(pointer_object);
			pointer_object = pointer_object->p_head_object;
		}

		cout << pointer_object->get_s_object_name() << '\n';

		while (pointer_object != this) {
			for (int i = 0; i < pointer_object->subordinate_objects.size(); ++i) {
				for (int blank = 0; blank < lvl * 4; ++blank) {
					cout << ' ';
				}
				cout << pointer_object->subordinate_objects[i]->get_s_object_name() << '\n';
			}
			pointer_object = ordinate_objects[ordinate_objects.size() - lvl];
			lvl++;
		}

		for (int i = 0; i < pointer_object->subordinate_objects.size(); ++i) {
			for (int blank = 0; blank < lvl * 4; ++blank) {
				cout << ' ';
			}
			cout << pointer_object->subordinate_objects[i]->get_s_object_name() << '\n';
		}
	}

	cl_base* get_p_child(string child_name) {

		for (int i = 0; i < subordinate_objects.size(); ++i) {
			if (subordinate_objects[i]->get_s_object_name() == child_name) {
				return subordinate_objects[i];
			}
		}
		return nullptr;
	}

	cl_base* get_p_from_this_hierarchy(string finding_name) {
		cl_base* ptr_child = get_p_child(finding_name);
		if (ptr_child != nullptr) {
			return ptr_child;
		}
		else {
			for (int i = 0; i < subordinate_objects.size(); ++i) {
				ptr_child = subordinate_objects[i]->get_p_from_this_hierarchy(finding_name);
				if (ptr_child != nullptr) {
					return ptr_child;
				}
			}
			return nullptr;
		}
	}
	/*Метод получения указателя на любой объект в составе дерева иерархии объектов согласно пути (координаты).
	В качестве параметра методу передать путь (координату) объекта. Координата задаться в следующем виде:
	/ - корневой объект;
	//«имя объекта» - поиск объекта по уникальной имени от корневого (для однозначности уникальность требуется в рамках дерева);
	. - текущий объект;
	.«имя объекта» - поиск объекта по уникальной имени от текущего (для однозначности уникальность требуется в рамках ветви дерева от текущего объекта);
	«имя объекта 1»[/«имя объекта 2»] . . . - относительная координата от текущего объекта, «имя объекта 1» подчиненный текущего;
	/«имя объекта 1»[/«имя объекта 2»]  . . . - абсолютная координата от корневого объекта.
	*/
	cl_base* get_p_global_hierarchy(string coordinate) {
		cl_base* pointer_object = this;
		vector<string> objs = coordinate_parse(coordinate);
		if(objs.size() == 1){
			if (objs[0] == "/") {
				while (pointer_object->get_p_head_object() != nullptr) {
					pointer_object = pointer_object->get_p_head_object();
				}
				return pointer_object;
			}
			else if (objs[0][0] == '/' && objs[0][1] == '/') {
				string finding_name = "";
				for (int i = 2; i < objs[0].size(); ++i) {
					finding_name += objs[0][i];
				}

				while (pointer_object->get_p_head_object() != nullptr) {
					pointer_object = pointer_object->get_p_head_object();
				}
				return pointer_object->get_p_from_this_hierarchy(finding_name);
			}
			else if (objs[0] == ".") {
				return this;
			}
			else if(objs[0][0] == '.'){
				string finding_name = "";
				for (int i = 1; i < objs[0].size(); ++i) {
					finding_name += objs[0][i];
				}
				return get_p_from_this_hierarchy(finding_name);
			}
			else if (objs[0][0] == '/') {
				string finding_name = "";
				for (int i = 1; i < objs[0].size(); ++i) {
					finding_name += objs[0][i];
				}
				while (pointer_object->get_p_head_object() != nullptr) {
					pointer_object = pointer_object->get_p_head_object();
				}
				return pointer_object->get_p_child(finding_name);
			}
			else {
				string finding_name = "";
				for (int i = 0; i < objs[0].size(); ++i) {
					finding_name += objs[0][i];
				}

				return get_p_child(finding_name);
			}
		}
		else {
			if (objs[0][0] == '/') {
				// «имя объекта 1»[/ «имя объекта 2»] . . . - относительная координата от текущего объекта, «имя объекта 1» подчиненный текущего;
				// /«имя объекта 1»[/ «имя объекта 2»]  . . . - абсолютная координата от корневого объекта.
				while (pointer_object->get_p_head_object() != nullptr) {
					pointer_object = pointer_object->get_p_head_object();
				}
				for (int i = 0; i < objs.size(); ++i) {
					string finding_name = "";
					for (int o = 1; o < objs[i].size(); ++o) {
						finding_name += objs[i][o];
					}
					pointer_object = pointer_object->get_p_child(finding_name);
				}
				return pointer_object;
			}
			else {
				string finding_name = "";
				for (int o = 0; o < objs[0].size(); ++o) {
					finding_name += objs[0][o];
				}
				pointer_object = pointer_object->get_p_child(finding_name);

				for (int i = 1; i < objs.size(); ++i) {
					string finding_name = "";
					for (int o = 1; o < objs[i].size(); ++o) {
						finding_name += objs[i][o];
					}
					pointer_object = pointer_object->get_p_child(finding_name);
				}
				return pointer_object;
			}
		}
	}

	void print_hiararchy_from_this(int lvl = 0) {
		for (int i = 0; i < subordinate_objects.size(); ++i) {
			for (int blank = 0; blank < lvl * 4; ++blank) {
				cout << ' ';
			}
			cout << subordinate_objects[i]->get_s_object_name() << '\n';
			print_hiararchy_from_this(lvl + 1);
		}
	}

	void print_hiararchy_state_from_this(int lvl = 1) {
		for (int i = 0; i < subordinate_objects.size(); ++i) {
			for (int blank = 0; blank < lvl * 4; ++blank) {
				cout << ' ';
			}
			cout << subordinate_objects[i]->get_s_object_name() << " " << subordinate_objects[i]->get_state() << '\n';
			subordinate_objects[i]->print_hiararchy_state_from_this(lvl + 1);
		}
	}

	void print_global_hierarchy_state() {
		cl_base* pointer_object = this;
		while (pointer_object->p_head_object != nullptr) {
			pointer_object = pointer_object->get_p_head_object();
		}
		cout << pointer_object->get_s_object_name() << " " << pointer_object->get_state() << '\n';
		pointer_object->print_hiararchy_state_from_this();
	}

	void print_hiararchy(int lvl = 1) {
		for (int i = 0; i < subordinate_objects.size(); ++i) {
			for (int blank = 0; blank < lvl * 4; ++blank) {
				cout << ' ';
			}
			cout << subordinate_objects[i]->get_s_object_name() << " " << subordinate_objects[i] << '\n';
			subordinate_objects[i]->print_hiararchy(lvl + 1);
		}
	}

	void print_global_hierarchy() {
		cl_base* pointer_object = this;
		while (pointer_object->p_head_object != nullptr) {
			pointer_object = pointer_object->get_p_head_object();
		}
		cout << pointer_object->get_s_object_name() << '\n';
		pointer_object->print_hiararchy();
	}

	vector<string> coordinate_parse(string coordinate) {
		vector<string>command;
		string str = "";
		for (int i = 0; i < coordinate.size(); ++i) {
			if (coordinate[i] != '/' && coordinate[i] != '.') {
				str = str + coordinate[i];
			}
			else {
				if (str.size() == 0) {
					str = str + coordinate[i];
				}
				else if (coordinate[i - 1] == '/' && coordinate[i] == '/') {
					str = str + coordinate[i];
				}
				else {
					command.push_back(str);
					str = coordinate[i];
				}
			}
		}
		command.push_back(str);
		return command;
	}
};

class cl_app :public cl_base {
private:
	cl_base* pointer;
public:
	cl_app(cl_base* p_head_object) :cl_base(p_head_object) {}

	void build_tree_objects() {
		vector<string> objects;
		string command;
		getline(cin, command, '\n');
		set_s_object_name(command);
		while (true) {
			objects.clear();
			getline(cin, command, '\n');
			for (int i = 0; i < command.size(); ++i) {
				string obj_name = "";
				while (command[i] != ' ' && i < command.size()) {
					obj_name = obj_name + command[i];
					++i;
				}
				objects.push_back(obj_name);
			}
			if (objects.size() != 1) {
				if (objects[0] == get_s_object_name()) {
					cl_base* ob;
					if (objects[1] != get_s_object_name() && is_correct_type(objects[2])) {
						ob = new cl_base(this, objects[1]);
						ob->set_type(objects[2]);
					}
					pointer = this;
				}
				else {
					if (objects[0] != pointer->get_s_object_name() && is_global_uniq_name(objects[1]) && is_correct_type(objects[2])) {
						pointer = pointer->get_p_global_hierarchy(objects[0]);
						cl_base* ob;
						ob = new cl_base(pointer, objects[1]);
						ob->set_type(objects[2]);
					}
					else {
						if (is_global_uniq_name(objects[1]) && is_correct_type(objects[2])) {
							cl_base* ob;
							ob = new cl_base(pointer, objects[1]);
							ob->set_type(objects[2]);
						}
					}
				}
			}
			else {
				break;
			}
		}

		while (true) {
			objects.clear();
			getline(cin, command, '\n');
			for (int i = 0; i < command.size(); ++i) {
				string obj_name = "";
				while (command[i] != ' ' && i < command.size()) {
					obj_name = obj_name + command[i];
					++i;
				}
				objects.push_back(obj_name);
			}

			/*
			for (int i = 0; i < objects.size(); ++i) {
				cout << objects[i] << " ";
			}*/

			if (objects.size() == 2) {
				if (objects[0] != get_s_object_name()) {
					get_p_from_this_hierarchy(objects[0])->set_state(objects[1]);
				}
				else {
					set_state(objects[1]);
				}
			}
			else {
				return;
			}
		}
	}

	int exec_app() {
		print_global_hierarchy();
		cout << "The tree of objects and their readiness\n";
		print_global_hierarchy_state();
		return 0;
	}
};

int main() {

	cl_app ob_cl_app(nullptr);
	ob_cl_app.build_tree_objects();
	return ob_cl_app.exec_app();
}