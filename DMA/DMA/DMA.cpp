#include "IDE_Controller.h"
using namespace std;

// Task 개수 입력 받기
int set_tasksize() {
	int size = 0;
	while (size < 500) {
		cout << "Task 개수를 입력하세요(500개 이상) : ";
		cin >> size;
		if (size < 500)
			cout << "다시 입력하세요" << endl;
	}
	return size;
}

// Task ID와 state 초기화
void init_task_info(Task *task, int tasksize) {
	for (int i = 0; i < tasksize; i++) {
		task[i].id = i;
		random_device random_number;
		task[i].state = random_number() % 5;
	}
}


void run() {
	int tasksize = set_tasksize();//task 개수 입력 받기
	Task* task = new Task[tasksize];
	init_task_info(task, tasksize);//task ID와 state 초기화
	cout << "============Task 할당============" << endl;
	IDE_Controller ctr(task, tasksize);

	system("pause");

	cout << "============Task 수행============" << endl;
	thread t_disk{ &IDE_Controller::device_disk, &ctr };//Disk Device의 Thread 생성
	thread t_printer{ &IDE_Controller::device_printer, &ctr };//Printer Device의 Thread 생성
	thread t_monitor{ &IDE_Controller::device_monitor, &ctr };//Monitor Device의 Thread 생성
	thread t_mouse{ &IDE_Controller::device_mouse, &ctr };//Mouse Device의 Thread 생성
	thread t_keyboard{ &IDE_Controller::device_keyboard, &ctr };//Keyboard Device의 Thread 생성

	t_disk.join();//Disk Device의 Thread 종료
	t_printer.join();//Printer Device의 Thread 종료
	t_monitor.join();//Monitor Device의 Thread 종료
	t_mouse.join();//Mouse Device의 Thread 종료
	t_keyboard.join();//Keyboard Device의 Thread 종료

	cout << endl << "All task finished" << endl << endl;

	system("pause");

	cout << "============Memory Buffer============" << endl;
	//Memory Buffer 출력
	while (ctr.Buffer.size()){
		Task temp = ctr.Buffer.front();//끝에 하나를 받고
		cout << left << "ID : " << temp.id << " Device : " << ctr.check_state(temp) << endl;//출력하고
		ctr.Buffer.pop();//지우기
	}

	system("pause");
}

int main() {
	run();
	return 0;
}