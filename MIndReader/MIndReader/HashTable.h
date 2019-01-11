#ifndef TEMPLATE_HASH_TABLE
#define TEMPLATE_HASH_TABLE
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

// default hash table size
const int HASH_SIZE = 100;

template <class ItemType>
class HashTable
{
public:
	HashTable(int hashSze = HASH_SIZE);

	bool IsEmpty(int key);
	bool  IsFull();
	int Hash(ItemType newItem);
	void Insert(ItemType newItem, ItemType guess);
	void InsertLinearProbe(ItemType newItem, int collisionChain, ItemType guess);
	void Append(int key, ItemType newItem, ItemType guess);
	void LinearAppend(int key, ItemType newItem, int collisionChain, ItemType guess);
	bool Remove(ItemType deleteItem, int key = -1);
	void Sort(int key);
	int TableSize();
	int TotalElems();
	int BucketSize(int key);
	int Count(ItemType searchItem);
	void MakeEmpty();
	int maxCollision = 0;


	~HashTable();

	class Iterator;

	Iterator begin(int key) { return(!IsEmpty(key)) ? head[key] : NULL; }

	Iterator end(int key = 0) { return NULL; }

private:
	struct node
	{
		ItemType currentItem;
		node* next;
	};
	node** head; // array of linked list declaration - front of each hash table cell
	int hashSize; // the size of the hash table (how many cells it has)
	int totElems; // holds the total number of elements in the entire table
	int* bucketSize; // holds the total number of elems in each specific hash table cell
	int* tails;
	int* heads;
};

template<class ItemType>
HashTable<ItemType>::HashTable(int hashSze)
{
	hashSize = hashSze;
	head = new node*[hashSize];
	heads = new int[hashSize];
	tails = new int[hashSize];
	bucketSize = new int[hashSize];
	
	for (int x = 0; x < hashSize; ++x)
	{
		head[x] = NULL;
		bucketSize[x] = 0;
		heads[x] = 0;
		tails[x] = 0;	
	}
	totElems = 0;
}

template<class ItemType>
bool HashTable<ItemType>::IsEmpty(int key)
{
	if (key >= 0 && key < hashSize)
	{
		return head[key] == NULL;
	}
	return true;
}

template<class ItemType>
bool HashTable<ItemType>::IsFull()
{
	try
	{
		node* location = new node;
		delete location;
		return false;
	}
	catch (std::bad_alloc&)
	{
		return true;
	}
}

template<class ItemType>
int HashTable<ItemType>::Hash(ItemType newItem)
{
	long h = 19937;
	std::stringstream convert;

	// convert the parameter to a string using "stringstream" which is done
	// so we can hash multiple datatypes using only one function
	convert << newItem;
	std::string temp = convert.str();

	for (unsigned x = 0; x < temp.length(); ++x)
	{
		h = (h << 6) ^ (h >> 26) ^ temp[x];
	}
	return abs(h % hashSize);
}

template<class ItemType>
void HashTable<ItemType>::Insert(ItemType newItem, ItemType guess)
{
	if (IsFull())
	{

	}
	else
	{
		int key = Hash(newItem);
		Append(key, newItem, guess);
	}
}

template<class ItemType>
void HashTable<ItemType>::InsertLinearProbe(ItemType newItem, int collisionChain, ItemType guess)
{
	if (IsFull())
	{

	}
	else
	{
		int key = Hash(newItem);
		LinearAppend(key, newItem, collisionChain, guess);
	}
}

template<class ItemType>
void HashTable<ItemType>::Append(int key, ItemType newItem, ItemType guess)
{
	if (IsFull())
	{

	}
	else
	{
		node* newNode = new node;  // adds new node
		newNode->currentItem = newItem;
		newNode->next = NULL;
		char ch = newItem.back();

		if (IsEmpty(key))
		{
			head[key] = newNode;
		}

		if (ch == 't')
		{
			++tails;
		}

		if (ch == 'h')
		{
			++heads;
		}

		++bucketSize[key];
		++totElems;
	}
}

template<class ItemType>
void HashTable<ItemType>::LinearAppend(int key, ItemType newItem, int collisionChain, ItemType guess)
{
	if (IsFull())
	{

	}
	else
	{
		node* newNode = new node;  // adds new node
		newNode->currentItem = newItem;
		newNode->next = NULL;

		if (IsEmpty(key))
		{
			head[key] = newNode;
			char ch = newItem.back();

			if (ch == 't')
			{
				++tails;
			}

			if (ch == 'h')
			{
				++heads;
			}
			if (collisionChain > maxCollision)
			{
				maxCollision = collisionChain;
			}
			++totElems;
			++bucketSize[key];
		}
		else
		{
			++collisionChain;
			LinearAppend(key + 1, newItem, collisionChain, guess);
		}


	}
}


