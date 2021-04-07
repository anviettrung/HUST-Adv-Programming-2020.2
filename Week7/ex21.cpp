#include <iostream>

using namespace std;

template<typename T>
struct LinkedListNode {
	T Value;

	LinkedListNode<T>* Prev;
	LinkedListNode<T>* Next;

	LinkedListNode() { }
	LinkedListNode(T val) {
		Value = val;
	}
};

template<typename T>
class LinkedList {
public:
	int Count;
	LinkedListNode<T>* First;
	LinkedListNode<T>* Last;

	LinkedList() {
		Count = 0;
		First = Last = NULL;
	}

	~LinkedList() {
		Clear();
	}

	void Clear() {
		while (First != NULL)
			RemoveFirst();
	}

	void AddFirst(LinkedListNode<T>* newNode) {
		if (First == NULL) {
			// Init
			First = newNode;
			Last  = newNode;
		} else {
			newNode->Next = First;
			First->Prev = newNode;
			First = newNode;
		}

		Count++;
	}

	void AddFirst(T val) {
		AddFirst(new LinkedListNode<T>(val));
	}

	void AddLast(LinkedListNode<T>* newNode) {
		if (Last == NULL) {
			// Init
			First = newNode;
			Last  = newNode;
		} else {
			newNode->Prev = Last;
			Last->Next = newNode;
			Last = newNode;
		}

		Count++;
	}

	void AddLast(T val) {
		AddLast(new LinkedListNode<T>(val));
	}

	void RemoveFirst() {
		LinkedListNode<T>* p = First;
		if (p != NULL) {
			First = First->Next;
			delete p;
			Count--;
		}
	}

	void RemoveLast() {
		LinkedListNode<T>* p = Last;
		if (p != NULL) {
			Last = Last->Prev;
			delete p;
			Count--;
		}
	}

	LinkedListNode<T>* Find(T val) {
		LinkedListNode<T>* res = First;

		while (res != NULL) {
			if (res->Value == val)
				return res;
			res = res->Next;
		}
		return NULL;
	}

	LinkedListNode<T>* FindLast(T val) {
		LinkedListNode<T>* res = Last;

		while (res != NULL) {
			if (res->Value == val)
				return res;
			res = res->Prev;
		}
		return NULL;
	}

	bool Contains(T val) {
		return Find(val) != NULL;
	}
};

int main()
{
	LinkedList<int> list;

	list.AddLast(3);
	list.AddLast(5);
	list.AddLast(36);

	for (LinkedListNode<int>* p = list.First; p != NULL; p = p->Next)
		cout << p->Value << " ";
	cout << endl;

	int x = 0;
	do {
		cin >> x;
		LinkedListNode<int>* ans = list.Find(x);
		if (ans != NULL)
			cout << "Found" << endl;
		else
			cout << "Not Found" << endl;
	} while (x != 0);

	return 0;
}