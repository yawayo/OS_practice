#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct NodeType
{
	T data;				///< A data for each node.
	NodeType* next;		///< A node pointer to point succeed node.
};


/**
*	Simple sorted list class for managing items.
*/
template <typename T>
class LinkedList
{
public:

	LinkedList();
	~LinkedList();

	void MakeEmpty();
	int GetLength();
	int GetCurpoint();
	int Add(T item);
	int Get(T& item);
	int Delete(T& item);
	void ResetList();
	void GetNextItem(T& item);

private:
	NodeType<T>* m_pList;
	NodeType<T>* m_pCurPointer;
	int m_nLength;
};

template <typename T>
LinkedList<T>::LinkedList()
{
	m_nLength = 0;
	m_pList = NULL;
	m_pCurPointer = NULL;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	MakeEmpty();
}

template <typename T>
void LinkedList<T>::MakeEmpty()
{
	NodeType<T> *tempPtr;

	while (m_pList != NULL)
	{
		tempPtr = m_pList;
		m_pList = m_pList->next;
		delete tempPtr;
	}

	m_nLength = 0;
}


template <typename T>
int LinkedList<T>::GetLength()
{
	return m_nLength;
}

template <typename T>
int LinkedList<T>::GetCurpoint()
{
	return m_pCurPointer;
}

template <typename T>
int LinkedList<T>::Add(T item)
{
	ResetList();

	NodeType<T> *node = new NodeType<T>;
	NodeType<T> *pre;
	T dummy;
	bool bFound = false;

	node->data = item;
	node->next = NULL;

	if (!m_nLength)
	{
		m_pList = node;
	}
	else
	{
		while (1)
		{
			pre = m_pCurPointer;

			GetNextItem(dummy);


			if (pre == NULL)
			{
				node->next = m_pCurPointer;
				m_pList = node;
				break;
			}

			node->next = m_pCurPointer;
			pre->next = node;
			break;


			if (m_pCurPointer->next == NULL)
			{
				m_pCurPointer->next = node;
				break;
			}
		}
	}

	m_nLength++;

	return 1;
}

template <typename T>
int LinkedList<T>::Get(T& item)
{
	bool moreToSearch, found;
	NodeType<T> *location;

	location = m_pList;
	found = false;
	moreToSearch = (location != NULL);

	while (moreToSearch && !found)
	{
		if (item == location->data)
		{
			found = true;
			item = location->data;
		}
		else
		{
			location = location->next;
			moreToSearch = (location != NULL);
		}
	}

	if (found)
		return 1;
	else
		return 0;
}

template <typename T>
int LinkedList<T>::Delete(T& item)
{
	bool moreToSearch, found;
	NodeType<T> *location, *predLoc;

	location = predLoc = m_pList;
	found = false;
	moreToSearch = (location != NULL);

	if (m_pList->data == item)
	{
		m_pList = location->next;
		delete location;

		found = true;
		m_nLength--;
	}
	else
	{
		while (moreToSearch)
		{
			if (item == location->data)
			{
				predLoc->next = location->next;
				delete location;

				moreToSearch = (location != NULL);
				found = true;
				m_nLength--;
				break;
			}
			predLoc = location;
			location = location->next;
			moreToSearch = (location != NULL);
		}
	}

	if (found)
		return 1;
	else
		return 0;
}

template <typename T>
void LinkedList<T>::ResetList()
{
	m_pCurPointer = NULL;
}

template <typename T>
void LinkedList<T>::GetNextItem(T& item)
{
	if (m_pCurPointer == NULL)
	{
		m_pCurPointer = m_pList;
	}
	else
		m_pCurPointer = m_pCurPointer->next;

	item = m_pCurPointer->data;

}