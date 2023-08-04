#include <iostream>
#include <memory>
#include <cmath>

using namespace std;

class node {
public:
	int value;
	shared_ptr<node> east;
	weak_ptr<node> Lchild;
	weak_ptr<node> Rchild;
	node() {}
	node(int i) { value = i; }
};

class tree {
public:
	shared_ptr<node> root;
	tree() { }

	//Implement all member functions below
	tree(int n, int m);//constructor for n-level tree with random values in 0 ... m-1
	//n=1: 1 node; n-2: 3 nodes; n=3: 7 nodes; n=4: 15 nodes, etc.

	tree(const tree& T);//copy constructor
	~tree();//destructor
	tree(tree&& T); //move constructor

	tree(const initializer_list<int>& V);//See lecture video recording for this.
	void operator = (const tree& T);//copy assignment
	void operator = (tree&& T); //move assignment
	tree ThreeTimes(); //return a tree with all node value being three times

	shared_ptr<node> operator[](int k);//The function returns the address of kth node
	//in the overall ring (or cycle).  For example, when k is 0, it returns the address of the
	//root; when k is 1, it returns the address of left child of root; when k is 2, it returns
	//the address of right child of root, etc.
	//For a level 4 tree, when k=14, it returns the address of the very last node of the tree.
	friend ostream& operator<<(ostream& str, const tree& T);//
	//print each level from root to leaves. At each level, print value from left to right.

	void InorderPrint(shared_ptr<node>);//in-order printing
};

tree::tree(int n, int m) {
	cout << "Constructor" << endl;
	root = make_shared<node>(rand() % m);
	auto sp1 = root;
	for (int num_node = 0; num_node < pow(2, n) - 1; num_node++) {
		sp1->east = make_shared<node>(rand() % m);
		sp1 = sp1->east;
	}
	sp1 = root;
	auto sp2 = root->east;
	while (sp2) {
		sp1->Lchild = sp2;
		sp2 = sp2->east;
		sp1->Rchild = sp2;
		sp1 = sp1->east;
		if (sp2) sp2 = sp2->east;
	}
	sp1 = sp2 = root;
	auto sp3 = root->east;
	while (sp3) {
		sp2->east = sp1;
		sp1 = sp1->Lchild.lock();
		sp2 = sp2->Rchild.lock();
		sp3 = sp3->Lchild.lock();
	}
}

tree::tree(const tree& T) {
	cout << "Copy Constructor" << endl;
	root = make_shared<node>(T.root->value);
	auto new_node = root;
	auto sp1 = T.root;
	auto sp2 = sp1;
	while (sp1) {
		if (sp2->east == sp1) {
			sp1 = sp1->Lchild.lock();
			sp2 = sp1;
		}
		else {
			sp2 = sp2->east;
		}
		if (sp2) {
			new_node->east = make_shared<node>(sp2->value);
			new_node = new_node->east;
		}
	}
	sp1 = root;
	sp2 = root->east;
	while (sp2) {
		sp1->Lchild = sp2;
		sp2 = sp2->east;
		sp1->Rchild = sp2;
		sp2 = sp2->east;
		sp1 = sp1->east;
	}
	sp1 = sp2 = root;
	auto sp3 = root->east;
	while (sp3) {
		sp2->east = sp1;
		sp1 = sp1->Lchild.lock();
		sp2 = sp2->Rchild.lock();
		sp3 = sp3->Lchild.lock();
	}
	sp2->east = sp1;
}

tree::~tree() {
	cout << "Destructor" << endl;
	if (!root) return;
	auto sp1 = root;
	auto sp2 = sp1->Lchild.lock();
	while (sp1) {
		sp1->east = nullptr;
		sp1 = sp2;
		if (sp2) sp2 = sp2->Lchild.lock();
	}
}

tree::tree(tree&& T) {
	cout << "Move Constructor" << endl;
	root = T.root;
	T.root = nullptr;
};

tree::tree(const initializer_list<int>& V) : tree(log2(V.size() + 1), 2) {
	cout << "Initializer List" << endl;
	auto sp1 = root;
	auto sp2 = sp1;
	for (auto i : V) {
		if (sp2->east != sp1) {
			sp2->value = i;
			sp2 = sp2->east;
		}
		else {
			sp2->value = i;
			if (sp1->Lchild.lock())
				sp1 = sp1->Lchild.lock();
			else return;
			sp2 = sp1;
		}
	}
}

