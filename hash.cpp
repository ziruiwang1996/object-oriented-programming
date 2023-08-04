#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <set>
#include <unordered_set>

using namespace std;

//when comparing equality of two structures, always compare sums of all int values in the structures
//When Hashing a structure, always hash the sum of all int values in the structure

class functorClass {
public:
	bool operator()(const set<int>* S1, const set<int>* S2) const {
		int tot_S1 = 0;
		int tot_S2 = 0;
		for (auto i : *S1) { tot_S1 += i; }
		for (auto i : *S2) { tot_S2 += i; }
		return tot_S1 < tot_S2;
	}

	bool operator()(const set<set<int>*, functorClass>* S1, const set<set<int>*, functorClass>* S2) const {
		int tot_S1 = 0;
		int tot_S2 = 0;
		for (auto i : *S1) { for (auto j : *i) { tot_S1 += j; } }
		for (auto i : *S2) { for (auto j : *i) { tot_S1 += j; } }
		return tot_S1 < tot_S2;
	}

	bool operator()(const map<set<set<int>*, functorClass>*, vector<int>*, functorClass> M1, const map<set<set<int>*, functorClass>*, vector<int>*, functorClass> M2) const {
		int tot_M1 = 0;
		int tot_M2 = 0;
		for (auto i : M1) {
			for (auto j : *(i.first)) { for (auto k : *j) { tot_M1 += k; } }
			for (auto j : *(i.second)) { tot_M1 += j; }
		}
		for (auto i : M2) {
			for (auto j : *(i.first)) { for (auto k : *j) { tot_M2 += k; } }
			for (auto j : *(i.second)) { tot_M2 += j; }
		}
		return tot_M1 < tot_M2;
	}
};

class hashFunctorClass {
public:
	unsigned int operator()(const map<set<set<int>*, functorClass>*, vector<int>*, functorClass> M) const {
		int tot = 0;
		for (auto i : M) {
			for (auto j : *(i.first)) { for (auto k : *j) { tot += k; } }
			for (auto j : *(i.second)) { tot += j; }
		}
		return hash<int>{}(tot);
	}

	bool operator()(const map<set<set<int>*, functorClass>*, vector<int>*, functorClass> M1, const map<set<set<int>*, functorClass>*, vector<int>*, functorClass> M2) const {
		int tot_M1 = 0;
		int tot_M2 = 0;
		for (auto i : M1) {
			for (auto j : *(i.first)) { for (auto k : *j) { tot_M1 += k; } }
			for (auto j : *(i.second)) { tot_M1 += j; }
		}
		for (auto i : M2) {
			for (auto j : *(i.first)) { for (auto k : *j) { tot_M2 += k; } }
			for (auto j : *(i.second)) { tot_M2 += j; }
		}
		return tot_M1 == tot_M2 && M1.size() == M2.size();
	}
};

//For printing, map: { ...}  vector: [...]  set(or unordered set): <...>
ostream& operator<<(ostream& str, const set<map<set<set<int>*, functorClass>*, vector<int>*, functorClass>, functorClass>& S) {
	str << "< " << endl;
	for (auto i : S) {
		str << "{";
		for (auto j : i) {
			str << "<";
			for (auto k : *(j.first)) {
				str << "<";
				for (auto l : *k) {
					str << l << " ";
				}
				str << ">";
			}
			str << "> [";
			for (auto k : *(j.second)) {
				str << k << " ";
			}
			str << "]";
		}
		str << "}" << endl;

	}
	str << ">";
	return str;
}

ostream& operator<<(ostream& str, const map<set<set<int>*, functorClass>*, vector<int>*, functorClass>& M) {
	str << "{";
	for (auto i : M) {
		str << "<";
		for (auto j : *(i.first)) {
			str << "<";
			for (auto k : *j) {
				str << k << " ";
			}
			str << ">";
		}
		str << ">[";
		for (auto j : *(i.second)) {
			str << j << " ";
		}
		str << "]";
	}
	str << "}";
	return str;
}

ostream& operator<<(ostream& str, const unordered_set<map<set<set<int>*, functorClass>*, vector<int>*, functorClass>, hashFunctorClass, hashFunctorClass>& S) {
	str << "{ " << endl;
	for (unsigned int i = 0; i < S.bucket_count(); i++) {
		str << "Bucket " << i << " contains ";
		for (auto it = S.begin(i); it != S.end(i); it++) {
			str << *it;
		}
		str << endl;
	}
	str << "}";
	return str;
}

int main() {
	//The following statement won't compile. Fix it.
	map<set<set<int>*, functorClass>*, vector<int>*, functorClass> M1{
		{ new set<set<int>*, functorClass>{ new set<int>{4,6,11}, new set<int>{1,4,9}, new set<int>{0,31,69} }, new vector<int>{7,21,5} },
		{ new set<set<int>*, functorClass>{ new set<int>{81,47,9}, new set<int>{7,15,6}, new set<int>{3,10,2} }, new vector<int>{7,12,5} },
		{ new set<set<int>*, functorClass>{ new set<int>{1,7,4}, new set<int>{1,92,44}, new set<int>{110,13,12} }, new vector<int>{7,2,5} }
	};
	map<set<set<int>*, functorClass>*, vector<int>*, functorClass> M2{
		{ new set<set<int>*, functorClass>{ new set<int>{5,6,11}, new set<int>{1,4,9}, new set<int>{0,31,9} }, new vector<int>{7,1,5} },
		{ new set<set<int>*, functorClass>{ new set<int>{1,7,9}, new set<int>{7,5,6}, new set<int>{3,10,62} }, new vector<int>{7,2,5} },
		{ new set<set<int>*, functorClass>{ new set<int>{1,7,24}, new set<int>{1,9,44}, new set<int>{10,13,12} }, new vector<int>{7,3,5} }
	};
	map<set<set<int>*, functorClass>*, vector<int>*, functorClass> M3{
		{ new set<set<int>*, functorClass>{ new set<int>{4,6,12}, new set<int>{1,7,9}, new set<int>{10,31,9} }, new vector<int>{7,21,15} },
		{ new set<set<int>*, functorClass>{ new set<int>{91,47,9}, new set<int>{7,15,12}, new set<int>{3,10,12} }, new vector<int>{17,2,5} },
		{ new set<set<int>*, functorClass>{ new set<int>{11,7,4}, new set<int>{1,92,4}, new set<int>{110,13,12} }, new vector<int>{7,6,5} }
	};
	set< map< set<set<int>*, functorClass>*, vector<int>*, functorClass >, functorClass > S1{ M1, M2, M3 };//Create your initial values with at least 3 elements in every STL container.
	cout << S1 << endl;

	//The following statement won't compile. Fix it.
	unordered_set< map < set<set<int>*, functorClass>*, vector<int>*, functorClass >, hashFunctorClass, hashFunctorClass > H1{ M1, M2, M3 };//You can re-use the above.
	cout << H1 << endl;//print bucket arrays
	return 0;
}
