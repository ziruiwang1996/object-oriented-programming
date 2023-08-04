/*
Implement member function Swap.
You are not allowed to use any external structures (such as array)
You are not allowed to use any help function
You are not allowed to create any extra node.
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
	void RemoveAll(int k);//Delete all nodes with value k.
	void Reverse();
	void Sort1();
	void Sort2();
	void Swap(Dnode* p1, Dnode* p2);
	/*
	Task: swap two nodes pointed by p1 and p2, respectively.
    Requirements:
	1. only allowed to change the "next" and "previous" of each node, but not "value".
    2. assume p1 is on the left side of p2.  Note that, in a DLL, we assume "head" is on the left side and "tail" ison the right side.
	*/
};

void DLL::RemoveAll(int k) {
	if (!head) return;//empty
	Dnode* p1{ head };
	while (p1) {//while p1 is not nullptr
		Dnode* p2 = p1->next;
		if (p1->value == k) {
			if (p1 == head && p1 == tail) {
				head = tail = nullptr;
				delete p1;
				return;
			}
			else if (p1 == head) {
				head = p1->next;
				head->previous = nullptr;
				delete p1;
			}
			else if (p1 == tail) {
				tail = p1->previous;
				tail->next = nullptr;
				delete p1;
			}
			else {
				p1->previous->next = p1->next;
				p1->next->previous = p1->previous;
				delete p1;
			}
		}
		p1 = p2;
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


void DLL::Swap(Dnode* p1, Dnode* p2) {
	if (p1 == head && p2 == tail) {
		if (p1->next == p2) {
			p1->previous = p2;
			p1->next = nullptr;
			p2->previous = nullptr;
			p2->next = p1;
			head = p2;
			tail = p1;
		}
		else {
			p1->previous = p2->previous;
			p2->next = p1->next;
			p1->next->previous = p2;
			p2->previous->next = p1;
			p1->next = nullptr;
			p2->previous = nullptr;
			head = p2;
			tail = p1;
		}
	}
	else if (p1 == head) {
		if (p1->next == p2) {
			p1->previous = p2;
			p1->next = p2->next;
			p2->next->previous = p1;
			p2->next = p1;
			p2->previous = nullptr;
			head = p2;
		}
		else {
			p1->previous = p2->previous;
			p2->next->previous = p1;
			p1->next->previous = p2;
			p2->previous->next = p1;
			Dnode* temp = p1->next;
			p1->next = p2->next;
			p2->next = temp;
			p2->previous = nullptr;
			head = p2;
		}
	}
	else if (p2 == tail) {
		if (p1->next == p2) {
			p2->next = p1;
			p2->previous = p1->previous;
			p1->previous->next = p2;
			p1->previous = p2;
			p1->next = nullptr;
			tail = p1;
		}
		else {
			tail->next = p1->next;
			p1->previous->next = p2;
			p2->previous->next = p1;
			p1->next->previous = p2;
			Dnode* temp = p2->previous;
			p2->previous = p1->previous;
			p1->previous = temp;
			p1->next = nullptr;
			tail = p1;
		}
	}
	else if (p1->next == p2) {
		p1->next = p2->next;
		p2->next->previous = p1;
		p1->previous->next = p2;
		p2->previous = p1->previous;
		p2->next = p1;
		p1->previous = p2;
	}
	else {
		p1->previous->next = p2;
		p2->previous->next = p1;
		p1->next->previous = p2;
		p2->next->previous = p1;
		Dnode* temp1 = p1->previous;
		p1->previous = p2->previous;
		p2->previous = temp1;
		Dnode* temp2 = p1->next;
		p1->next = p2->next;
		p2->next = temp2;
	}
}

void DLL::Sort2() {
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
		if (pmin != p1) {
			Swap(p1, pmin);
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
	L1.RemoveAll(1);
	L1.PrintF();
	L1.PrintB();
	L1.Sort1();
	L1.PrintF();
	L1.PrintB();
	DLL L2{ 50, 50 };
	L2.PrintF();
	L2.PrintB();
	L2.Sort2();
	L2.PrintF();
	L2.PrintB();
	return 0;
}
