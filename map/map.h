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
	bool Full();							//�鿴ͼ�ڽӱ��Ƿ���
	bool Empty();							//�鿴ͼ�ڽӱ��Ƿ�Ϊ��
	void InsertVertices(const T &data);		//�ڽӱ��в����µĶ���
	void InsertEdge(int v1,int v2,K weight);//�ڽӱ��в��붥��Ϊv1��v2֮��ȨֵΪweight�ı�
	void RemoveEdge(int v1,int v2);			//�Ƴ��ڽӱ�����v1��v2Ϊ����ı�
	void RemoveVertices(int v);				//�Ƴ��ڽӱ����±�Ϊv�Ķ���
	K GetWeight(int v1, int v2);			//ȡ���ڽӱ����±�Ϊv1��v2Ϊ����ıߵ�Ȩֵ�Ĵ�С
	int GetFirstNeighbor(int v1);			//ȡ���ڽӱ�����v1Ϊ�±�Ķ������һ��������±ꡣ
	int GetSecondNeighbor(int v1, int v2);	//ȡ���ڽӱ�����v1Ϊ�±�v2Ϊ��һ�����±����һ�����±�ֵ
	void BFS(int x);						//���ڽӱ��ĳ�����㿪ʼ����������ȱ���
	void output();
private:
	Edgetable<T,K> *table;		//�ڽӱ�
	int maxVertices;		//��󶥵���
	int numEdges;			//�ߵ���
	int numVertices;			//������
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
		while (ptr != NULL)				//���ڽӱ�������ߴ��ڲ���
		{
			
			if (ptr->dest == v2)
			{
				cout << "this edge is already exist in the map" << endl;
				return;
			}
			ptr = ptr->next;
		}

		Edge<T, K> *w = new Edge<T, K>;		//��v1�ڽӱ��в��뵽v2������߲���ͷ�巨��
		w->dest = v2;
		w->cost = weight;
		w->next = p;				
		p = w;
		numEdges++;

		Edge<T, K> *q = new Edge<T, K>;		//��v2�ڽӱ��в���v1����ߣ�����ͷ�巨��
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
	Edge<T, K> *f = table[v1].next;//Ҫɾ���ı߾����ڽӱ�Ķ���ĵ�һ����
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
	//Ҫɾ���ı߲����ڽӱ���ĵ�һ����
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

	//ɾ����һ���ڽӱ������Ӧ�ıߡ�
	f = table[v2].next;
	if (f == NULL)			//�ö���û�бߴ���
	{
		return;
	}
	if (f != NULL)			//�ö���Ҫɾ���ı߾��ڸ��ڽӱ�ĵ�һ���ߡ�
	{

		if (f->dest == v1)
		{
			table[v2].next = f->next;
			delete[]f;
			f = NULL;
		}
	}

	p = f;							//�ö���Ҫɾ���ı��ڲ��ǵ�һ���ڵ��Ӧ�ı��ϡ�
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
	//�����һ��table����ɾ�����Ǹ��ϣ�Ȼ��ı����ж�Ӧ�ıߵ�ֵ��
	table[v].data = table[numVertices-1].data;
	table[v].next = table[numVertices-1].next;
	for (int i = 0; i < numVertices-1; i++)	//�޸������ڵ�������ýڵ��йصıߡ�
	{
		if (i == v)			//�������Լ���һ��ʱ���Ͳ�����ɨ�ӹ����Ƿ��б�Ҫ�޸ĵ����⡣
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
	Edge<T, K> *ed = table[x].next;			//������¼�˶������һ����
	bool *visit = new bool[maxVertices];	//�������ö����ǲ��Ǳ����ʹ�
	for (int i = 0; i < maxVertices; i++)visit[i] = false;
	int i = 0;								//����ѭ��������ͨ��ͼ
	cout << table[x].data<< " ";			//���ȴ�ӡ�ö��㡣
	visit[x] = true;						//����һ�����ʺ�ı��ֵ��Ϊ�档
	for (int i = 0; i < numVertices; i++)
	{
		while (ed != NULL)					//���ö�����ٽֱ߲�Ϊ��ʱ������һ�������
		{
			x = ed->dest;					//�õ���һ��Ҫ���ʵĶ�����±�
			ed = _BFS(table[ed->dest],visit,x);
		}
		if (i == x)
			continue;						//������ͨ��ͼ�Ķ����ʶ��x��ͬʱ������
		if (visit[i] == false)				//���ѡ�����ͨ��ͼ�Ķ��������û�б����ʹ��Ķ��㡣
		{
			cout << table[i].data << " ";	//���û�з�������һ�������ȷ�������Ȼ������ȱ�����
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
	if (visit[x] == false)					//���ö���û�б�����ʱ�Ž��з���
	{
		cout << t.data<<" ";						//���ʸö���
		visit[x] = true;						//����־λ��Ϊ1						
		return t.next;						//���ظö���ıߡ�
	}
	return NULL;							//����ö��㱻���ʣ��򷵻ؿա�
}



