
#include "SubjectIndex.h"
#include <fstream>

std::string RetTermName(char line[]) {

	using namespace std;
	string line_s(line);
	int pos = line_s.find(",");
	line_s = line_s.substr(0, pos);
	size_t index = 0;

	while ((index = line_s.find("  ")) != std::string::npos)line_s.erase(index, 1);

	return line_s;

}

unsigned int RetPageNumber(char line[]) {

	using namespace std;
	string line_s(line);
	int pos = line_s.find(",") + 1;
	int number = 0;

	if (pos != 0) {

		line_s = line_s.substr(pos);
		number = std::stoi(line_s);

	}

	return number;

}
bool ReadLaforeSubjectIndex(ndx::SubjectIndex* subject_index) {

	using namespace std;
	ifstream file;

	file.open("terms.txt", ios::in);

	if (!file.is_open()) return false;

	char line[100];

	string termin, under_termin, under_under_termin;

	while (file.getline(line, 100)) {

		int index = 0;
		while (line[index] == '\t') index++;

		int page;

		switch (index) {
		case 0: {

			termin = RetTermName(line);
			page = RetPageNumber(line);
			subject_index->AddTermin(termin, page);

			break;
		}

		case 1: {

			under_termin = RetTermName(line);
			page = RetPageNumber(line);
			subject_index->AddUnderTermin(termin, under_termin, page);

			break;
		}

		case 2: {

			under_under_termin = RetTermName(line);
			page = RetPageNumber(line);
			subject_index->AddUnderUnderTermin(termin, under_termin, under_under_termin, page);

			break;
		}

		};

	}

}


class SubjectIndexInterface {

	enum Command {

		FIND_TERMIN = 0,
		ADD_TERMIN,
		ADD_UNDERTERMIN,
		ADD_PAGE,
		DELETE_TERMIN,
		DELETE_UNDERTERMIN,
		DELETE_PAGE,
		EDIT_TERM,
		SORT_TERMS,
		SORT_PAGES,
		SHOW_SUBJECT_INDEX,
		SORT_UNDERTERMS,
		FIND_UNDERTERMIN,
		SAFE_AND_EXIT,
		EXIT_WITHOUT_SAVING,
		NOTHING

	};

private:

	ndx::SubjectIndex subject_index;
	const char* const menu_string = "_____________________\n"
									"0. Find term+\n"
									"1. Add termin+\n"
									"2. Add underterm\n"
									"3. Add page\n"
									"4. Delete term\n"
									"5. Delete underterm\n"
									"6. Delete page\n"
									"7. Edit term\n"
									"8. Sort terms+\n"
									"9. Sort pages\n"
									"10. Show subject index+\n"
									"11. Sort underterms\n"
									"12. Find underterm\n"
									"13. Safe and exit\n"
									"14. Exit without saving\n"
									"_____________________\n";

	inline void PrintMenu()const { std::cout << menu_string; }

	Command ReadCommand()const {

		unsigned int  input_command;
		std::cin >> input_command;
		return (Command)input_command;

	}

	void PrintTerminInfo(const ndx::Termin termin) {

		using namespace std;
		cout << termin.name << ", " << termin.page << "." << endl;

	}
	ndx::Termin ScanTerminInfo() {
		using namespace std;
		string name;
		PageNumber page;
		cout << "Введите название термина: "; cin >> name;
		cout << "Введите номер страницы: "; cin >> page;
		return ndx::Termin{ name, page, nullptr};
	}

	void ProcessCommand(Command command) {

		switch (command) {
		case FIND_TERMIN: {

			using namespace std;
			using namespace ndx;

			string input_t_name;
			cout << "Введите название термина: "; cin >> input_t_name;

			try{

				const Termin& termin = subject_index.SearchTermin(input_t_name);
				PrintTerminInfo(termin);
				
				for (size_t i = 0; i < termin.under_termins->size(); i++)
				{
					const ListElement& under_termin = (*termin.under_termins)[i];
					cout << '\t' << under_termin.name << ", " << (*under_termin.page_list_ptr)[0];

				}

			}
			catch (ndx::SubjectIndexException exception) {

				cerr << exception.What() << endl;
			}

			system("pause");

			break;
		}

		case ADD_TERMIN: {

			ndx::Termin termin = ScanTerminInfo();
			subject_index.AddTermin(termin.name, termin.page);

			break;
		}
		
		case SHOW_SUBJECT_INDEX: {

			subject_index.Print();
			system("pause");
			break;
		}

		case SORT_TERMS: {

			subject_index.SortTerminsNames();
			break;
		}
		case ADD_UNDERTERMIN: {

			using namespace std;
			string termin_name;
			cout << "Ведите название термина: "; cin >> termin_name;
			ndx::Termin under_termin = ScanTerminInfo();
			subject_index.AddUnderTermin(termin_name, under_termin.name, under_termin.page);
			break;
		}
		case EDIT_TERM: {

			using namespace std;
			string termin_name;
			cout << "Ведите название термина: "; cin >> termin_name;

			ndx::Termin termin = ScanTerminInfo();

			subject_index.EditTermin();

			break;
		}

		}

	}
protected:
public:
	void Start() {

		Command command = NOTHING;

		while ((command != EXIT_WITHOUT_SAVING) && (command != SAFE_AND_EXIT)) {

			system("cls");
			PrintMenu();
			command = ReadCommand();
			ProcessCommand(command);

		}

	}

	explicit SubjectIndexInterface()noexcept{

		ReadLaforeSubjectIndex(&subject_index);
	}

};


int main() {

	//setlocale(LC_ALL, "ru");
	system("chcp 1251");	
	SubjectIndexInterface subject_index;
	subject_index.Start();
	
	return 0;

}