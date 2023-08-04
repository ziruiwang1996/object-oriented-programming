/*
Task: Implement member function Merge.
Requirements:
Your implementation has to be in-place.
You are required to implement the Merge algorithm to be described in class.
You are not allowed to call sort1 or sort2, or Swap from HW1.
You are not allowed to use any external structures (such as array)
You are not allowed to use any helper function
You are not allowed to create new nodes or any extra structures (such as array, list, etc.).
*/
#include <iostream>
using namespace std;

class Dnode {
public:
	int value;
	Dnode* next;
	Dnode* previous;
	Dnode(int i) { value = i; next = previous = nullptr; }
	Dnode() { next = previous = nullptr; }
};

class DLL {//Doubly Linked List
public:
	Dnode* head;
	Dnode* tail;
	DLL(int n, int m);//Constructor; Construct an n-node DLL with random
	//values in 0 ... m-1
	DLL() { head = tail = nullptr; }
	void PrintF();//Print forward from head
	void PrintB();//Print backward from tail
	void Sort1();
	void Merge(Dnode* p);
	/* Given that nodes in head ....p->previous are sorted, and
	   nodes in p .... tail are also sorted, combine the two into a single
	   sorted list.  You are required to perform an in-place implementation.
	*/
};

DLL::DLL(const initializer_list<int>& I) {
	head = nullptr;
	node* p1 = nullptr;
	for (auto& i : I) {
		if (!head) {
			head = new Dnode(i);
			tail = head;
			tail->next = nullptr;

			p1 = head;
		}
		else {
			p1->next = new node(i);
			p1 = p1->next;
		}
	}
}

void DLL::Merge(Dnode* p) {
	if (p == nullptr || p == head) { return; }
	else if (p == head->next && p->value >= head->value) { return; }
	else if (p == tail) {
		if (p->value >= p->previous->value) { return; }
		if (p->value <= head->value) {
			p->previous->next = nullptr;
			p->next = head;
			head->previous = p;
			tail = p->previous;
			p->previous = nullptr;
			head = p;
			return;
	  }
	}
	else {
		Dnode* p1{ head };
		Dnode* p2{ p };
		while (p1 != p2) {
			if ( p2 == nullptr ) break;
			if (p2->value > p1->value) {
				p1 = p1->next;
			}
			else {
				Dnode* temp{ p2->next };
				if (p1 == head) {
					p2->previous->next = p2->next;
					p2->next->previous = p2->previous;
					p2->next = p1;
					p1->previous = p2;
					p2->previous = nullptr;
					head = p2;
				}
				else if (p2 == tail) {
					tail = p2->previous;
					p2->previous->next = nullptr;
					p2->next = p1;
					p1->previous->next = p2;
					p2->previous = p1->previous;
					p1->previous = p2;
				}
				else {
					p2->previous->next = p2->next;
					p2->next->previous = p2->previous;
					p2->next = p1;
					p1->previous->next = p2;
					p2->previous = p1->previous;
					p1->previous = p2;
				}
				p2 = temp;
			}
		}
	}
}

void DLL::Sort1() {
	if (!head || !head->next) return;//0 or 1 node
	Dnode* p1{ head };
	while (p1->next) {
		Dnode* p2{ p1->next }, * p3{ p1->next };
		Dnode* pmin{ p1 };
		int min{ p1->value };
		while (p2) {//while p2 is not nullptr
			if (p2->value < min) {
				min = p2->value;
				pmin = p2;
			}
			p2 = p2->next;
		}
		if (pmin != p1) {//swap pmin->value with p1->value
			pmin->value = p1->value;
			p1->value = min;
		}
		//p1 = p1->next;
		p1 = p3;
	}
}

DLL::DLL(int n, int m) {
	head = tail = nullptr;
	for (int i = 0; i < n; ++i) {
		Dnode* p1{ new Dnode{rand() % m} };
		if (!head) {//empty
			head = tail = p1;
		}
		else {
			tail->next = p1;
			p1->previous = tail;
			tail = p1;
		}
	}
}

void DLL::PrintF() {
	cout << endl;
	Dnode* p1{ head };
	while (p1) {
		cout << p1->value << " ";
		p1 = p1->next;
	}
}

void DLL::PrintB() {
	cout << endl;
	Dnode* p1{ tail };
	while (p1) {
		cout << p1->value << " ";
		p1 = p1->previous;
	}
}

int main() {
	DLL  L1{ 30, 20 };
	L1.PrintF();
	L1.PrintB();

	L1.Sort1();
	L1.PrintF();
	L1.PrintB();
	cout << "     " << endl;
	DLL L2{ 29, 15 };
	L2.PrintF();
	L2.PrintB();
	L2.Sort1();
	L2.PrintF();
	L2.PrintB();
	L1.tail->next = L2.head;
	L2.head->previous = L1.tail;
	L1.tail = L2.tail;
	Dnode* p = L2.head;
	L2.head = L2.tail = nullptr;
	L1.Merge(p);
	L1.PrintF();
	L1.PrintB();

	return 0;
}
