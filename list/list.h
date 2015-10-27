#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1024
using namespace std;

template<class T>
class SeqList
{
public:
	SeqList(int sz = MAX_SIZE);
	SeqList(SeqList<T> &L);
	SeqList<T>  operator=(SeqList<T>& L);
	~SeqList();
public:
	int Size()const{ return maxSize; }
	int Length()const{ return last + 1; }
	int Search(T &x)const;
	int Locate(int i)const;
	T GetData(int i)const;
	bool SetData(int i, const T &x);
	bool Insert(int i, const T &x);
	bool Remove(int i);
	bool IsEmpty()const;
	bool IsFull()const;
	void input();
	void output();
	void reSize(int newSize);
protected:
	T *data;
	int maxSize;
	int last;
};

template<class T>
SeqList<T>::SeqList(int sz) 
{
	if (sz > 0)
	{
		data = new T[sz];
		maxSize = sz;
		last = -1;
		if (data == NULL)
		{
			cout << "new memory failed" << endl;
			exit(1);
		}
	}
}

template<class T>
SeqList<T>::~SeqList()
{
	delete [] data;
	data = NULL;
}

template<class T>
SeqList<T>::SeqList(SeqList<T> &L)	//构造函数
{
	maxSize = L.Size();
	last = L.Length() - 1;
	data = new T[maxSize];
	if (data == NULL)
	{
		cout << "new memory failed" << endl;
		exit(1);
	}
	for (int i = 0, i < last; i++)
	{
		if (!SetData(L.GetData(i), i))
		{
			cout << "push element failed" << endl;
			exit(1);
		}
	}
}

template<class T>
int SeqList<T>::Search(T &x)const			//查找该值所对应下标
{
	for (int i = 0; i<last + 1; i++)
	{
		if (x == data[i])
		{
			return i;
		}
	}
	cout << "there is no x exist" << endl;
	return -1;
}

template<class T>
int SeqList<T>::Locate(int i)const	//查看该该下标对应的位置有没有值
{
	if (i >= 0 && i <= last)
	{
		return i;
	}
	cout << "the i is not exist" << endl;
	return -1;
}

template<class T>
T SeqList<T>::GetData(int i)const	//得到该下标所对应的值
{
	if ((Locate(i)) != -1)
	{
		return data[i];
	}
	cout << "this locate is not exist" << endl;
	return -1;
}

template<class T>
bool SeqList<T>::SetData(int i, const T &x)//设置该下标处的值为参数所给值
{
	if (i >= 0 && i <= last + 1)
	{
		if (i <= last)
		{
			cout << "this x will recover old element" << endl;
		}
		if (i == last + 1)
		{
			last++;
		}
		data[i] = x;
		return true;
	}
	cout << "sorry you enter a wrong first parameter" << endl;
	return false;
}

template<class T>
bool SeqList<T>::Insert(int i, const T &x)//在某个下标处插入值，并将后续元素后移
{
	if (last == maxSize - 1)
	{
		cout << "the list is full" << endl;
		return false;
	}
	if (i>last + 1)
	{
		cout << "sorry you insert a worng location" << endl;
		return false;
	}
	if (i == last + 1)
	{
		data[i] = x;
		last++;
		return true;
	}
	if (i >= 0 && i <= last)
	{
		for (int j = last; j >= i; j--)
		{
			data[j + 1] = data[j];
		}
		data[i] = x;
		this->last++;
		cout << "Insert complete!";
		return true;
	}
}

template<class T>
bool SeqList<T>::Remove(int i)//删除某下标对应的值，并将后面的元素前移
{
	if (i >= maxSize || i < 0)
	{
		cout << "you enter a wrong first parameter" << endl;
		return false;
	}
	if (i > last)
	{
		cout << "the first parameter you enter corresponding x is not exist" << endl;
		return false;
	}
	if (i >= 0 && i <= last)
	{
		for (; i<last; i++)
		{
			data[i] = data[i + 1];
		}
		last--;
		return true;
	}
}

template<class T>
bool SeqList<T>::IsEmpty()const	//	查看顺序表是否为空
{
	if (last == -1)
	{
		cout << "the seqlist is empty" << endl;
		return true;
	}
	else
	{
		cout << "the seqlist is not empty" << endl;
		return false;
	}
}

template<class T>
bool SeqList<T>::IsFull()const	//	查看顺序表是否满
{
	if (last == maxSize - 1)
	{
		cout << "the seqlist is full" << endl;
		return true;
	}
	else
	{
		cout << "the seqlist is not full" << endl;
		return false;
	}
}

template<class T>
void SeqList<T>::input()	//向顺序表中输入数据
{
	int size = 0;
	cout << "plase enter the list elements number " << endl;
	cin >> size;
	if (size > maxSize)
	{
		cout << "sorry ,the number you enter is wrong ";
			return;
	}
	else
	{
		cout << "please enter element one by one" << endl;
		for (int i = 0; i < size; i++)
		{
			cin >> data[i];
			last++;
		}
	}

}

template<class T>
void SeqList<T>::output()		//将顺序表中的元素打印出来
{
	if (last == -1)
	{
		cout << "the SeqList is empty";
		return;
	}
	cout << "all of the element is as follows" << endl;
	for (int i = 0; i <= last; i++)
	{
		cout << data[i];
		cout << " ";
	}
	cout << endl;
}

template<class T>
void SeqList<T>::reSize(int newSize)		//重新分配顺序表的大小
{
	if (newSize <= maxSize)
	{
		cout << "the new size you enter is smaller than the old one " << endl;
		return;
	}
	T* data1;
	data1 = new T[newSize];
	if (data == NULL)
	{
		cout << "new memory failed" << endl;
		exit(1);
	}
	for (int i = 0; i < last; i++)
	{
		data1[i] = data[i];
	}
	delete data[];
	data = data1;
	data1 = NULL;
	cout << "resize memory over !" << endl;
}

template<class T>
SeqList<T> SeqList<T>::operator=(SeqList<T> &L)
{
	if (this != &L)
	{
		last = L.Length();
		maxSize = L.Size();
		data = new T[maxsize];
		if (data == NULL)
		{
			cout << "new memory failed !" << endl;
			exit(1);
		}
		for (int i = 0; i<last, i++)
		{
			data[i] = L.data[i];
		}
	}
	cout << "assignment complete" << endl;
}



