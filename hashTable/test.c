#include "hashTable.h"

int main()
{
	HashTable<int, int> hb(7);
	hb.Insert(5);
	hb.Insert(7);
	hb.Insert(12);
	hb.Find(12);
	hb.Remove(5);
	
	return 0;
}