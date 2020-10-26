#include "SubjectIndex.h"
#include <memory>

class Menu {

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
		FIND_UNDERTERMIN,
		FIND_A_TERM_BY_UNDERTERM,
		SAFE_AND_EXIT,
		EXIT_WITHOUT_SAVING,
		NOTHING

	};

private:

	const string menu_string = "_____________________\n"
		"0. Find term\n"
		"1. Add termin\n"
		"2. Add underterm\n"
		"3. Add page-\n"
		"4. Delete term\n"
		"5. Delete underterm\n"
		"6. Delete page-\n"
		"7. Edit term\n"
		"8. Sort terms\n"
		"9. Sort pages\n"
		"10. Show subject index+\n"
		"11. Find underterm\n"
		"12. Find a term by underterm\n"
		"13. Safe and exit\n"
		"14. Exit without saving\n"
		"_____________________\n";

	SubjectIndex subject_index_;

	static Menu instance_;

	explicit Menu()noexcept {
		subject_index_.ReadFile("terms.txt");
	}

protected:
public:
	inline void PrintMenu()const { std::cout << menu_string; }
	Command ReadCommand()const {

		using std::cin;
		
		bool correct_input = false;
		unsigned int  input_command;

		while (!correct_input) {
			
			cin.clear();
			
			cin >> input_command;

			if (cin.good())correct_input = true;

		}
	
		return (Command)input_command;

	}

	void PrintTerminInfo(const Termin& termin)const {

		using namespace std;

		try {

			cout << termin.GetPrintString() << endl;

		}
		catch (TerminException exception) {

			cout << exception.What();

		}

	}

	const string ScanTerminName() {
		using std::cin;
		string name;
		cin.clear(); 
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> name;
		return name;
	}
	PageNumber ScanTerminPage() {
		using std::cin;
		char page[50];
		cin.ignore();
		cin.getline(page, 50);
		return std::stoi(page);
	}
	Termin ScanTerminInfo() {

		using std::cout;

		string name;
		PageNumber page;
		cout << "Print name";
		name = ScanTerminName();
		cout << "Print page: ";
		page = ScanTerminPage();

		return Termin(name, page);
	}

	void ProcessCommand(Command command) {

		switch (command) {
		case FIND_TERMIN: {

			using namespace std;
		
			string input_t_name;
			cout << "Print name: ";
			input_t_name = ScanTerminName();
			//cin.clear();
			
			try {

				const Termin& termin = subject_index_.SearchTermin(input_t_name);
				PrintTerminInfo(termin);

				TerminsList& under_termins = termin.GetUnderTerminsList();

				for (size_t i = 0; i < under_termins.GetNumberOfTermins(); i++)
				{
					const Termin& under_termin = under_termins[i];

					cout << '\t' << under_termin.GetName() << ", " << under_termin.GetPage(0) << endl;

				}

			}
			catch (SubjectIndexException exception) {

				cout << exception.What() << endl;
			}
			catch (TerminException exception) {

				cout << exception.What() << endl;

			}

			system("pause");

			break;
		}
		case FIND_A_TERM_BY_UNDERTERM: {
			
			using std::cout;
			using std::endl;
			
			string under_termin_name;
			cout << "Print undertermin name: ";

			under_termin_name = ScanTerminName();
			
			try {
				const Termin& termin = subject_index_.SearchTerminByUnderTermin(under_termin_name);
				cout << termin.GetPrintString() << endl;
			}
			catch (SubjectIndexException exception) {
				cout << exception.What() << endl;
			}

			system("pause");
			break;
		}
		case ADD_TERMIN: {

			Termin termin = ScanTerminInfo();
			subject_index_.AddTermin(termin.GetName(), termin.GetPage(0));

			break;
		}

		case SHOW_SUBJECT_INDEX: {

			subject_index_.Print();
			system("pause");
			break;
		}

		case SORT_TERMS: {

			subject_index_.SortTerminsNames();
			break;
		}
		case SORT_PAGES: {

			subject_index_.SortPages();
			break;
		}
		case ADD_UNDERTERMIN: {

			using namespace std;
			string termin_name;
			cout << "Print termin name: "; cin >> termin_name;
			Termin under_termin = ScanTerminInfo();
			try {
				subject_index_.AddUnderTermin(termin_name, under_termin.GetName(), under_termin.GetPage(0));
			}
			catch (SubjectIndexException exception) {
				cout << exception.What() << endl;
			}

			system("pause");
			break;
		}
		case EDIT_TERM: {

			using namespace std;
			string termin_name;
			cout << "Print termin name: ";
			termin_name = ScanTerminName();
			cout << "New data." << endl;
			Termin termin = ScanTerminInfo();
			try {
				subject_index_.EditTermin(termin_name, termin.GetName(), termin.GetPage(0));
			}
			catch (SubjectIndexException exception) {
				cout << exception.What() << endl;
			}
			break;
		}
	
		case DELETE_TERMIN: {

			using std::cout;
			using std::endl;
			
			cout << "Print termin name: ";
			const string  termin_name = ScanTerminName();
			try {

				subject_index_.DeleteTermin(termin_name);

			}
			catch (SubjectIndexException exception) {

				cout << exception.What() << endl;

			}
			break;
		}

		case DELETE_UNDERTERMIN: {

			using std::cout;
			using std::endl;

			cout << "Print termin name: ";
			const string  termin_name = ScanTerminName();
			cout << "Print undertermin name: ";
			const string under_termin_name = ScanTerminName();

			try {

				Termin termin = subject_index_.SearchTermin(termin_name);
				termin.DeleteUnderTermin(under_termin_name);

			}
			catch (SubjectIndexException exception) {

				cout << exception.What() << endl;

			}
			catch (TerminException exception) {
				cout << exception.What() << endl;
			}
			
			system("pause");

			break;
		}

		}

	}

	static Menu* Exemplar()noexcept;

	explicit Menu(const Menu&) = delete;

	void operator=(const Menu&) = delete;

	void Start() {

		Command command = NOTHING;

		while ((command != EXIT_WITHOUT_SAVING) && (command != SAFE_AND_EXIT)) {

			system("cls");
			PrintMenu();
			command = ReadCommand();
			ProcessCommand(command);

		}

	}
};

Menu* Menu::Exemplar()noexcept {

	static Menu exemplar{};

	return &exemplar;
}

int main() {

	using std::shared_ptr;

	const shared_ptr<Menu> menu_ptr(Menu::Exemplar());

	menu_ptr->Start();

	return 0;
}