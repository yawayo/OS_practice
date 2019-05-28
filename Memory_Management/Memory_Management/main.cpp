#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;


struct Process {
	int id;
	int size;
};
struct Memory {
	int id;
	int size;
};
void run();// 실행 함수
void init_memory();// Memory 초기화
void count_empty_size(vector<int>* size);// Memory의 빈공간 검출
void Request();// Request 함수
void init_Process(Process* pcs);// Memory에 할당할 Process 정의
void set_memory_size();// Memory 공간 체크
void size_big(Process pcs, int size);// Process 할당
void size_same(Process pcs);// Process 할당
void slide();// 빈공간 없을 시 Slide 함수
void Release();// Process 종료
void print_memory();// Memory 내용 출력

Memory memory[15];// Memory

int main() {
	run();
	return 0;
}
// 실행 함수
void run() {

	init_memory();// Memory 초기화
	print_memory();// Memory 상태 출력
	int choise;// 선택 변수

	while (1) {
		choise = 0;
		cout << "시작" << endl;
		cout << "1. Request" << endl;
		cout << "2. Release" << endl;
		cout << "3. Print Memory" << endl;
		cout << "0. End" << endl;
		cout << "---->";
		cin >> choise;

		switch (choise)
		{
		case 1:
			Request();// Request 함수
			break;
		case 2:
			Release();// Release 함수
			break;
		case 3:
			print_memory();// Memory 상태 출력
			break;
		case 0:
			return;// 종료
		default:
			cout << "잘 못 입력하였습니다." << endl << endl;
			break;
		}
		set_memory_size();// Memory 공간 체크
	}
}
// Memory 초기화
void init_memory() {
	for (int i = 0; i < 15; i++) {
		memory[i].id = 0;// 모든 Memory 공간 Empty
		memory[i].size = 15;// Empty 사이즈
	}
}
// Memory 공간 체크
void set_memory_size() {
	int count = 1;
	for (int i = 0; i < 14; i++) {
		if (memory[i].id == memory[i + 1].id)
			count++;
		else {
			for (int j = 0; j < count; j++)
				memory[i - j].size = count;
			count = 1;
		}
		if (i == 13)
			for (int j = 0; j < count; j++)
				memory[i - j + 1].size = count;
	}
}
// Memory의 빈공간 검출
void count_empty_size(vector<int>* size) {
	size->clear();
	int count = 0;
	for (int i = 0; i < 15; i++) {
		if (memory[i].id == 0)
			count++;
		else {
			if (count > 0)
				size->push_back(count);
			count = 0;
		}
		if ((i == 14) && (count > 0)) {
			size->push_back(count);
			count = 0;
		}
	}
}
// Process 할당 : Memory의 빈 공간이 모두 Process의 사이즈보다 큰 경우
void size_big(Process pcs, int size) {
	bool done = false;
	for (int i = 0; i < 15; i++) {
		if ((memory[i].size == size) && (memory[i].id == 0)) {
			for (int j = 0; j < pcs.size; j++)
				memory[i + j].id = pcs.id;
			done = true;
		}
		if (done)
			break;
	}
	set_memory_size();
}
// Process 할당 : Memory의 빈 공간이 Process의 사이즈와 같은 경우
void size_same(Process pcs) {
	bool done = false;
	for (int i = 0; i < 15; i++) {
		if ((memory[i].size == pcs.size) && (memory[i].id == 0)) {
			for (int j = 0; j < pcs.size; j++)
				memory[i + j].id = pcs.id;
			done = true;
		}
		if (done)
			break;
	}
	set_memory_size();
}
// 빈공간의 총 크기가 Process 사이즈보다 크거가 같지만 각각의 빈공간은 모두 Process 사이즈보다 작은 경우 Slide
void slide() {
	vector<int> size;
	count_empty_size(&size);
	while (!((size.size() == 1) && (memory[14].id == 0))) {
		count_empty_size(&size);
		for (int i = 14; i > 0; i--) {
			if ((memory[i].id != 0) && (memory[i - 1].id == 0)) {
				memory[i - 1].id = memory[i].id;
				memory[i].id = 0;
			}
		}
	}
}
//Request 함수
void Request() {
	int sum = 0; // 빈칸 총 크기
	vector<int> size;
	Process pcs;
	bool exist = false;
	init_Process(&pcs);
	for (int i = 0; i < 15; i++)
		if (memory[i].id == pcs.id)
			exist = true;

	if (!exist) {
		count_empty_size(&size);
		sort(size.begin(), size.end());
		cout << "size.size() : " << size.size() << endl;
		for (int i = 0; i < size.size(); i++) {
			cout << "size[i] : " << size[i] << " ";
			sum += size[i];
		}
		cout << endl;

		// 빈칸의 크기가 Process 크기와 같은 부분이 있으면 그 부분에 Process 삽입
		// 없으면 Process 크기보다 큰 빈칸중에서 가장 작은 빈칸에 삽입
		// 빈칸은 있지만 모든 빈칸이 다 Process 크기보다 작을경우 프로세스들을 한쪽으로 모아준 후 빈칸이 생기면 삽입
		// 빈칸 없으면 꽉 찼다고 출력
		bool done = false;
		if (sum >= pcs.size) {
			for (int i = 0; i < size.size(); i++) {// 빈칸 개수 각각 체크
				for (int j = 0; j < 15; j++) {
					if (!done) {
						if (size[i] == pcs.size) {
							size_same(pcs);
							done = true;
						}
						else if (size[i] > pcs.size) {
							size_big(pcs, size[i]);
							done = true;
						}
					}
				}
			}
			if (!done) {
				slide();
				count_empty_size(&size);
				for (int j = 0; j < 15; j++) {
					if (size[0] == pcs.size) {
						size_same(pcs);
						done = true;
						break;
					}
					else if (size[0] > pcs.size) {
						size_big(pcs, size[0]);
						done = true;
						break;
					}
				}
			}
		}
		else {
			if (sum == 0)
				cout << "Memory가 꽉 찼습니다." << endl;
			else
				cout << "Memory에 빈 공간이 부족합니다." << endl;
		}
	}
	else
		cout << "이미 있는 Process 입니다." << endl;
	set_memory_size();
	print_memory();// Memory 상태 출력
}
// Memory에 할당할 Process 정의
void init_Process(Process* pcs) {
	cout << "ID : ";
	cin >> pcs->id;
	cout << "Size : ";
	cin >> pcs->size;
}
// Process 종료
void Release() {
	int id;
	cout << "종료할 Process id : ";
	cin >> id;
	bool exist = false;
	for (int i = 0; i < 15; i++)
		if (memory[i].id == id)
			exist = true;

	if (exist) {
		for (int i = 0; i < 15; i++) // 입력한 ID와 같은 ID의 Process 종료
			if (memory[i].id == id)
				memory[i].id = 0;
	}
	else
		cout << "해당 Process가 존재하지 않습니다." << endl;

	print_memory();// Memory 상태 출력
}
// Memory 상태 출력
void print_memory() {
	set_memory_size();// Memory 공간 체크

	cout << "index : ";// index 출력
	for (int i = 0; i < 15; i++)
		cout << setw(2) << i + 1 << "  ";
	cout << endl;

	cout << "ID    : ";// Process ID 출력
	for (int i = 0; i < 15; i++) {
		if (memory[i].id != 0)
			cout << setw(2) << memory[i].id << "  ";
		else
			cout << setw(2) << "-" << "  ";
	}cout << endl;

	cout << "size  : ";// 그 공간의 사이즈 출력
	for (int i = 0; i < 15; i++)
		cout << setw(2) << memory[i].size << "  ";
	cout << endl;
}