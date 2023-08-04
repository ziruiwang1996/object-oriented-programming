//Recursive Operation with Trees
#include <iostream>
#include <typeinfo>
using namespace std;

class node {
public:
	int value;
	node* Lchild;
	node* Rchild;
	node(int i) : value(i), Lchild{ nullptr }, Rchild{ nullptr } {}
	node() { Lchild = Rchild = nullptr; }
};

class tree {//Full binary trees: 1, 3, 7, 15 ,   2^k-1 nodes
public:
	node* root;
	tree() { root = nullptr; }
	tree(int n, int m);//constructor
	node* Constructor_helper(int n, int m);
	void InOrderT(node* p);//Inorder Traveral of a subtree whose root is pointed by p
	void PreOrderT(node* p);
	void PostOrderT(node* p);
	//Implement InorderSort, Preordersot, PostorderSort and initializer_list.
	//Recursion is required in all implemenations.
	//In the three sorting implementation, you can use while loop, but not other loop stuctures (such as for).
	pair<node*, node*> InorderSort(node* p);
	pair<node*, node*> PreorderSort(node* p);
	pair<node*, node*> PostorderSort(node* p);
	tree(const initializer_list<int>& I);
	void IL_helper(const initializer_list<int>& I, const int*& p1, node* p2);
};

tree::tree(int n, int m) {
	root = Constructor_helper(n, m);
}

node* tree::Constructor_helper(int n, int m) {//constructor helper
	if (n == 0) return nullptr;//NULL is nullptr and zero; don't use it anymore
	//int i{ NULL }; i is 0
	node* p{ new node{ rand() % m } };
	p->Lchild = Constructor_helper(n - 1, m);
	p->Rchild = Constructor_helper(n - 1, m);
	return  p;
}

void tree::PostOrderT(node* p) {
	if (!p) return;
	PostOrderT(p->Lchild);
	//cout << p->value << " ";
	PostOrderT(p->Rchild);
	cout << p->value << " ";
}

void tree::PreOrderT(node* p) {
	if (!p) return;
	cout << p->value << " ";
	PreOrderT(p->Lchild);
	//cout << p->value << " ";
	PreOrderT(p->Rchild);
}

void tree::InOrderT(node* p) {
	if (!p) return;
	InOrderT(p->Lchild);
	cout << p->value << " ";
	InOrderT(p->Rchild);
}

pair<node*, node*> tree::InorderSort(node* p) {
	if (!p || !p->Lchild) return make_pair(p, p);
	auto Lpair = InorderSort(p->Lchild);
	auto Rpair = InorderSort(p->Rchild);
	while (Rpair.first->value < Lpair.second->value) {
		int temp = Rpair.first->value;
		Rpair.first->value = Lpair.second->value;
		Lpair.second->value = temp;
		Lpair = InorderSort(p->Lchild);
		Rpair = InorderSort(p->Rchild);
	}
	if (p->value < Lpair.second->value) {
		int temp = p->value;
		p->value = Lpair.second->value;
		Lpair.second->value = temp;
		Lpair = InorderSort(p->Lchild);
	}
	if (p->value > Rpair.first->value) {
		int temp = p->value;
		p->value = Rpair.first->value;
		Rpair.first->value = temp;
		Rpair = InorderSort(p->Rchild);
	}
	return make_pair(Lpair.first, Rpair.second);
}

pair<node*, node*> tree::PreorderSort(node* p) {
	if (!p || !p->Lchild) return make_pair(p, p);
	auto Lpair = PreorderSort(p->Lchild);
	auto Rpair = PreorderSort(p->Rchild);
	if (p->value > p->Lchild->value) {
		int temp = p->value;
		p->value = p->Lchild->value;
		p->Lchild->value = temp;
		Lpair = PreorderSort(p->Lchild);
	}
	if (p->Lchild->value > p->Rchild->value) {
		int temp = p->Lchild->value;
		p->Lchild->value = p->Rchild->value;
		p->Rchild->value = temp;
		Rpair = PreorderSort(p->Rchild);
		Lpair = PreorderSort(p->Rchild);
	}
	while (p->Rchild->value < Lpair.second->value) {
		int temp = p->Rchild->value;
		p->Rchild->value = Lpair.second->value;
		Lpair.second->value = temp;
		Lpair = PreorderSort(p->Lchild);
		Rpair = PreorderSort(p->Rchild);
	}
	return make_pair(Lpair.first, Rpair.second);
}

pair<node*, node*> tree::PostorderSort(node* p) {
	if (!p || !p->Lchild) return make_pair(p, p);
	auto Lpair = PostorderSort(p->Lchild);
	auto Rpair = PostorderSort(p->Rchild);
	if (p->value < p->Rchild->value) {
		int temp = p->value;
		p->value = p->Rchild->value;
		p->Rchild->value = temp;
		Rpair = PostorderSort(p->Rchild);
	}
	if (p->Rchild->value < p->Lchild->value) {
		int temp = p->Rchild->value;
		p->Rchild->value = p->Lchild->value;
		p->Lchild->value = temp;
		Rpair = PostorderSort(p->Rchild);
		Lpair = PostorderSort(p->Lchild);
	}
	while (Rpair.first->value < p->Lchild->value) {
		int temp = Rpair.first->value;
		Rpair.first->value = p->Lchild->value;
		p->Lchild->value = temp;
		Lpair = PostorderSort(p->Lchild);
		Rpair = PostorderSort(p->Rchild);
	}
	return make_pair(Lpair.first, Rpair.second);
}

tree::tree(const initializer_list<int>& I) : tree(log2(I.size() + 1), 2) {
	auto it = I.begin();
	IL_helper(I, it, this->root);
}

void tree::IL_helper(const initializer_list<int>& I, const int*& p1, node* p2) {
	if (p2->Lchild) IL_helper(I, p1, p2->Lchild);
	p2->value = *p1;
	p1++;
	if (p2->Rchild) IL_helper(I, p1, p2->Rchild);
}

int main() {
	tree T1(5, 32);
	T1.InOrderT(T1.root);
	cout << endl;
	T1.PreOrderT(T1.root);
	cout << endl;
	T1.PostOrderT(T1.root);
	cout << endl;
	cout << endl;

	T1.InorderSort(T1.root);
	T1.InOrderT(T1.root);
	cout << endl;
	T1.PreOrderT(T1.root);
	cout << endl;
	T1.PostOrderT(T1.root);
	cout << endl;
	cout << endl;

	T1.PreorderSort(T1.root);
	T1.InOrderT(T1.root);
	cout << endl;
	T1.PreOrderT(T1.root);
	cout << endl;
	T1.PostOrderT(T1.root);
	cout << endl;
	cout << endl;

	T1.PostorderSort(T1.root);
	T1.InOrderT(T1.root);
	cout << endl;
	T1.PreOrderT(T1.root);
	cout << endl;
	T1.PostOrderT(T1.root);
	cout << endl;
	cout << endl;

	tree T2{ 10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32 };
	T2.InOrderT(T2.root);
	cout << endl;
	T2.PreOrderT(T2.root);
	cout << endl;
	T2.PostOrderT(T2.root);
	cout << endl;
	return 0;
}
