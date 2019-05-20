#include "IDE_Controller.h"
using namespace std;

random_device random_number;

mutex IDE_Controller::mtx;

//생성자
IDE_Controller::IDE_Controller(Task* task, int task_size) {
	size = task_size;
	for (int i = 0; i < size; i++) {
		if (task[i].state == 0)// Device가 Disk면 Disk Queue에 저장
			Q_disk.push(task[i]);
		if (task[i].state == 1)// Device가 Printer면 Disk Queue에 저장
			Q_printer.push(task[i]);
		if (task[i].state == 2)// Device가 Monitor면 Disk Queue에 저장
			Q_monitor.push(task[i]);
		if (task[i].state == 3)// Device가 Mouse면 Disk Queue에 저장
			Q_mouse.push(task[i]);
		if (task[i].state == 4)// Device가 Keyboard면 Disk Queue에 저장
			Q_keyboard.push(task[i]);
		cout << left << "ID : " << task[i].id << "  Device : " << check_state(task[i]) << endl;
	}
}

// Disk Device Controller
void IDE_Controller::device_disk() {
	int disk_size = Q_disk.size();// Disk Queue의 크기 계산
	for (int i = 0; i < disk_size; i++) {
		int C = random_number() % 5;// Device가 독점하지 않기 위해서
		if (C == 0)// 1/5의 확률로 1초 스탑
			this_thread::sleep_for(chrono::duration<double>(1));
		lock_guard<mutex> guard(mtx);// 상호 배제
		if (Q_disk.size() != 0) {// Queue에 남아있으면 다음 수행
			Task temp = Q_disk.front();// Disk Queue 맨 끝 가져오기
			cout << left << "ID : " << temp.id << " Device : " << check_state(temp) << endl;
			Q_disk.pop();// 맨 끝 버리기
			DMA_Controller(temp);// Memory Buffer에 넣는다
		}
		else//끝나면 다음 출력
			cout << "finish all task" << endl;
	}
}
void IDE_Controller::device_printer() {
	int printer_size = Q_printer.size();// Printer Queue의 크기 계산
	for (int i = 0; i < printer_size ; i++) {
		int C = random_number() % 5;// Device가 독점하지 않기 위해서
		if (C == 0)// 1/5의 확률로 1초 스탑
			this_thread::sleep_for(chrono::duration<double>(1));
		lock_guard<mutex> guard(mtx);// 상호 배제
		if (Q_disk.size() != 0) {// Queue에 남아있으면 다음 수행
			Task temp = Q_printer.front();// Printer Queue 맨 끝 가져오기
			cout << left << "ID : " << temp.id << " Device : " << check_state(temp) << endl;
			Q_printer.pop();// 맨 끝 버리기
			DMA_Controller(temp);// Memory Buffer에 넣는다
		}
		else//끝나면 다음 출력
			cout << "finish all task" << endl;
	}
}
void IDE_Controller::device_monitor() {
	int monitor_size = Q_monitor.size();// Monitor Queue의 크기 계산
	for (int i = 0; i < monitor_size; i++) {
		int C = random_number() % 5;// Device가 독점하지 않기 위해서
		if (C == 0)// 1/5의 확률로 1초 스탑
			this_thread::sleep_for(chrono::duration<double>(1));
		lock_guard<mutex> guard(mtx);// 상호 배제
		if (Q_monitor.size() != 0) {// Queue에 남아있으면 다음 수행
			Task temp = Q_monitor.front();// Monitor Queue 맨 끝 가져오기
			cout << left << "ID : " << temp.id << " Device : " << check_state(temp) << endl;
			Q_monitor.pop();// 맨 끝 버리기
			DMA_Controller(temp);// Memory Buffer에 넣는다
		}
		else//끝나면 다음 출력
			cout << "finish all task" << endl;
	}
}
void IDE_Controller::device_mouse() {
	int mouse_size = Q_mouse.size();// Mouse Queue의 크기 계산
	for (int i = 0; i < mouse_size; i++) {
		int C = random_number() % 5;// Device가 독점하지 않기 위해서
		if (C == 0)// 1/5의 확률로 1초 스탑
			this_thread::sleep_for(chrono::duration<double>(1));
		lock_guard<mutex> guard(mtx);// 상호 배제
		if (Q_mouse.size() != 0) {// Queue에 남아있으면 다음 수행
			Task temp = Q_mouse.front();// Mouse Queue 맨 끝 가져오기
			cout << left << "ID : " << temp.id << " Device : " << check_state(temp) << endl;
			Q_mouse.pop();// 맨 끝 버리기
			DMA_Controller(temp);// Memory Buffer에 넣는다
		}
		else//끝나면 다음 출력
			cout << "finish all task" << endl;
	}
}
void IDE_Controller::device_keyboard() {
	int keyboard_size = Q_keyboard.size();// Keyboard Queue의 크기 계산
	for (int i = 0; i < keyboard_size; i++) {
		int C = random_number() % 5;// Device가 독점하지 않기 위해서
		if (C == 0)// 1/5의 확률로 1초 스탑
			this_thread::sleep_for(chrono::duration<double>(1));
		lock_guard<mutex> guard(mtx);// 상호 배제
		if (Q_keyboard.size() != 0) {// Queue에 남아있으면 다음 수행
			Task temp = Q_keyboard.front();// Keyboard Queue 맨 끝 가져오기
			cout << left << "ID : " << temp.id << " Device : " << check_state(temp) << endl;
			Q_keyboard.pop();// 맨 끝 버리기
			DMA_Controller(temp);// Memory Buffer에 넣는다
		}
		else//끝나면 다음 출력
			cout << "finish all task" << endl;
	}
}
//Device 출력(0:Disk 1:Printer 2:Monitor 3:Mouse 4:Keyboard)
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
//수행 종료된 Task를 Memory Buffer에 저장
void IDE_Controller::DMA_Controller(Task task) {
	Buffer.push(task);
}