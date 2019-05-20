#pragma once

#include<iostream>

using namespace std;

#define maxQueue 11

template<class T>
class Queue {
public:
	Queue();
	~Queue();
	int GetLength();
	void ResetList();
	int GetNextItem(T &item);
	bool IsFull();
	bool IsEmpty();
	void MakeEmpty();
	void EnQueue(T item);
	void DeQueue(T &item);
	int DeleteItem(T &key);
	int GetItem(T &key);

private:
	int m_CurPointer;    //iterator
	int m_iFront;    //index of one infront of the first element.
	int m_iRear;    //index of the last element.
	int m_nmaxQueue;    //max size of the queue.
	int m_Length;    //numer of data in list
	BufferData *m_pItems;    //pointer for dynamic allocation.
};

//Allocate dynamic array whose size is maxQueue.
template<class T>
Queue<T>::Queue() {
	m_pItems = new T[maxQueue];    //m_pItems�� ũ�Ⱑ maxQueue�� �迭�� �����.
	m_Length = 0;
	m_nmaxQueue = maxQueue;
	m_iFront = m_nmaxQueue - 1;
	m_iRear = m_nmaxQueue - 1;    //��� �������� �ʱ�ȭ�����ش�.
}

//Destruct the object. Free the array dynamically allocated.
template<class T>
Queue<T>::~Queue() {
	delete[] m_pItems;    //�����Ҵ��ߴ� �޸𸮸� �������ش�.
}

//list�� ���̸� ��ȯ�Ѵ�.
template<class T>
int Queue<T>::GetLength() {
	return m_Length;
}

//Determines whether the queue is full.
template<class InfoType>
bool Queue<InfoType>::IsFull() {
	if (m_iFront - m_iRear == 1 || m_iRear - m_iFront == m_nmaxQueue - 1)
		return 1;    //m_iFront�� m_iRear���� 1 ���϶��� �� �����̹Ƿ� 1�� �����Ѵ�. m_iFront�� 0�϶��� m_iRear�� m_nmaxQueue-1�� ������ �� �����̴�.

	return 0;    //�� ���� �ʾ����� 0�� �����Ѵ�.
}

//Determines whether the queue is empty.
template<class T>
bool Queue<T>::IsEmpty() {
	if (m_iFront == m_iRear)
		return 1;

	return 0;
}


//Adds newItem to the last of the queue.
template<class T>
void Queue<T>::EnQueue(T item) {
	if (IsFull())     //���� á�� ��
	{
		T temp = item;    //�ӽú��� temp�� ���� ���� ����

		DeQueue(item);    //���� ���� ����Ʈ���� �����.
		m_iRear = (m_iRear + 1) % m_nmaxQueue;
		m_pItems[m_iRear] = temp;    //temp���� �־��ش�
	}    //���� ������ ������ ����

	else {
		m_iRear = (m_iRear + 1) % m_nmaxQueue;
		m_pItems[m_iRear] = item;

		m_Length++; //m_iRear�� 1���������ְ� item���� �־��ش�.
	}
}

//Removes first item from the queue.
template<class T>
void Queue<T>::DeQueue(T &item) {
	if (IsEmpty())
		cout << "������ϴ�";

	m_iFront = (m_iFront + 1) % m_nmaxQueue;
	item = m_pItems[m_iFront];

	m_Length--; //m_iFront�� 1 ���������ְ� ������ ���� item�� �������ش�.
}

// ����� ���� Info�� ť�� ���� ��� ����� ������ �� 1�� �����ϰ� ť�� ���ų� �� ť�̸� 0�� �����Ѵ�.
template<typename T>
int Queue<T>::DeleteItem(T &key) {
	if (!IsEmpty())
		for (int i = 0; i < maxQueue; i++)
			if (m_pItems[i].Getid() == key.Getid()) {
				if (m_iRear > m_iFront) {
					for (i; i < maxQueue; i++)
						if (i != maxQueue - 1)
							m_pItems[i].Setinfo(m_pItems[i + 1].Getid(), m_pItems[i + 1].Getid() % 5);
				}
				else {
					if (i <= m_iRear)
						for (i; i <= m_iRear; i++)
							m_pItems[i].Setinfo(m_pItems[i + 1].Getid(), m_pItems[i + 1].Getid() % 5);
					else {
						for (i; i < maxQueue; i++)
							if (i != maxQueue - 1)
								m_pItems[i].Setinfo(m_pItems[i + 1].Getid(), m_pItems[i + 1].Getid() % 5);
							else
								m_pItems[i].Setinfo(m_pItems[i + 1].Getid(), m_pItems[i + 1].Getid() % 5);

						for (int j = 0; j <= m_iRear; j++)
							m_pItems[i].Setinfo(m_pItems[i + 1].Getid(), m_pItems[i + 1].Getid() % 5);
					}
				}

				if (m_iRear == 0)
					m_iRear = maxQueue - 1;
				else
					m_iRear--;

				m_Length--;
				return 1;

			}
	return 0;
}

template<typename T>
int Queue<T>::GetItem(T &key) {
	if (!IsEmpty())
		for (int i = 0; i < maxQueue; i++)
			if (m_pItems[i].GetId() == key.GetId()) {
				m_pItems[i].SetTitle(key.GetTitle());
				return 1;
			}
	return 0;
}


template<class T>
int Queue<T>::GetNextItem(T &item) {
	m_CurPointer = (m_CurPointer + 1) % m_nmaxQueue;// list pointer ����
	item = m_pItems[m_CurPointer];    // ���� list pointer�� ���ڵ带 ����

	return m_CurPointer;    //iterator�� ��ġ ��ȯ
}

//iterator�� �ʱ�ȭ ��Ų��.
template<class T>
void Queue<T>::ResetList() {
	m_CurPointer = m_iFront;    //iterator�� front������ �ʱ�ȭ ��Ų��.
}


//Makes the queue empty.
template<class T>
void Queue<T>::MakeEmpty() {
	m_iFront = m_nmaxQueue - 1;
	m_iRear = m_nmaxQueue - 1;    //�����ڿ� ���� ������ m_iFront�� m_iRear�� �������ش�.
	m_Length = 0;
}