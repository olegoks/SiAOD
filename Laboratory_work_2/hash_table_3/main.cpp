
#include "SubjectIndex.h"

int main() {

	ndx::SubjectIndex subject_index;
	subject_index.AddTermin("Termin_1", 100);
	subject_index.AddUnderTermin("Termin_1", "Under_termin_1", 200);
	

	return 0;
}