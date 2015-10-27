#include "map.h"


//这个图是一个无向图，要想把他设计成为有向图，，很简单，，只是在插入边和删除边的过程中不要一次性增加两个或者删除两个。。
int main()
{
	map<int, int> map(5);
	//map.Full();
	map.InsertVertices(8);
	map.InsertVertices(10);
	map.InsertVertices(20);
	map.InsertVertices(30);
	map.InsertEdge(0, 1, 23);
	map.InsertEdge(0, 2, 33);
	map.InsertEdge(2, 3, 43);
	map.InsertEdge(3, 1, 53);
	
	//map.RemoveVertices(0);
	//map.RemoveEdge(0, 1);
	map.output();
	//cout<<map.GetWeight(2, 0);
	
	
	//cout<<map.GetFirstNeighbor(2);
	map.DFS(0);
	cout << map.GetSecondNeighbor(2, 3) << endl;
	//map.Empty();
	

	return 0;
}