#include<iostream>
#include <vector>
using namespace std;

#define MAX 100

template<class K,class V>
struct BucketNode
{
	K key;
	V value;
	BucketNode<K,V> *link;
	BucketNode()
	{
		key = -1;
		value = -1;
		link = NULL;
	}
};

template<class K,class V>
class HashBucket
{
public:
	HashBucket(int div, int sz = MAX);
	~HashBucket();
	bool Insert(V);
	bool Remove(V);
	K Find(const V);

protected:
	K HashFunction(V si)
	{
		return si % div;
	}
private:
	int div;
	int capacity;
	int usedSize;
	BucketNode<K,V> *table;
};

template <class K,class V>
HashBucket<K,V>::HashBucket(int d,int sz)
{
	div = d;
	capacity = sz;
	usedSize = 0;
	table = new BucketNode<K, V>[d];
	if (table == NULL)exit(0);
}

template <class K,class V>
HashBucket<K, V>::~HashBucket()
{
	BucketNode<K,V> *p,*q;
	for (int i = 0; i < div; i++)
	{
		p = table[i].link;
		q = p;
		while (p != NULL)
		{
			q = p;
			p = p->link;
			delete[]q;
		}
	}
	delete[]table;
}

template <class K,class V>
bool HashBucket<K, V>::Insert(V val)
{
	if (usedSize < capacity)
	{
		K key = HashFunction(val);
		BucketNode<K, V> *bn = new BucketNode<K, V>;
		if (bn == NULL)exit(1);
		bn->link = NULL;
		bn->key = key;
		bn->value = val;

		table[key].link = bn;

		return true;
	}
	else
	{
		cout << "sorry ,the hashTable is full!" << endl;
		return false;
	}
}


template <class K,class V>
bool HashBucket<K, V>::Remove(V val)
{
	int key = HashFunction(val);
	BucketNode<K, V> *ptr = table[key].link;
	while (ptr != NULL)
	{
		if (ptr->value == val)
		{
			return true;
		}
		ptr = ptr->link;
	}
	return false;
}

template <class K,class V>
K HashBucket<K, V>::Find(const V val)
{
	int key = HashFunction(val);
	BucketNode<K, V> *ptr = table[key].link;
	while (ptr != NULL)
	{
		if (ptr->value == val)
		{
			return ptr->key;
		}
		ptr = ptr->link;
	}
	return -1;
}
