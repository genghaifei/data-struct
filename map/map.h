#include <iostream>
using namespace std;

#define defaultSize 10

template<class T,class K>
struct Edge
{
	int dest;
	K cost;
	Edge<T,K> *next;
	Edge(){}
	Edge(int destNum,K costNum) :dest(destNum), cost(costNom), next(NULL)
	{}
	bool operator!=(Edge<T,K> &l)
	{
		if (dest != l.dest)
		{
			return true;
		}
		else
			return false;
	}
};

template<class T,class K>
struct Edgetable
{
	T data;
	Edge<T,K> *next;
};


template<class T,class K>
class map
{
public:
	map(int sz = defaultSize);
	~map();
	bool Full();							//查看图邻接表是否满
	bool Empty();							//查看图邻接表是否为空
	void InsertVertices(const T &data);		//邻接表中插入新的顶点
	void InsertEdge(int v1,int v2,K weight);//邻接表中插入顶点为v1和v2之间权值为weight的边
	void RemoveEdge(int v1,int v2);			//移除邻接表中以v1和v2为顶点的边
	void RemoveVertices(int v);				//移除邻接表中下标为v的顶点
	K GetWeight(int v1, int v2);			//取得邻接表中下标为v1和v2为顶点的边的权值的大小
	int GetFirstNeighbor(int v1);			//取得邻接表中以v1为下标的顶点的下一个顶点的下标。
	int GetSecondNeighbor(int v1, int v2);	//取得邻接表中以v1为下标v2为下一顶点下标的下一顶点下标值
	void BFS(int x);						//从邻接表的某个顶点开始进行深度优先遍历
	void output();
private:
	Edgetable<T,K> *table;		//邻接表
	int maxVertices;		//最大顶点数
	int numEdges;			//边的数
	int numVertices;			//顶点数
};
template<class T,class K>
map<T, K>::map(int sz )
{
	maxVertices = sz;
	numEdges = 0;
	numVertices = 0;
	table = new Edgetable<T,K> [maxVertices];
	if (table == NULL)
	{
		cout << "new memory failed";
		exit(1);
	}
	for (int i = 0; i < sz; i++)
	{
		table[i].next = NULL;
	}
}
template <class T,class K>
map<T, K>::~map()
{
	for (int i = 0; i < numVertices; i++)
	{
		Edge<T, K> *p;
		p = table[i].next;
		while (table[i].next != NULL)
		{	
			p = table[i].next;
			table[i].next = p->next;
			delete[]p;
		}
	}
	delete[]table;
}

template <class T,class K>
bool map<T, K>::Full()
{
	if (numVertices == maxVertices)
	{
		cout << "the map table is full" << endl;
		return true;
	}
	else
	{
		cout << "the map table is not full" << endl;
		return false;
	}
}

template <class T,class K>
bool map<T, K>::Empty()
{
	if (numVertices == 0)
	{
		cout << "the map table is empty" << endl;
		return true;
	}
	else
	{
		cout << "the map table is not empty" << endl;
		return false;
	}
}

template <class T,class K>
void map<T, K>::InsertVertices(const T &data)
{
	if (numVertices == maxVertices)
	{
		cout << "sorry ,the table is full can not insert Vertice" << endl;
		return;
	}
	table[numVertices].data = data;
	numVertices++;
}

template <class T,class K>
void map<T, K>::InsertEdge(int v1, int v2, K weight)
{
	if ((v1 >= 0 && v1 < numVertices) && (v2 >= 0 && v2 < numVertices))
	{
		
		Edge<T, K> *&p = table[v1].next;
		Edge<T, K> *ptr = p;
		while (ptr != NULL)				//看邻接表中这个边存在不。
		{
			
			if (ptr->dest == v2)
			{
				cout << "this edge is already exist in the map" << endl;
				return;
			}
			ptr = ptr->next;
		}

		Edge<T, K> *w = new Edge<T, K>;		//给v1邻接表中插入到v2的这个边采用头插法。
		w->dest = v2;
		w->cost = weight;
		w->next = p;				
		p = w;
		numEdges++;

		Edge<T, K> *q = new Edge<T, K>;		//给v2邻接表中插入v1这个边，采用头插法。
		Edge<T, K> *&t = table[v2].next;
		q->dest = v1;
		q->cost = weight;
		q->next = t;
		t = q;
		numEdges++;
	}
}

template<class T,class K>
void map<T, K>::RemoveEdge(int v1, int v2)
{
	if ((v1 < 0 || v1 > numEdges) || (v2 < 0 || v2 > numEdges))
	{
		cout << "sorry you enter a wrong paramater" << endl;
		return;
	}
	Edge<T, K> *f = table[v1].next;//要删除的边就在邻接表的顶点的第一个边
	Edge<T, K> *p;
	if (f == NULL)
	{
		return;
	}
	if (f != NULL)
	{

		if (f->dest == v2)
		{
			table[v1].next = f->next;
			delete[]f;
			f = NULL;
		}
	}
	//要删除的边不在邻接表顶点的第一个边
	p = f;
	while (f != NULL)
	{
		if (f->dest == v2)
		{
			p->next = f->next;
			delete[]f;
			f = NULL;
			break;
		}
		p = f;
		f = f->next;
	}

	//删除另一个邻接表的所对应的边。
	f = table[v2].next;
	if (f == NULL)			//该顶点没有边存在
	{
		return;
	}
	if (f != NULL)			//该顶点要删除的边就在该邻接表的第一个边。
	{

		if (f->dest == v1)
		{
			table[v2].next = f->next;
			delete[]f;
			f = NULL;
		}
	}

	p = f;							//该顶点要删除的边在不是第一个节点对应的边上。
	while (f != NULL)
	{
		if (f->dest == v1)
		{
			p->next = f->next;
			delete[]f;
			f = NULL;
			break;
		}
		p = f;
		f = f->next;
	}

}

