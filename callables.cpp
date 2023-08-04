#include <iostream>
#include <vector>
#include <list>
#include <map>

//For all printing, { ...} for linked list, {..} for map, <...> for list, and , [...] for vector
using namespace std;

template <typename T> class node {
public:
	T value;
	node<T>* next;
	node(T i) { value = i; next = nullptr; }
	node() { next = nullptr; }
};

template <typename T> class LinkedList {
public:
	node<T>* head;
	LinkedList<T>() { head = nullptr; }
	LinkedList<T>(const initializer_list<T>& I);//Initializer List
};

template <typename T> LinkedList<T>::LinkedList(const initializer_list<T>& I) : LinkedList<T>() {//Initializer List
	head = nullptr;//not needed with the :Link....
	auto p1{ I.end() - 1 };//initializer_list supports begin() and end()
	while (p1 != I.begin() - 1) {
		node<T>* p2{ new node<T>{*p1} };
		p2->next = head;
		head = p2;
		--p1;
	}
}

class myFunctorClass {
public:
	bool operator()(const list<int>* p1, const list<int>* p2) const {
		//For comparions, compare the sums of all int values in the structures.
		int p1_sum = 0;
		int p2_sum = 0;
		for (auto i : *p1) { p1_sum += i; }
		for (auto i : *p2) { p2_sum += i; }
		return p1_sum < p2_sum;
	}

	//map<list<int>*, vector<int>, myFunctorClass>*
	bool operator()(const map<list<int>*, vector<int>, myFunctorClass>* p1, const map<list<int>*, vector<int>, myFunctorClass>* p2) const {
		//For comparions, compare the sums of all int values in the structures.
		int p1_sum = 0;
		int p2_sum = 0;
		for (auto i : *p1) {
			for (auto j : *(i.first)) { p1_sum += j; }
			for (auto k : i.second) { p1_sum += k; }
		}
		for (auto i : *p2) {
			for (auto j : *(i.first)) { p2_sum += j; }
			for (auto k : i.second) { p2_sum += k; }
		}
		return p1_sum < p2_sum;
	}
};

template <class T> class myCompareClass {
public:
	bool operator()(const T& x, const T& y) const {
		return x > y;
	}
};

template <typename T> ostream& operator<<(ostream& str, const LinkedList<T>& L) {
	str << "{ ";
	node<T>* p1{ L.head };
	while (p1) {
		str << p1->value << " ";
		p1 = p1->next;
	}
	str << "}";
	return str;
}

ostream& operator<<(ostream& str, const map<map<list<int>*, vector<int>, myFunctorClass>*, int, myFunctorClass> M) {
	str << "{ " << endl;
	for (auto i : M) {
		str << "{";
		for (auto j : *i.first) {
			str << " < ";
			for (auto k : *j.first) {
				str << k << " ";
			}
			str << "> ";
			str << "[ ";
			for (auto l : j.second) {
				str << l << " ";
			}
			str << "]";
		}
		str << " " << i.second << " }" << endl;
	}
	str << "}" << endl;
	return str;
}

template <class T> bool f1(T& x, T& y) {
	return (x % 5) > (y % 5);
}

template <class T1, class T2> void Sort(LinkedList<T1>& lst, T2 f) {
	if (!lst.head) return;
	node<T1>* temp = lst.head;
	size_t size = 0;
	while (temp) {
		temp = temp->next;
		size++;
	}
	int it = 0;
	while (it < size) {
		node<T1>* temp1 = lst.head;
		while (temp1->next) {
			node<T1>* temp2 = temp1->next;
			if (f(temp1->value, temp2->value)) {
				T1 temp_val = temp1->value;
				temp1->value = temp2->value;
				temp2->value = temp_val;
			}
			temp1 = temp2;
		}
		it++;
	}
}

int main() {
	/*
	Write a bubble_sort function, Sort, which takes two arguments:
	a reference to LinkedList<T> and a callable. (See how Sort is called in code below.)
	When the callable is a lambda, the result of sorting is in descending order.
	When the callable is a functor, the result of sorting is in ascending order.
	When the callable is a regular function, the result of sorting is an ascending mod 5 sequence.
	Also see the sample screenshot.
	*/
	LinkedList<int> a1{ 10,2,0,14,43,25,18,1,5,45 };
	cout << a1 << endl;
	cout << endl;
	Sort(a1, [](int x, int y) {return x < y; });//You need to implement the lambda
	cout << a1 << endl;
	cout << endl;
	LinkedList<int> a2{ 10,2,0,14,43,25,18,1,5,45 };
	cout << a2 << endl;
	cout << endl;
	Sort(a2, myCompareClass<int>{});
	cout << a2 << endl;
	cout << endl;

	LinkedList<int> a3{ 10,2,0,14,43,25,18,1,5,45 };
	cout << a3 << endl;
	cout << endl;
	Sort(a3, f1<int>);//You need to implement f1.
	cout << a3 << endl;
	cout << endl;
	/*
	Remember that map will always sort elements by comparing the first part of each element (i.e., the key part).
	Implement functors in class myFunctorClass classes to allow the following map declaration to work.
	In both classes, when comparing two keys, count the sums of all int values at all levels, and compare the sums.
	*/
	auto M11 = new map<list<int>*, vector<int>, myFunctorClass>{
		{new list<int>{ 3,2,6,7 }, vector<int>{ 4,5,7,6,7 }},
	    {new list<int>{ 2,5,6,7 }, vector<int>{ 3,6,7,8,9 }},
	    {new list<int>{ 6,7,2,6 }, vector<int>{ 13,4,6,2 }} };
	auto M12 = new map<list<int>*, vector<int>, myFunctorClass>{
		{new list<int>{ 5,6,7,3 }, vector<int>{ 4,4,5 }},
		{new list<int>{ 2,3,4 }, vector<int>{ 3,4,4,5 }},
		{new list<int>{ 2,6,7 }, vector<int>{ 3,4,6,4,2 }} };
	auto M13 = new map<list<int>*, vector<int>, myFunctorClass>{
		{new list<int>{ 6,2,8,0 }, vector<int>{ 4,3,2,8,6,7}},
	    {new list<int>{ 3,4,5,6 }, vector<int>{ 3,2 }},
	    {new list<int>{ 2,1,4,5 }, vector<int>{ 3,2,3,6 }} };
	map<map<list<int>*, vector<int>, myFunctorClass>*, int, myFunctorClass> M1{ {M11, 1}, {M12, 2}, {M13, 3} };
	//You need to create your initial data for M1.
	//For map, list and vector, at least three elements are required.
	//Implement the needed overloading operator<< to support the following printing.
	cout << M1 << endl;
	cout << endl;

	return 0;
}