template<class ItemType>
bool HashTable<ItemType>::Remove(ItemType deleteItem, int key)
{
	bool isFound = false;
	node* tempPtr;
	if (key == -1)
	{
		key = Hash(deleteItem);
	}

	if (IsEmpty(key))
	{

	}
	else if (head[key]->currentItem == deleteItem)
	{
		tempPtr = head[key];
		head[key] = head[key]->next;
		delete tempPtr;
		--totElems;
		--bucketSize[key];
		isFound = true;
	}
	else
	{
		for (tempPtr = head[key]; tempPtr->next != NULL; tempPtr = tempPtr->next)
		{
			if (tempPtr->next->currentItem == deleteItem)
			{
				node* deleteNode = tempPtr->next;
				tempPtr->next = tempPtr->next->next;
				delete deleteNode;
				isFound = true;
				--totElems;
				--bucketSize[key];
				break;
			}
		}
	}
	return isFound;
}

template<class ItemType>
void HashTable<ItemType>::Sort(int key)
{
	if (IsEmpty(key))
	{
	}
	else
	{
		int listSize = BucketSize(key);
		bool sorted = false;

		do {
			sorted = true;
			int x = 0;
			for (node* tempPtr = head[key];
				tempPtr->next != NULL && x < listSize - 1;
				tempPtr = tempPtr->next, ++x)
			{
				if (tempPtr->currentItem > tempPtr->next->currentItem)
				{
					ItemType temp = tempPtr->currentItem;
					tempPtr->currentItem = tempPtr->next->currentItem;
					tempPtr->next->currentItem = temp;
					sorted = false;
				}
			}
			--listSize;
		} while (!sorted);
	}
}

template<class ItemType>
int HashTable<ItemType>::TableSize()
{
	return hashSize;
}

template<class ItemType>
int HashTable<ItemType>::TotalElems()
{
	return totElems;
}

template<class ItemType>
int HashTable<ItemType>::BucketSize(int key)
{
	return(!IsEmpty(key)) ? bucketSize[key] : 0;
}

template<class ItemType>
int HashTable<ItemType>::Count(ItemType searchItem)
{
	int key = Hash(searchItem);
	int t = 1;
	int h = 0;

	if (IsEmpty(key))
	{

	}
	else
	{
		if (tails[key] > heads[key])
		{
			return t;
		}
		else
		{
			return h;
		}
	}
}

template<class ItemType>
void HashTable<ItemType>::MakeEmpty()
{
	totElems = 0;
	for (int x = 0; x < hashSize; ++x)
	{
		if (!IsEmpty(x))
		{
			while (!IsEmpty(x))
			{
				node* temp = head[x];
				head[x] = head[x]->next;
				delete temp;
			}
		}
		bucketSize[x] = 0;
	}
}

template<class ItemType>
HashTable<ItemType>::~HashTable()
{
	MakeEmpty();
	delete[] head;
	delete[] bucketSize;
}

template <class ItemType>
class HashTable<ItemType>::Iterator :
	public std::iterator<std::forward_iterator_tag, ItemType>,
	public HashTable<ItemType>
{
public:
	// Iterator constructor
	Iterator(node* otherIter = NULL)
	{
		itHead = otherIter;
	}
	~Iterator() {}
	// The assignment and relational operators are straightforward
	Iterator& operator=(const Iterator& other)
	{
		itHead = other.itHead;
		return(*this);
	}
	bool operator==(const Iterator& other)const
	{
		return itHead == other.itHead;
	}
	bool operator!=(const Iterator& other)const
	{
		return itHead != other.itHead;
	}
	bool operator<(const Iterator& other)const
	{
		return itHead < other.itHead;
	}
	bool operator>(const Iterator& other)const
	{
		return other.itHead < itHead;
	}
	bool operator<=(const Iterator& other)const
	{
		return (!(other.itHead < itHead));
	}
	bool operator>=(const Iterator& other)const
	{
		return (!(itHead < other.itHead));
	}

	Iterator operator+(int incr)
	{
		node* temp = itHead;
		for (int x = 0; x < incr && temp != NULL; ++x)
		{
			temp = temp->next;
		}
		return temp;
	}
	Iterator operator+=(int incr)
	{
		for (int x = 0; x < incr && itHead != NULL; ++x)
		{
			itHead = itHead->next;
		}
		return itHead;
	}
	Iterator& operator++() // pre increment
	{
		if (itHead != NULL)
		{
			itHead = itHead->next;
		}
		return(*this);
	}
	Iterator operator++(int) // post increment
	{
		node* temp = itHead;
		this->operator++();
		return temp;
	}
	ItemType& operator[](int incr)
	{
		if (itHead == NULL || (*this + incr) == NULL)
		{
			return junk;
		}
		return(*(*this + incr));
	}

	ItemType& operator*()
	{
		if (itHead == NULL)
		{
			return junk;
		}
		return itHead->currentItem;
	}
	ItemType* operator->()
	{
		return(&**this);
	}
private:
	node* itHead;
	ItemType junk;
};
#endif //