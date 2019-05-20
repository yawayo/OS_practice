#include "IDE_Controller.h"
using namespace std;

random_device random_number;

mutex IDE_Controller::mtx;

//������
IDE_Controller::IDE_Controller(Task* task, int task_size) {
	size = task_size;
	for (int i = 0; i < size; i++) {
		if (task[i].state == 0)// Device�� Disk�� Disk Queue�� ����
			Q_disk.push(task[i]);
		if (task[i].state == 1)// Device�� Printer�� Disk Queue�� ����
			Q_printer.push(task[i]);
		if (task[i].state == 2)// Device�� Monitor�� Disk Queue�� ����
			Q_monitor.push(task[i]);
		if (task[i].state == 3)// Device�� Mouse�� Disk Queue�� ����
			Q_mouse.push(task[i]);
		if (task[i].state == 4)// Device�� Keyboard�� Disk Queue�� ����
			Q_keyboard.push(task[i]);
		cout << left << "ID : " << task[i].id << "  Device : " << check_state(task[i]) << endl;
	}
}

// Disk Device Controller
void IDE_Controller::device_disk() {
	int disk_size = Q_disk.size();// Disk Queue�� ũ�� ���
	for (int i = 0; i < disk_size; i++) {
		int C = random_number() % 5;// Device�� �������� �ʱ� ���ؼ�
		if (C == 0)// 1/5�� Ȯ���� 1�� ��ž
			this_thread::sleep_for(chrono::duration<double>(1));
		lock_guard<mutex> guard(mtx);// ��ȣ ����
		if (Q_disk.size() != 0) {// Queue�� ���������� ���� ����
			Task temp = Q_disk.front();// Disk Queue �� �� ��������
			cout << left << "ID : " << temp.id << " Device : " << check_state(temp) << endl;
			Q_disk.pop();// �� �� ������
			DMA_Controller(temp);// Memory Buffer�� �ִ´�
		}
		else//������ ���� ���
			cout << "finish all task" << endl;
	}
}
void IDE_Controller::device_printer() {
	int printer_size = Q_printer.size();// Printer Queue�� ũ�� ���
	for (int i = 0; i < printer_size ; i++) {
		int C = random_number() % 5;// Device�� �������� �ʱ� ���ؼ�
		if (C == 0)// 1/5�� Ȯ���� 1�� ��ž
			this_thread::sleep_for(chrono::duration<double>(1));
		lock_guard<mutex> guard(mtx);// ��ȣ ����
		if (Q_disk.size() != 0) {// Queue�� ���������� ���� ����
			Task temp = Q_printer.front();// Printer Queue �� �� ��������
			cout << left << "ID : " << temp.id << " Device : " << check_state(temp) << endl;
			Q_printer.pop();// �� �� ������
			DMA_Controller(temp);// Memory Buffer�� �ִ´�
		}
		else//������ ���� ���
			cout << "finish all task" << endl;
	}
}
void IDE_Controller::device_monitor() {
	int monitor_size = Q_monitor.size();// Monitor Queue�� ũ�� ���
	for (int i = 0; i < monitor_size; i++) {
		int C = random_number() % 5;// Device�� �������� �ʱ� ���ؼ�
		if (C == 0)// 1/5�� Ȯ���� 1�� ��ž
			this_thread::sleep_for(chrono::duration<double>(1));
		lock_guard<mutex> guard(mtx);// ��ȣ ����
		if (Q_monitor.size() != 0) {// Queue�� ���������� ���� ����
			Task temp = Q_monitor.front();// Monitor Queue �� �� ��������
			cout << left << "ID : " << temp.id << " Device : " << check_state(temp) << endl;
			Q_monitor.pop();// �� �� ������
			DMA_Controller(temp);// Memory Buffer�� �ִ´�
		}
		else//������ ���� ���
			cout << "finish all task" << endl;
	}
}
void IDE_Controller::device_mouse() {
	int mouse_size = Q_mouse.size();// Mouse Queue�� ũ�� ���
	for (int i = 0; i < mouse_size; i++) {
		int C = random_number() % 5;// Device�� �������� �ʱ� ���ؼ�
		if (C == 0)// 1/5�� Ȯ���� 1�� ��ž
			this_thread::sleep_for(chrono::duration<double>(1));
		lock_guard<mutex> guard(mtx);// ��ȣ ����
		if (Q_mouse.size() != 0) {// Queue�� ���������� ���� ����
			Task temp = Q_mouse.front();// Mouse Queue �� �� ��������
			cout << left << "ID : " << temp.id << " Device : " << check_state(temp) << endl;
			Q_mouse.pop();// �� �� ������
			DMA_Controller(temp);// Memory Buffer�� �ִ´�
		}
		else//������ ���� ���
			cout << "finish all task" << endl;
	}
}
void IDE_Controller::device_keyboard() {
	int keyboard_size = Q_keyboard.size();// Keyboard Queue�� ũ�� ���
	for (int i = 0; i < keyboard_size; i++) {
		int C = random_number() % 5;// Device�� �������� �ʱ� ���ؼ�
		if (C == 0)// 1/5�� Ȯ���� 1�� ��ž
			this_thread::sleep_for(chrono::duration<double>(1));
		lock_guard<mutex> guard(mtx);// ��ȣ ����
		if (Q_keyboard.size() != 0) {// Queue�� ���������� ���� ����
			Task temp = Q_keyboard.front();// Keyboard Queue �� �� ��������
			cout << left << "ID : " << temp.id << " Device : " << check_state(temp) << endl;
			Q_keyboard.pop();// �� �� ������
			DMA_Controller(temp);// Memory Buffer�� �ִ´�
		}
		else//������ ���� ���
			cout << "finish all task" << endl;
	}
}
//Device ���(0:Disk 1:Printer 2:Monitor 3:Mouse 4:Keyboard)
string IDE_Controller::check_state(Task task) {
	if (task.state == 0)
		return "Disk";
	if (task.state == 1)
		return "Printer";
	if (task.state == 2)
		return "Monitor";
	if (task.state == 3)
		return "Mouse";
	if (task.state == 4)
		return "Keyboard";
}
//���� ����� Task�� Memory Buffer�� ����
void IDE_Controller::DMA_Controller(Task task) {
	Buffer.push(task);
}