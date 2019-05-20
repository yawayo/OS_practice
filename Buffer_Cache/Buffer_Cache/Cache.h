#pragma once
#include "BufferData.h"
#include"Queue.h"
#include"LinkedList.h"

class Cache {
public:
	Cache();
	~Cache();

	void Run();
	int GetCommand();
	int SearchBuffer();
	int Display();

protected:
	Queue<BufferData> device_0;
	Queue<BufferData> device_1;
	Queue<BufferData> device_2;
	Queue<BufferData> device_3;
	Queue<BufferData> device_4;
	LinkedList<BufferData> FreeList;
	int Command;
};
