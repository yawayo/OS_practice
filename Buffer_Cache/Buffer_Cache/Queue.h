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
	m_pItems = new T[maxQueue];    //m_pItems에 크기가 maxQueue인 배열을 만든다.
	m_Length = 0;
	m_nmaxQueue = maxQueue;
	m_iFront = m_nmaxQueue - 1;
	m_iRear = m_nmaxQueue - 1;    //멤버 변수들을 초기화시켜준다.
}

//Destruct the object. Free the array dynamically allocated.
template<class T>
Queue<T>::~Queue() {
	delete[] m_pItems;    //동적할당했던 메모리를 해제해준다.
}

//list의 길이를 반환한다.
template<class T>
int Queue<T>::GetLength() {
	return m_Length;
}

//Determines whether the queue is full.
template<class InfoType>
bool Queue<InfoType>::IsFull() {
	if (m_iFront - m_iRear == 1 || m_iRear - m_iFront == m_nmaxQueue - 1)
		return 1;    //m_iFront가 m_iRear보다 1 앞일때는 꽉 찬것이므로 1을 리턴한다. m_iFront가 0일때는 m_iRear가 m_nmaxQueue-1과 같을때 꽉 찬것이다.

	return 0;    //꽉 차지 않았으면 0을 리턴한다.
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
	if (IsFull())     //가득 찼을 때
	{
		T temp = item;    //임시변수 temp에 현재 값을 저장

		DeQueue(item);    //현재 값을 리스트에서 지운다.
		m_iRear = (m_iRear + 1) % m_nmaxQueue;
		m_pItems[m_iRear] = temp;    //temp값을 넣어준다
	}    //가장 오래된 데이터 삭제

	else {
		m_iRear = (m_iRear + 1) % m_nmaxQueue;
		m_pItems[m_iRear] = item;

		m_Length++; //m_iRear를 1증가시켜주고 item값을 넣어준다.
	}
}

//Removes first item from the queue.
template<class T>
void Queue<T>::DeQueue(T &item) {
	if (IsEmpty())
		cout << "비었습니다";

	m_iFront = (m_iFront + 1) % m_nmaxQueue;
	item = m_pItems[m_iFront];

	m_Length--; //m_iFront를 1 증가시켜주고 삭제될 값을 item에 복사해준다.
}

// 지우고 싶은 Info가 큐에 있을 경우 지우고 끌어당긴 후 1을 리턴하고 큐에 없거나 빈 큐이면 0을 리턴한다.
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
	m_CurPointer = (m_CurPointer + 1) % m_nmaxQueue;// list pointer 증가
	item = m_pItems[m_CurPointer];    // 현재 list pointer의 레코드를 복사

	return m_CurPointer;    //iterator의 위치 반환
}

//iterator를 초기화 시킨다.
template<class T>
void Queue<T>::ResetList() {
	m_CurPointer = m_iFront;    //iterator를 front값으로 초기화 시킨다.
}


//Makes the queue empty.
template<class T>
void Queue<T>::MakeEmpty() {
	m_iFront = m_nmaxQueue - 1;
	m_iRear = m_nmaxQueue - 1;    //생성자와 같은 값으로 m_iFront와 m_iRear를 변경해준다.
	m_Length = 0;
}