#include <iostream>
using namespace std;

#define DefaultSize 50

enum status{Active,Empty,Deleted};

template <class T,class K>
class HashTable
{
public:
	HashTable(int d, int sz = DefaultSize);
	~HashTable();
	HashTable(HashTable<T, K> &);
	HashTable<T, K> operator=(HashTable<T, K> &);
	bool Insert(const T &);
	bool Remove(const T &);
	int Find(const T &);
protected:
	int HashFunction(const T &e);
private:
	int div;
	T  *table;
	int maxSize;
	int usedSize;
	status *st;
};

template <class T,class K>
int HashTable<T, K>::HashFunction(const T &e)
{
	int key = e % div;
	return key;
}

template <class T,class K>
HashTable<T, K>::HashTable(int d, int sz)
{
	while(sz < d)
	{
		cout << "the room is too small please retype";
		cin >> sz;
	}
	maxSize = sz;
	usedSize = 0;
	div = d;
	table = new T[sz];
	if (table == NULL)
	{cout << "new memory failed!" << endl;exit(1);}
	st = new status[sz];
	if (st == NULL)
	{cout << "new memory failed!" << endl;exit(1);}
	for (int i = 0; i < maxSize; i++)
	{st[i] = Empty;}
}

template<class T,class K>
HashTable<T, K>::~HashTable()
{
	delete[]st;
	delete[]table;
}

template<class T,class K>
HashTable<T, K>::HashTable(HashTable<T, K> &L)
{
	table = new T[L.maxSize];
	div = L.div;
	st = new status[L.maxSize];
	maxSize = L.maxSize;
	usedSize = L.usedSize;
	for (int i = 0; i < maxSize; i++)
	{
		table[i] = L.table[i];
		st[i] = L.st[i];
	}
}

template<class T,class K>
HashTable<T, K> HashTable<T, K>::operator=(HashTable<T, K> &L)
{
	if (*this != &L)
	{
		maxSize = L.maxSize;
		usedSize = L.usedSize;
		div = L.div;
		delete[]table;
		delete[]st;
		table = new T[maxSize];
		st = new status[maxSize];
		for (int i = 0; i < maxSize; i++)
		{
			table[i] = L.table[i];
			st[i] = L.st[i];
		}
	}
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////闭散列线性探查法////////////////////////////////
/*
template<class T,class K>
bool HashTable<T, K>::Insert(const T &x)
{
	if (usedSize >= maxSize)
	{
		cout << "the hashTable is full " << endl;
		return false;
	}

	int key = HashFunction(x);
	for (int j = 0; j < maxSize; j++, key++)
	{
		if ((st[key] == Active) && (table[key] == x))
		{
			cout << "this element is existed in hashTable" << endl;
			return false;
		}
		if (st[key] != Active)
		{
			table[key] = x;
			st[key] = Active;
			usedSize++;
			return true;
		}
		if (key == maxSize)
		{
			key = 0;
		}
	}
}

template<class T,class K>
int HashTable<T, K>::Find(const T &x)
{
	int i = HashFunction(x);

	for (; i < maxSize; i++)
	{
		if (table[i] == x && st[i] == Active )
		{
			return i;
		}
	}
	for (i = 0; i < HashFunction(x); i++)
	{
		if ( table[i] == x && st[i] == Active)
		{
			return i;
		}
	}
	return -1;
}
template<class T,class K>
bool HashTable<T, K>::Remove(const T &x)
{
	if (usedSize == 0)
	{
		cout << "this HashTable is empty" << endl;
		return false;
	}
	int index = Find(x);
	if (index == -1)
	{
		cout << "this element is not existd in hashTable" << endl;
		return false;
	}
	st[index] = Deleted;
	usedSize--;
	return true;
}
*/
//////////////////////////////////////////////////////////////////////////////
////////////////////////////闭散列二次探查法//////////////////////////////////

template <class T,class K>
int HashTable<T,K>::Find(const T &x)
{
	int key = HashFunction(x);
	bool visit = true;
	int i = key;
	int j = key;
	for (; i < maxSize, j >= 0;)
	{
		if (visit == true)
		{
			if (table[i] == x && st[i] == Active)
			{
				return i;
			}
			if (i == maxSize - 1)
			{
				i = 0;
			}
			if (i == j)
			{
				return -1;
			}
			i++;
			visit = false;
		}
		if (visit == false)
		{
			if (table[j] == x && st[i] == Active)
			{
				return j;
			}
			if (j == 0)
			{
				j = maxSize;
			}
			if (i == j)
			{
				return -1;
			}
			j--;
			visit = true;
		}

	}
	return -1;
}

template <class T,class K>
bool HashTable<T, K>::Insert(const T &x)
{
	if (usedSize >= maxSize)
	{
		cout << "the hashTable is full" << endl;
		return false;
	}
	int key = Find(x);
	if (key != -1)
	{
		cout << "this element is existd in hashTable" << endl;
		return false;
	}
	key = HashFunction(x);
	bool visit = true;
	int i = key;
	int j = key;
	for (; i < maxSize, j >= 0;)
	{
		if (visit == true)
		{
			if (st[i] != Active)
			{
				table[i] = x;
				st[i] = Active;
				usedSize++;
				return true;
			}
			if (i == maxSize - 1)
			{
				i = 0;
			}
			i++;
			visit = false;
		}
		if (visit == false)
		{
			if (st[j] != Active)
			{
				table[j] = x;
				st[j] = Active;
				usedSize++;
				return true;
			}
			if (j == 0)
			{
				j = maxSize;
			}
			j--;
			visit = true;
		}
	}
	return false;
}

template <class T,class K>
bool HashTable<T, K>::Remove(const T &x)
{
	if (usedSize == 0)
	{
		cout << "this hashTable is empty" << endl;
		return false;
	}
	int key = Find(x);
	if (key == -1)
	{
		cout << "the element is not in this HashTable" << endl;
		return false;
	}
	st[key] = Deleted;
	usedSize--;
	return true;
}

