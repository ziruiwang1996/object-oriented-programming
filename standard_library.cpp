#include <iostream>
#include <list>
#include <map>
#include <string>
#include <iomanip>
using namespace std;

class course {
public:
	string name;//CIS554
	int section;//1
	int credits;//3
	string grade;//A-
	course() {}
	course(string n, int s, int c, string g) { name = n; section = s; credits = c; grade = g; }
	bool operator<(const course& c) const;
	bool operator==(const course& c) const;
	float num_grade();
};

float course::num_grade() {
	map<string, float> M{
		{"A", 4.0f},
		{"A-", 3.667f},
		{"B+",  3.333f},
		{"B",	3.0f},
		{"B-" ,  2.667f},
		{"C+" ,  2.333f},
		{"C",	2.0f},
		{"C-" ,  1.667f},
		{"D",	1.0f},
		{"D-" , 0.667f},
		{"F",	0.0f}
	};
	return M[grade];
}

bool course::operator<(const course& c) const {
	return (name < c.name);
}

bool course::operator==(const course& c) const {
	return (name == c.name);
}

/*
Implement the following functions.
When adding a student, if the student is already in DB, then ignore the operation.
When adding a course, if the course is already in DB (even if it is in
a different semester, then ignore the operation.
All courses in a semester should be sorted according to name (increasing order)

When dropping a course, if the course does not exist, then ignore the operation.
When removing a student, if the student does not exist, then ignore the operation.
All courses in a semester need to be sorted.
When dropping or adding a course, overall GPA, semester GPA, overall credits and semester credits all need to be updated.
If after drop_course, the list becomes empty, you don't need to remove the list.
*/

