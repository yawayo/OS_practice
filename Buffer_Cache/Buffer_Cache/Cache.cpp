#include "Cache.h"
#include <ctime>

using namespace std;

Cache::Cache() {//�ʱ�ȭ
	device_0.MakeEmpty();
	device_1.MakeEmpty();
	device_2.MakeEmpty();
	device_3.MakeEmpty();
	device_4.MakeEmpty();
	FreeList.MakeEmpty();
	Command = -1;
	//0~4�� device�� ���� 3~10���� Buffer�� �ʱ�ȭ
	int A[10];
	int data = 0;
	srand(time(NULL));
	for (int i = 0; i < 5; i++) {
		for (int x = 0; x < 10; x++)
			A[x] = 0;

		int num = rand() % 8 + 3;

		for (int x = 0; x < num; x++) {
			data = rand() % 100 + 1;
			if (data % 5 == i)
				A[x] = data;
			else
				x--;

			for (int y = 0; y < x; y++) {
				if (A[x] == A[y]) {
					x--; break;
				}
			}
		}
		for (int x = 0; x < num; x++) {
			BufferData bf;
			bf.Setinfo(A[x], i);
			int state = 0;
			state = rand() % 4;
			bf.SetState(state);
			if (i == 0)device_0.EnQueue(bf);
			else if (i == 1)device_1.EnQueue(bf);
			else if (i == 2)device_2.EnQueue(bf);
			else if (i == 3)device_3.EnQueue(bf);
			else if (i == 4)device_4.EnQueue(bf);
			if (state == 0)
				FreeList.Add(bf);
		}
	}
	Display();
}
Cache::~Cache() {
	device_0.MakeEmpty();
	device_1.MakeEmpty();
	device_2.MakeEmpty();
	device_3.MakeEmpty();
	device_4.MakeEmpty();
	FreeList.MakeEmpty();
}

