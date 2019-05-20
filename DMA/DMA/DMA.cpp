#include "IDE_Controller.h"
using namespace std;

// Task ���� �Է� �ޱ�
int set_tasksize() {
	int size = 0;
	while (size < 500) {
		cout << "Task ������ �Է��ϼ���(500�� �̻�) : ";
		cin >> size;
		if (size < 500)
			cout << "�ٽ� �Է��ϼ���" << endl;
	}
	return size;
}

// Task ID�� state �ʱ�ȭ
void init_task_info(Task *task, int tasksize) {
	for (int i = 0; i < tasksize; i++) {
		task[i].id = i;
		random_device random_number;
		task[i].state = random_number() % 5;
	}
}


void run() {
	int tasksize = set_tasksize();//task ���� �Է� �ޱ�
	Task* task = new Task[tasksize];
	init_task_info(task, tasksize);//task ID�� state �ʱ�ȭ
	cout << "============Task �Ҵ�============" << endl;
	IDE_Controller ctr(task, tasksize);

	system("pause");

	cout << "============Task ����============" << endl;
	thread t_disk{ &IDE_Controller::device_disk, &ctr };//Disk Device�� Thread ����
	thread t_printer{ &IDE_Controller::device_printer, &ctr };//Printer Device�� Thread ����
	thread t_monitor{ &IDE_Controller::device_monitor, &ctr };//Monitor Device�� Thread ����
	thread t_mouse{ &IDE_Controller::device_mouse, &ctr };//Mouse Device�� Thread ����
	thread t_keyboard{ &IDE_Controller::device_keyboard, &ctr };//Keyboard Device�� Thread ����

	t_disk.join();//Disk Device�� Thread ����
	t_printer.join();//Printer Device�� Thread ����
	t_monitor.join();//Monitor Device�� Thread ����
	t_mouse.join();//Mouse Device�� Thread ����
	t_keyboard.join();//Keyboard Device�� Thread ����

	cout << endl << "All task finished" << endl << endl;

	system("pause");

	cout << "============Memory Buffer============" << endl;
	//Memory Buffer ���
	while (ctr.Buffer.size()){
		Task temp = ctr.Buffer.front();//���� �ϳ��� �ް�
		cout << left << "ID : " << temp.id << " Device : " << ctr.check_state(temp) << endl;//����ϰ�
		ctr.Buffer.pop();//�����
	}

	system("pause");
}

int main() {
	run();
	return 0;
}