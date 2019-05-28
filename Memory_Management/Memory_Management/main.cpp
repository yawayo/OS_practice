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
void run();// ���� �Լ�
void init_memory();// Memory �ʱ�ȭ
void count_empty_size(vector<int>* size);// Memory�� ����� ����
void Request();// Request �Լ�
void init_Process(Process* pcs);// Memory�� �Ҵ��� Process ����
void set_memory_size();// Memory ���� üũ
void size_big(Process pcs, int size);// Process �Ҵ�
void size_same(Process pcs);// Process �Ҵ�
void slide();// ����� ���� �� Slide �Լ�
void Release();// Process ����
void print_memory();// Memory ���� ���

Memory memory[15];// Memory

int main() {
	run();
	return 0;
}
// ���� �Լ�
void run() {

	init_memory();// Memory �ʱ�ȭ
	print_memory();// Memory ���� ���
	int choise;// ���� ����

	while (1) {
		choise = 0;
		cout << "����" << endl;
		cout << "1. Request" << endl;
		cout << "2. Release" << endl;
		cout << "3. Print Memory" << endl;
		cout << "0. End" << endl;
		cout << "---->";
		cin >> choise;

		switch (choise)
		{
		case 1:
			Request();// Request �Լ�
			break;
		case 2:
			Release();// Release �Լ�
			break;
		case 3:
			print_memory();// Memory ���� ���
			break;
		case 0:
			return;// ����
		default:
			cout << "�� �� �Է��Ͽ����ϴ�." << endl << endl;
			break;
		}
		set_memory_size();// Memory ���� üũ
	}
}
// Memory �ʱ�ȭ
void init_memory() {
	for (int i = 0; i < 15; i++) {
		memory[i].id = 0;// ��� Memory ���� Empty
		memory[i].size = 15;// Empty ������
	}
}
// Memory ���� üũ
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
// Memory�� ����� ����
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
// Process �Ҵ� : Memory�� �� ������ ��� Process�� ������� ū ���
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
// Process �Ҵ� : Memory�� �� ������ Process�� ������� ���� ���
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
// ������� �� ũ�Ⱑ Process ������� ũ�Ű� ������ ������ ������� ��� Process ������� ���� ��� Slide
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
//Request �Լ�
void Request() {
	int sum = 0; // ��ĭ �� ũ��
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

		// ��ĭ�� ũ�Ⱑ Process ũ��� ���� �κ��� ������ �� �κп� Process ����
		// ������ Process ũ�⺸�� ū ��ĭ�߿��� ���� ���� ��ĭ�� ����
		// ��ĭ�� ������ ��� ��ĭ�� �� Process ũ�⺸�� ������� ���μ������� �������� ����� �� ��ĭ�� ����� ����
		// ��ĭ ������ �� á�ٰ� ���
		bool done = false;
		if (sum >= pcs.size) {
			for (int i = 0; i < size.size(); i++) {// ��ĭ ���� ���� üũ
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
				cout << "Memory�� �� á���ϴ�." << endl;
			else
				cout << "Memory�� �� ������ �����մϴ�." << endl;
		}
	}
	else
		cout << "�̹� �ִ� Process �Դϴ�." << endl;
	set_memory_size();
	print_memory();// Memory ���� ���
}
// Memory�� �Ҵ��� Process ����
void init_Process(Process* pcs) {
	cout << "ID : ";
	cin >> pcs->id;
	cout << "Size : ";
	cin >> pcs->size;
}
// Process ����
void Release() {
	int id;
	cout << "������ Process id : ";
	cin >> id;
	bool exist = false;
	for (int i = 0; i < 15; i++)
		if (memory[i].id == id)
			exist = true;

	if (exist) {
		for (int i = 0; i < 15; i++) // �Է��� ID�� ���� ID�� Process ����
			if (memory[i].id == id)
				memory[i].id = 0;
	}
	else
		cout << "�ش� Process�� �������� �ʽ��ϴ�." << endl;

	print_memory();// Memory ���� ���
}
// Memory ���� ���
void print_memory() {
	set_memory_size();// Memory ���� üũ

	cout << "index : ";// index ���
	for (int i = 0; i < 15; i++)
		cout << setw(2) << i + 1 << "  ";
	cout << endl;

	cout << "ID    : ";// Process ID ���
	for (int i = 0; i < 15; i++) {
		if (memory[i].id != 0)
			cout << setw(2) << memory[i].id << "  ";
		else
			cout << setw(2) << "-" << "  ";
	}cout << endl;

	cout << "size  : ";// �� ������ ������ ���
	for (int i = 0; i < 15; i++)
		cout << setw(2) << memory[i].size << "  ";
	cout << endl;
}