void add_student(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int id);
void remove_student(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int id);
void add_course(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017
void drop_course(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int semester, int id, course c);
void print_student_semester_courses(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int semester, int id);
void print_student_all_courses(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int id);

ostream& operator<<(ostream& str, const course& c) {
	str << "(" << c.name << " " << c.section << " " << c.credits << " " << c.grade << ")";
	return str;
}

ostream& operator<<(ostream& str, map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB) {
	str << endl << "DB:" << endl;
	for (const auto& i : DB) {
		print_student_all_courses(DB, i.first);
	}
	return str;
}

int main() {
	//map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>>  DB;
	map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*> DB;
	add_student(DB, 11111);
	course C1("CIS554", 1, 3, "A-"), C2("CSE674", 1, 3, "B+"), C3("MAT296", 8, 4, "A"), C4("WRT205", 5, 3, "A");
	add_course(DB, 20171, 11111, C1);
	add_course(DB, 20171, 11111, C4);
	add_course(DB, 20171, 11111, C3);
	add_course(DB, 20171, 11111, C2);
	print_student_semester_courses(DB, 20171, 11111);
	drop_course(DB, 20171, 11111, C1);
	print_student_semester_courses(DB, 20171, 11111); //sorted according to course name

	course C5("CIS351", 2, 3, "A-"), C6("PSY205", 5, 3, "B+"), C7("MAT331", 2, 3, "A"), C8("ECN203", 4, 3, "A"), C9("CIS341", 1, 3, "A"), C10("CIS352", 2, 3, "A");
	add_course(DB, 20172, 11111, C5);
	add_course(DB, 20172, 11111, C6);
	add_course(DB, 20172, 11111, C7);
	add_course(DB, 20172, 11111, C8);
	add_course(DB, 20172, 11111, C3);
	add_course(DB, 20172, 11111, C9);
	add_course(DB, 20172, 11111, C10);
	drop_course(DB, 20171, 11111, C5);
	print_student_all_courses(DB, 11111);//ID GPA

	add_student(DB, 11112);
	add_course(DB, 20171, 11112, C2);
	add_course(DB, 20171, 11112, C5);
	add_course(DB, 20171, 11112, C7);
	drop_course(DB, 20171, 11111, C5);
	add_course(DB, 20171, 11112, C4);
	print_student_semester_courses(DB, 20171, 11112);

	add_course(DB, 20172, 11112, C8);
	add_course(DB, 20172, 11112, C3);
	add_course(DB, 20172, 11112, C5);
	add_course(DB, 20172, 11112, C1);
	drop_course(DB, 20171, 11111, C1);
	print_student_semester_courses(DB, 20172, 11112);

	print_student_all_courses(DB, 11112);

	//Overload operator<< to allow the following cout statements.
	cout << DB << endl;
	remove_student(DB, 11111);
	cout << DB << endl;
	return 0;
}

void add_student(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int id) {
	if (DB.find(id) != DB.end()) return; //student found
	DB[id] = new pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >
	{
		new pair<int, float>{0, 0.0f},
		new map<int, pair<pair<int, float>*, list<course*>*> > {}
	};
}

void remove_student(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int id) {
	if (DB.find(id) == DB.end()) return; //student not found
	delete DB[id]->first;
	auto& M1{ *(DB[id]->second) };
	for (auto& i : M1) {
		delete i.second.first;
		auto& L2{ *(i.second.second) };
		for (auto& j : L2) {
			delete j;
		}
		delete i.second.second;
	}
	delete DB[id]->second;
	delete DB[id];
	DB.erase(id);
}

void add_course(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int semester, int id, course c) {
	if (DB.find(id) == DB.end()) return;
	if (DB[id]->second->find(semester) == DB[id]->second->end()) { //semester not found
		(*(DB[id]->second))[semester] = { new pair<int, float>{0, 0.0f}, new list<course*> {} };
	}
	// if course already in another semester
	for (const auto& i : *(DB[id]->second)) {
		for (const auto& j : *(i.second.second)) {
			if (c == *j) return;
		}
	}
	auto& P1{ (*(DB[id]->second))[semester] }; //a pair
	auto& L2{ *((*(DB[id]->second))[semester].second) }; //a list
	if (L2.size() == 0) {
		L2.push_back(new course(c));
	}
	else {
		auto course_temp = L2.begin();
		while (**course_temp < c) {
			++course_temp;
			if (course_temp == L2.end()) {
				break;
			}
		}
		L2.insert(course_temp, new course(c));
	}
	P1.first->second = ((P1.first->second) * (P1.first->first) + (c.credits * c.num_grade())) / (P1.first->first + c.credits); //update term GPA
	P1.first->first += c.credits; //update term credit
	DB[id]->first->second = ((DB[id]->first->second) * (DB[id]->first->first) + (c.credits * c.num_grade())) / (DB[id]->first->first + c.credits); //update cml GPA
	DB[id]->first->first += c.credits; //update overall credit
}

void drop_course(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int semester, int id, course c) {
	if (DB.find(id) == DB.end()) return;
	if (DB[id]->second->find(semester) == DB[id]->second->end()) return; //semester not found
	auto& P1{ (*(DB[id]->second))[semester] }; //semester pair
	auto& L2{ *((*(DB[id]->second))[semester].second) }; //course list
	size_t size_before = L2.size();
	for (auto i = L2.begin(); i != L2.end(); ++i) {
		if (**i == c) {
			delete* i;
			L2.erase(i);
			break;
		}
	}
	if (L2.size() != size_before) {  //course removed
		P1.first->second = ((P1.first->second) * (P1.first->first) - (c.credits * c.num_grade())) / (P1.first->first - c.credits); //update term GPA
		P1.first->first -= c.credits; //update term credits
		DB[id]->first->second = ((DB[id]->first->second) * (DB[id]->first->first) - (c.credits * c.num_grade())) / (DB[id]->first->first - c.credits); //update cml GPA
		DB[id]->first->first -= c.credits; //update overall credits
	}
}

// consider the case not exist?
void print_student_semester_courses(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int semester, int id) {
	cout << "ID: " << id << endl;
	cout << "Semester: " << semester << endl;
	cout << "GPA: " << fixed << setprecision(2) << (*(DB[id]->second))[semester].first->second << endl;
	cout << "Credits: " << (*(DB[id]->second))[semester].first->first << endl;
	for (const auto& i : *((*(DB[id]->second))[semester].second)) {
		cout << *i << " ";
	}
	cout << endl;
}

void print_student_all_courses(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int id) {
	cout << "ID: " << id << endl;
	cout << "Overall GPA: " << fixed << setprecision(2) << DB[id]->first->second << endl;
	cout << "Overall Credits: " << DB[id]->first->first << endl;
	auto& M1{ *(DB[id]->second) }; //map
	for (const auto& i : M1) {
		cout << "Semester: " << i.first << endl;
		cout << "GPA: " << fixed << setprecision(2) << i.second.first->second << endl;
		cout << "Credits: " << i.second.first->first << endl;
		for (const auto& j : *(i.second.second)) {
			cout << *j << " ";
		}
		cout << endl;
	}
}
