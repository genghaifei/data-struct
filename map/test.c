#include "map.h"


//���ͼ��һ������ͼ��Ҫ�������Ƴ�Ϊ����ͼ�����ܼ򵥣���ֻ���ڲ���ߺ�ɾ���ߵĹ����в�Ҫһ����������������ɾ����������
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