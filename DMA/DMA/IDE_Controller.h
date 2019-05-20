#pragma once
#include <iostream>
#include <mutex>
#include <string>
#include <queue>
#include <random>
#include <chrono>
#include <thread>
#include <condition_variable>

using namespace std;

struct Task {
	int id;
	int state;
};

class IDE_Controller{
public:
	IDE_Controller() {};
	IDE_Controller(Task* task, int task_size);//������
	~IDE_Controller() {};
	int size;//Task ����
	int device;//Device(0:Disk 1:Printer 2:Monitor 3:Mouse 4:Keyboard)
	queue<Task> Q_disk;//Disk Queue
	queue<Task> Q_printer;//Printer Queue
	queue<Task> Q_monitor;//Monitor Queue
	queue<Task> Q_mouse;//Mouse Queue
	queue<Task> Q_keyboard;//Keyboard Queue
	queue<Task> Buffer;//Memory Buffer
	static mutex mtx;//Mutex
	condition_variable cv;
	void device_disk();//Disk Device Controller
	void device_printer();//Printer Device Controller
	void device_monitor();//Monitor Device Controller
	void device_mouse();//Mouse Device Controller
	void device_keyboard();//Keyboard Device Controller
	string check_state(Task task);//Device ���(0:Disk 1:Printer 2:Monitor 3:Mouse 4:Keyboard)
	void DMA_Controller(Task task);//���� ����� Task�� Memory Buffer�� ����
};