void Cache::Run() {
	while (1) {
		Command = GetCommand();

		switch (Command) {
		case 1://���� ã��
			SearchBuffer();
			break;
		case 2://��� ���� �����ֱ�
			Display();
			break;
		case 0:
			cout << "����" << endl;
			return;
		default:
			cout << "�� �� �Է��ϼ̽��ϴ�." << endl;
			break;

		}
	}
}
int Cache::GetCommand() {
	int cmd;
	cout << endl;
	cout << "\t 1. ã�� ���۸� �Է��ϼ���" << endl;
	cout << "\t 2. ��� ���� ����" << endl;
	cout << "\t 0. ����" << endl;
	cout << "\t ---->";
	cin >> cmd;
	cout << endl;

	return cmd;
}
int Cache::SearchBuffer() {
	BufferData bf_q;
	BufferData bf_s;
	int num;
	cout << "ã�� ���۸� �Է��ϼ��� : ";
	cin >> num;
	//Device ���� �˻�
	if (num % 5 == 0) {//0�� Device
		device_0.ResetList();
		for (int i = 0; i < device_0.GetLength(); i++) {
			device_0.GetNextItem(bf_q);//ó������ �ϳ��� �˻�
			if (bf_q.Getid() == num) {//ť���� ã��
				if (bf_q.GetState() == 1) {//Busy ����
					//�ó�����5 
					cout << "�ó����� 5" << endl;
					//ã�� ������ ���¸� ���������� Free���·� �ٲ��ش�
					device_0.DeleteItem(bf_q);
					bf_s.Setinfo(num, num % 5);
					bf_s.SetState(0);//Free�� ����
					device_0.EnQueue(bf_s);
					return 0;
				}
				else if(bf_q.GetState() == 0) {//Free����
					//�ó�����1
					cout << "�ó����� 1" << endl;
					//ã�� ������ ���¸� Busy�� �ٲ��ְ� Free List���� �����
					device_0.DeleteItem(bf_q);
					bf_s.Setinfo(num, num % 5);
					bf_s.SetState(1);//busy�� ����
					device_0.EnQueue(bf_s);
					FreeList.Delete(bf_s);
					return 0;
				}
			}
		}
		if (!FreeList.GetLength()) {//ã�� ���۰� ť�� ���� Free List�� ����ִ�
			//�ó�����4
			cout << "�ó����� 4" << endl;
			//�ٽý���
			return 0;
		}
		FreeList.ResetList();
		while (1) {//�ó����� 2, 3
			int cnt = 0;
			FreeList.GetNextItem(bf_q);//�տ������� �ϳ��� �˻�
			if (bf_q.GetState() == 0) {//�˻��� Buffer�� ���°� Free�� ���
				FreeList.Delete(bf_q);//Buffer�� ������ ����� �˻��Ϸ��� ���ο� Buffer �߰�
				bf_s.Setinfo(num, num % 5);
				bf_s.SetState(1);
				device_0.EnQueue(bf_s);
				if (!cnt)
					cout << "�ó����� 2" << endl;
				else
					cout << "�ó����� 3" << endl;
				return 0;
			}
			else {//�˻��� Buffer�� ���°� Free�� �ƴ� ���
				//Buffer�� ���¸� Write�� ������ְ� Free List���� �����Ѵ�
				device_0.DeleteItem(bf_q);
				bf_s.Setinfo(num, num % 5);
				bf_s.SetState(3);//write�� ����
				device_0.EnQueue(bf_s);
				FreeList.Delete(bf_s);
				cnt++;
			}
		}

		return 0;
	}
	else if (num % 5 == 1) {//1�� Device
		device_1.ResetList();
		for (int i = 0; i < device_1.GetLength(); i++) {
			device_1.GetNextItem(bf_q);//ó������ �ϳ��� �˻�
			if (bf_q.Getid() == num) {//ť���� ã��
				if (bf_q.GetState() == 1) {//Busy ����
					//�ó�����5 
					cout << "�ó����� 5" << endl;
					//ã�� ������ ���¸� ���������� Free���·� �ٲ��ش�
					device_1.DeleteItem(bf_q);
					bf_s.Setinfo(num, num % 5);
					bf_s.SetState(0);//Free�� ����
					device_1.EnQueue(bf_s);
					return 0;
				}
				else if (bf_q.GetState() == 0) {//Free����
					//�ó�����1
					cout << "�ó����� 1" << endl;
					//ã�� ������ ���¸� Busy�� �ٲ��ְ� Free List���� �����
					device_1.DeleteItem(bf_q);
					bf_s.Setinfo(num, num % 5);
					bf_s.SetState(1);//busy�� ����
					device_1.EnQueue(bf_s);
					FreeList.Delete(bf_s);
					return 0;
				}
			}
		}
		if (!FreeList.GetLength()) {//ã�� ���۰� ť�� ���� Free List�� ����ִ�
			//�ó�����4
			cout << "�ó����� 4" << endl;
			//�ٽý���
			return 0;
		}
		FreeList.ResetList();
		while (1) {//�ó����� 2, 3
			int cnt = 0;
			FreeList.GetNextItem(bf_q);//�տ������� �ϳ��� �˻�
			if (bf_q.GetState() == 0) {//�˻��� Buffer�� ���°� Free�� ���
				FreeList.Delete(bf_q);//Buffer�� ������ ����� �˻��Ϸ��� ���ο� Buffer �߰�
				bf_s.Setinfo(num, num % 5);
				bf_s.SetState(1);
				device_1.EnQueue(bf_s);
				if (!cnt)
					cout << "�ó����� 2" << endl;
				else
					cout << "�ó����� 3" << endl;
				return 0;
			}
			else {//�˻��� Buffer�� ���°� Free�� �ƴ� ���
				//Buffer�� ���¸� Write�� ������ְ� Free List���� �����Ѵ�
				device_1.DeleteItem(bf_q);
				bf_s.Setinfo(num, num % 5);
				bf_s.SetState(3);//write�� ����
				device_1.EnQueue(bf_s);
				FreeList.Delete(bf_s);
				cnt++;
			}
		}

		return 0;
	}
	else if (num % 5 == 2) {//2�� Device
	device_2.ResetList();
	for (int i = 0; i < device_2.GetLength(); i++) {
		device_2.GetNextItem(bf_q);//ó������ �ϳ��� �˻�
		if (bf_q.Getid() == num) {//ť���� ã��
			if (bf_q.GetState() == 1) {//Busy ����
				//�ó�����5 
				cout << "�ó����� 5" << endl;
				//ã�� ������ ���¸� ���������� Free���·� �ٲ��ش�
				device_2.DeleteItem(bf_q);
				bf_s.Setinfo(num, num % 5);
				bf_s.SetState(0);//Free�� ����
				device_2.EnQueue(bf_s);
				return 0;
			}
			else if (bf_q.GetState() == 0) {//Free����
				//�ó�����1
				cout << "�ó����� 1" << endl;
				//ã�� ������ ���¸� Busy�� �ٲ��ְ� Free List���� �����
				device_2.DeleteItem(bf_q);
				bf_s.Setinfo(num, num % 5);
				bf_s.SetState(1);//busy�� ����
				device_2.EnQueue(bf_s);
				FreeList.Delete(bf_s);
				return 0;
			}
		}
	}
	if (!FreeList.GetLength()) {//ã�� ���۰� ť�� ���� Free List�� ����ִ�
		//�ó�����4
		cout << "�ó����� 4" << endl;
		//�ٽý���
		return 0;
	}
	FreeList.ResetList();
	while (1) {//�ó����� 2, 3
		int cnt = 0;
		FreeList.GetNextItem(bf_q);//�տ������� �ϳ��� �˻�
		if (bf_q.GetState() == 0) {//�˻��� Buffer�� ���°� Free�� ���
			FreeList.Delete(bf_q);//Buffer�� ������ ����� �˻��Ϸ��� ���ο� Buffer �߰�
			bf_s.Setinfo(num, num % 5);
			bf_s.SetState(1);
			device_2.EnQueue(bf_s);
			if (!cnt)
				cout << "�ó����� 2" << endl;
			else
				cout << "�ó����� 3" << endl;
			return 0;
		}
		else {//�˻��� Buffer�� ���°� Free�� �ƴ� ���
			//Buffer�� ���¸� Write�� ������ְ� Free List���� �����Ѵ�
			device_2.DeleteItem(bf_q);
			bf_s.Setinfo(num, num % 5);
			bf_s.SetState(3);//write�� ����
			device_2.EnQueue(bf_s);
			FreeList.Delete(bf_s);
			cnt++;
		}
	}

	return 0;
	}
	else if (num % 5 == 3) {//3�� Device
	device_3.ResetList();
	for (int i = 0; i < device_3.GetLength(); i++) {
		device_3.GetNextItem(bf_q);//ó������ �ϳ��� �˻�
		if (bf_q.Getid() == num) {//ť���� ã��
			if (bf_q.GetState() == 1) {//Busy ����
				//�ó�����5 
				cout << "�ó����� 5" << endl;
				//ã�� ������ ���¸� ���������� Free���·� �ٲ��ش�
				device_3.DeleteItem(bf_q);
				bf_s.Setinfo(num, num % 5);
				bf_s.SetState(0);//Free�� ����
				device_3.EnQueue(bf_s);
				return 0;
			}
			else if (bf_q.GetState() == 0) {//Free����
				//�ó�����1
				cout << "�ó����� 1" << endl;
				//ã�� ������ ���¸� Busy�� �ٲ��ְ� Free List���� �����
				device_3.DeleteItem(bf_q);
				bf_s.Setinfo(num, num % 5);
				bf_s.SetState(1);//busy�� ����
				device_3.EnQueue(bf_s);
				FreeList.Delete(bf_s);
				return 0;
			}
		}
	}
	if (!FreeList.GetLength()) {//ã�� ���۰� ť�� ���� Free List�� ����ִ�
		//�ó�����4
		cout << "�ó����� 4" << endl;
		//�ٽý���
		return 0;
	}
	FreeList.ResetList();
	while (1) {//�ó����� 2, 3
		int cnt = 0;
		FreeList.GetNextItem(bf_q);//�տ������� �ϳ��� �˻�
		if (bf_q.GetState() == 0) {//�˻��� Buffer�� ���°� Free�� ���
			FreeList.Delete(bf_q);//Buffer�� ������ ����� �˻��Ϸ��� ���ο� Buffer �߰�
			bf_s.Setinfo(num, num % 5);
			bf_s.SetState(1);
			device_3.EnQueue(bf_s);
			if (!cnt)
				cout << "�ó����� 2" << endl;
			else
				cout << "�ó����� 3" << endl;
			return 0;
		}
		else {//�˻��� Buffer�� ���°� Free�� �ƴ� ���
			//Buffer�� ���¸� Write�� ������ְ� Free List���� �����Ѵ�
			device_3.DeleteItem(bf_q);
			bf_s.Setinfo(num, num % 5);
			bf_s.SetState(3);//write�� ����
			device_3.EnQueue(bf_s);
			FreeList.Delete(bf_s);
			cnt++;
		}
	}

	return 0;
	}
	else if (num % 5 == 4) {//4�� Device
		device_4.ResetList();
		for (int i = 0; i < device_4.GetLength(); i++) {
			device_4.GetNextItem(bf_q);//ó������ �ϳ��� �˻�
			if (bf_q.Getid() == num) {//ť���� ã��
				if (bf_q.GetState() == 1) {//Busy ����
					//�ó�����5 
					cout << "�ó����� 5" << endl;
					//ã�� ������ ���¸� ���������� Free���·� �ٲ��ش�
					device_4.DeleteItem(bf_q);
					bf_s.Setinfo(num, num % 5);
					bf_s.SetState(0);//Free�� ����
					device_4.EnQueue(bf_s);
					return 0;
				}
				else if (bf_q.GetState() == 0) {//Free����
					//�ó�����1
					cout << "�ó����� 1" << endl;
					//ã�� ������ ���¸� Busy�� �ٲ��ְ� Free List���� �����
					device_4.DeleteItem(bf_q);
					bf_s.Setinfo(num, num % 5);
					bf_s.SetState(1);//busy�� ����
					device_4.EnQueue(bf_s);
					FreeList.Delete(bf_s);
					return 0;
				}
			}
		}
		if (!FreeList.GetLength()) {//ã�� ���۰� ť�� ���� Free List�� ����ִ�
			//�ó�����4
			cout << "�ó����� 4" << endl;
			//�ٽý���
			return 0;
		}
		FreeList.ResetList();
		while (1) {//�ó����� 2, 3
			int cnt = 0;
			FreeList.GetNextItem(bf_q);//�տ������� �ϳ��� �˻�
			if (bf_q.GetState() == 0) {//�˻��� Buffer�� ���°� Free�� ���
				FreeList.Delete(bf_q);//Buffer�� ������ ����� �˻��Ϸ��� ���ο� Buffer �߰�
				bf_s.Setinfo(num, num % 5);
				bf_s.SetState(1);
				device_4.EnQueue(bf_s);
				if (!cnt)
					cout << "�ó����� 2" << endl;
				else
					cout << "�ó����� 3" << endl;
				return 0;
			}
			else {//�˻��� Buffer�� ���°� Free�� �ƴ� ���
				//Buffer�� ���¸� Write�� ������ְ� Free List���� �����Ѵ�
				device_4.DeleteItem(bf_q);
				bf_s.Setinfo(num, num % 5);
				bf_s.SetState(3);//write�� ����
				device_4.EnQueue(bf_s);
				FreeList.Delete(bf_s);
				cnt++;
			}
		}

		return 0;
	}
	return 0;
}
int Cache::Display() {
	BufferData bf;

	//0�� Device ���
	cout << "\n\t\tdevice 0\n" << endl;
	device_0.ResetList();
	for (int i = 0; i < device_0.GetLength(); i++) {
		device_0.GetNextItem(bf);
		bf.DisplayAll();
	}
	//1�� Device ���
	cout << "\n\t\tdevice 1\n" << endl;
	device_1.ResetList();
	for (int i = 0; i < device_1.GetLength(); i++) {
		device_1.GetNextItem(bf);
		bf.DisplayAll();
	}
	//2�� Device ���
	cout << "\n\t\tdevice 2\n" << endl;
	device_2.ResetList();
	for (int i = 0; i < device_2.GetLength(); i++) {
		device_2.GetNextItem(bf);
		bf.DisplayAll();
	}
	//3�� Device ���
	cout << "\n\t\tdevice 3\n" << endl;
	device_3.ResetList();
	for (int i = 0; i < device_3.GetLength(); i++) {
		device_3.GetNextItem(bf);
		bf.DisplayAll();
	}
	//4�� Device ���
	cout << "\n\t\tdevice 4\n" << endl;
	device_4.ResetList();
	for (int i = 0; i < device_4.GetLength(); i++) {
		device_4.GetNextItem(bf);
		bf.DisplayAll();
	}
	//Free List ���
	if (FreeList.GetLength() != 0) {
		cout << "\n\t\tFree List\n" << endl;

		FreeList.ResetList();
		for (int i = 0; i < FreeList.GetLength(); i++) {
			FreeList.GetNextItem(bf);
			bf.DisplayAll();
		}
		return 1;
	}
	else {
		cout << "\n\t\t������ϴ�.\n" << endl;
		return 0;
	}

}