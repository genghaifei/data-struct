#include "HashBucket.h"

int main()
{
	HashBucket<int, int> ha(11);
	ha.Insert(12);
	ha.Insert(14);
	ha.Insert(34);
	ha.Insert(225);

	ha.Remove(23);
	ha.Remove(34);
	ha.Find(34);

	return 0;
}