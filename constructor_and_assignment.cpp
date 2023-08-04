/*
You are not allowed to use any helper functions
You are not alllowed to use any extra class.
 */
#include <iostream>
#include <map>
#include <list>
#include <tuple>
using namespace std;

class course {
public:
	string name;
	int section;
	int credits;
	string grade;
	course() {}
	course(string n, int s, int c, string g) { name = n; section = s; credits = c; grade = g; }
};

template <class T> class Record {
public:
	map<int, list< tuple <int*, int, T*>* >*>* pData;
	Record() { }
	Record(const initializer_list < pair<int, initializer_list<tuple <int, int, T>  >>>& I);
	Record(const Record<T>& R);//Copy Constructor
	void operator=(const Record<T>& R);//Copy Assignment
	~Record();//Destructor
	Record<T> ThreeTimes();//All int objects are multiplied by 3, except those in courses
	//and the keys (i.e., the first part of each map elements).
	//See sample screenshot.
	Record(Record<T>&& R);//Move Constructor
	void operator=(Record<T>&& R);//Move Assignment
};

template <class T> void Record<T>::operator=(Record<T>&& R) { //Move Assignment
	if (pData != nullptr) {
		for (auto i : *pData) {
			for (auto j : *(i.second)) {
				delete get<0>(*j);
				delete get<2>(*j);
				delete j;
			}
			delete i.second;
		}
		delete pData;
	}
	pData = R.pData;
	R.pData = nullptr;
	cout << "Move Assignment" << endl;
}

template <class T> Record<T>::Record(Record<T>&& R) { //Move Constructor
	pData = R.pData;
	R.pData = nullptr;
	cout << "Move Constructor" << endl;
}

template<class T> Record<T> Record<T>::ThreeTimes() {
	Record<T> temp{ *this };  //call copy constructor
	for (auto i : *(temp.pData)) {
		for (auto j : *(i.second)) {
			*(get<0>(*j)) *= 3;
			get<1>(*j) *= 3;
		}
	}
	cout << "ThreeTimes" << endl;
	return temp;
}

template<class T> Record<T>::~Record() { //Destructor
	if (pData == nullptr) {
		cout << "Destructor" << endl;
		return;
	}
	for (auto i : *pData) {
		for (auto j : *(i.second)) {
			delete get<0>(*j);
			delete get<2>(*j);
			delete j;
		}
		delete i.second;
	}
	delete pData;
	cout << "Destructor" << endl;
}

template <class T> void Record<T>::operator=(const Record<T>& R) { //Copy Assignment
	if (pData == R.pData) { //when object is the same
		cout << "Copy Assignment" << endl;
		return;
	}
	// delete first
	if (pData != nullptr) {
		for (auto i : *pData) {
			for (auto j : *(i.second)) {
				delete get<0>(*j);
				delete get<2>(*j);
				delete j;
			}
			delete i.second;
		}
		delete pData;
	}
	// deep copy
	pData = new map<int, list< tuple <int*, int, T*>* >*>{};
	for (auto i : *(R.pData)) {
		(*pData)[i.first] = new list< tuple <int*, int, T*>* >{};
		for (auto j : *(i.second)) {
			auto temp = new tuple < int*, int, T* >{};
			get<0>(*temp) = new int(*(get<0>(*j)));
			get<1>(*temp) = get<1>(*j);
			get<2>(*temp) = new T(*(get<2>(*j)));
			(*pData)[i.first]->push_back(temp);
		}
	}
	cout << "Copy Assignment" << endl;
}

template <class T> Record<T>::Record(const Record<T>& R) { //Copy constructor
	pData = new map<int, list< tuple <int*, int, T*>* >*>{};
	for (auto i : *(R.pData)) {
		(*pData)[i.first] = new list< tuple <int*, int, T*>* >{};
		for (auto j : *(i.second)) {
			auto temp = new tuple < int*, int, T* >{};
			get<0>(*temp) = new int(*(get<0>(*j)));
			get<1>(*temp) = get<1>(*j);
			get<2>(*temp) = new T(*(get<2>(*j)));
			(*pData)[i.first]->push_back(temp);
		}
	}
	cout << "Copy Constructor" << endl;
}

template <class T> Record<T>::Record(const initializer_list < pair<int, initializer_list<tuple <int, int, T>>>>& I) {
	pData = new map<int, list< tuple <int*, int, T*>* >*>{};
	for (auto i : I) {
		(*pData)[i.first] = new list< tuple <int*, int, T*>* >{};
		for (auto j : i.second) {
			auto temp = new tuple < int*, int, T* >{};
			get<0>(*temp) = new int(get<0>(j));
			get<1>(*temp) = get<1>(j);
			get<2>(*temp) = new T(get<2>(j));
			(*pData)[i.first]->push_back(temp);
		}
	}
	cout << "Initializer List" << endl;
}

//You need to implement all needed overloaded operator<<
template <class T> ostream& operator<<(ostream& str, const Record<T>& R);
ostream& operator<<(ostream& str, const course& t);

int main() {
	course C1("CIS554", 1, 3, "A-"), C2("CSE674", 1, 3, "B+"), C3("MAT296", 8, 4, "A"), C4("WRT205", 5, 3, "A");
	course C5("CIS351", 2, 3, "A-"), C6("PSY205", 5, 3, "B+"), C7("MAT331", 2, 3, "A"), C8("ECN203", 4, 3, "A");

	Record<course> R1{ {10, { {12, 11, C1}, {9, 8, C2}  }},
		{7, {{8,7, C3}, {3,2, C4}, {1, 0, C5}}},{4, {{21, 20, C6}, {15, 14,C7}} } };
	cout << R1 << endl;

	Record<course> R2{ R1 };
	cout << R2 << endl;

	Record<course> R3;
	R3 = R1;
	cout << R3 << endl;

	R3 = R1.ThreeTimes();
	cout << R3 << endl;

	R3 = R3;
	cout << R3 << endl;
	return 0;
}

template <class T> ostream& operator<<(ostream& str, const Record<T>& R) {
	str << "{" << endl;
	for (auto i : *(R.pData)) {
		str << "{ " << i.first << " { ";
		for (auto j : *(i.second)) {
			str << *(get<0>(*j)) << " " << get<1>(*j) << " " << *(get<2>(*j)) << "  ";
		}
		str << " } }" << endl;
	}
	str << "}" << endl;
	return str;
}

ostream& operator<<(ostream& str, const course& t) {
	str << "(" << t.name << " " << t.section << " " << t.credits << " " << t.grade << ")" << "  ";
	return str;
}