template<class T,class K>
void map<T, K>::RemoveVertices(int v)
{
	if (v < 0 || v > numVertices)
	{
		cout << "you enter a wrong parameter" << endl;
		return;
	}

	for (int vi = 0; vi < numVertices; vi++)
	{
		if (vi == v)
			continue;
		RemoveEdge(vi, v);
	}
	//将最后一个table放在删除的那个上，然后改变所有对应的边的值。
	table[v].data = table[numVertices-1].data;
	table[v].next = table[numVertices-1].next;
	for (int i = 0; i < numVertices-1; i++)	//修改其他节点中有与该节点有关的边。
	{
		if (i == v)			//当遇到自己这一行时，就不用来扫视关于是否有边要修改的问题。
			continue;
		Edge<T, K> *q = table[i].next;
		while (q != NULL)
		{
			if (q->dest == numVertices-1)
			{
				q->dest = v;
				break;
			}
			q = q->next;
		}
	}
	numVertices--;

}

template<class T,class K>
K map<T, K>::GetWeight(int v1, int v2)
{
	if ((v1 < 0 || v1 > numEdges) || (v2 < 0 || v2 > numEdges))
	{
		cout << "sorry you enter a wrong paramater" << endl;
		return NULL;
	}
	Edge<T, K> *p = table[v1].next;
	while (p != NULL)
	{
		if (p->dest == v2)
		{
			return p->cost;
		}
		p = p->next;
	}
	cout << "this edge is not exist" << endl;
	return NULL;
}

template<class T,class K>
int map<T, K>::GetFirstNeighbor(int v1)
{
	if (v1 < 0 || v1 > numEdges) 
	{
		cout << "sorry you enter a wrong paramater" << endl;
		return -1;
	}
	Edge<T, K> *p = table[v1].next;
	if (p != NULL)
		return p->dest;
	return NULL;
}

template<class T,class K>
int map<T, K>::GetSecondNeighbor(int v1, int v2)
{
	if ((v1 < 0 || v1 > numEdges) || (v2 < 0 || v2 > numEdges))
	{
		cout << "sorry you enter a wrong paramater" << endl;
		return -1;
	}
	Edge<T, K> *p = table[v1].next;
	if (p != NULL && table[p->dest].next != NULL)
	{
		p = table[p->dest].next;
		while (p->next != NULL)
		{
			if (p->dest == v2)
				p = p->next;
			if (p->dest != v2)
				return p->dest;	
		}
	}
	return -1;
}

template <class T,class K>
void map<T, K>::output()
{
	cout << "**********************OUTPUT*************************************" << endl;
	for (int i = 0; i < numVertices; i++)
	{
		Edge<T, K> *q = table[i].next;
		cout << "line " << i << " data:"<<table[i].data<<"\t";
		while (q != NULL)
		{
			cout << "(" << i<<","<<q->dest << "  " << q->cost << ")" << "  ";
			q = q->next;
		}
		cout << endl;
	}
	cout << "***********************END***************************************" << endl;
}
template<class T,class K>
void map<T, K>::BFS(int x)
{
	if (x < 0 || x > numVertices)
	{
		cout << "You enter a wrong paramter" << endl;
		return;
	}
	Edge<T, K> *ed = table[x].next;			//用来记录此顶点的下一条边
	bool *visit = new bool[maxVertices];	//用来检测该顶点是不是被访问过
	for (int i = 0; i < maxVertices; i++)visit[i] = false;
	int i = 0;								//用来循环遍历连通子图
	cout << table[x].data<< " ";			//首先打印该顶点。
	visit[x] = true;						//将第一个访问后的标记值置为真。
	for (int i = 0; i < numVertices; i++)
	{
		while (ed != NULL)					//当该顶点的临街边不为空时进行下一顶点访问
		{
			x = ed->dest;					//得到下一个要访问的顶点的下标
			ed = _BFS(table[ed->dest],visit,x);
		}
		if (i == x)
			continue;						//当该连通子图的顶点标识和x相同时跳过。
		if (visit[i] == false)				//如果选择的连通子图的顶点必须是没有被访问过的顶点。
		{
			cout << table[i].data << " ";	//如果没有访问其中一个，则先访问他，然后再深度遍历。
			visit[i] = true;
			ed = table[i].next;
		}
	}	
	delete[]visit;
	cout << endl;
}

template<class T,class K>
Edge<T, K>* _BFS(Edgetable<T, K> t,bool *visit,int x)
{
	if (visit[x] == false)					//当该顶点没有被访问时才进行访问
	{
		cout << t.data<<" ";						//访问该顶点
		visit[x] = true;						//将标志位置为1						
		return t.next;						//返回该顶点的边。
	}
	return NULL;							//如果该顶点被访问，则返回空。
}