void tree::operator=(const tree& T) {
	cout << "Copy Assignment" << endl;
	if (root == T.root) return;
	if (root) {
		auto sp1 = root;
		auto sp2 = sp1->Lchild.lock();
		while (sp1) {
			sp1->east = nullptr;
			sp1 = sp2;
			if (sp2) sp2 = sp2->Lchild.lock();
		}
	}
	root = make_shared<node>(T.root->value);
	auto new_node = root;
	auto sp1 = T.root;
	auto sp2 = sp1;
	while (sp1) {
		if (sp2->east == sp1) {
			sp1 = sp1->Lchild.lock();
			sp2 = sp1;
		}
		else {
			sp2 = sp2->east;
		}
		if (sp2) {
			new_node->east = make_shared<node>(sp2->value);
			new_node = new_node->east;
		}
	}
	sp1 = root;
	sp2 = root->east;
	while (sp2) {
		sp1->Lchild = sp2;
		sp2 = sp2->east;
		sp1->Rchild = sp2;
		sp2 = sp2->east;
		sp1 = sp1->east;
	}
	sp1 = sp2 = root;
	auto sp3 = root->east;
	while (sp3) {
		sp2->east = sp1;
		sp1 = sp1->Lchild.lock();
		sp2 = sp2->Rchild.lock();
		sp3 = sp3->Lchild.lock();
	}
	sp2->east = sp1;
}

void tree::operator=(tree&& T) {
	cout << "Move Assignment" << endl;
	if (root) {
		auto sp1 = root;
		auto sp2 = sp1->Lchild.lock();
		while (sp1) {
			sp1->east = nullptr;
			sp1 = sp2;
			if (sp2) sp2 = sp2->Lchild.lock();
		}
	}
	root = T.root;
	T.root = nullptr;
}

tree tree::ThreeTimes() {
	cout << "Three Times" << endl;
	tree temp{ *this };  
	auto sp1 = temp.root;
	while (sp1) {
		sp1->value *= 3;
		auto sp2 = sp1->east;
		while (sp2 != sp1) {
			sp2->value *= 3;
			sp2 = sp2->east;
		}
		sp1 = sp1->Lchild.lock();
	}
	return temp;
}

shared_ptr<node> tree::operator[](int k) {
	int level = log2(k);
	auto sp = root;
	for (int i = 0; i < level; i++) {
		sp = sp->Lchild.lock();
	}
	int breadth = k - pow(2, level) + 1;
	for (int i = 0; i < breadth; i++) {
		sp = sp->east;
	}
	return sp;
}

ostream& operator<<(ostream& str, const tree& T) {
	auto sp1 = T.root;
	while (sp1) {
		str << sp1->value << " ";
		auto sp2 = sp1->east;
		while (sp2 != sp1) {
			str << sp2->value << " ";
			sp2 = sp2->east;
		}
		sp1 = sp1->Lchild.lock();
	}
	return str;
}

void tree::InorderPrint(shared_ptr<node> n) {
	if (!n) return;
	InorderPrint(n->Lchild.lock());
	cout << n->value << " ";
	InorderPrint(n->Rchild.lock());
}

int main() {
	tree T1(3, 10);
	cout << T1 << endl;
	T1.InorderPrint(T1.root);
	cout << endl;
	tree T2 = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};

	cout << T2 << endl;
	T2.InorderPrint(T2.root);
	cout << endl;

	tree T3{T2};
	cout << T3 << endl;
	T3.InorderPrint(T3.root);
	cout << endl;

	tree T4;
	T4 = T3;
	cout << T4 << endl;
	T4.InorderPrint(T4.root);
	cout << endl;

	cout << T4[0]->value << endl;
	cout << T4[2]->value << endl;
	cout << T4[4]->value << endl;
	cout << T4[6]->value << endl;

	T4 = T3.ThreeTimes();
	cout << T4 << endl;
	T4.InorderPrint(T4.root);
	cout << endl;

	return 0;
}
