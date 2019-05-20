#include "Cache.h"
#include <ctime>

using namespace std;

Cache::Cache() {//초기화
	device_0.MakeEmpty();
	device_1.MakeEmpty();
	device_2.MakeEmpty();
	device_3.MakeEmpty();
	device_4.MakeEmpty();
	FreeList.MakeEmpty();
	Command = -1;
	//0~4번 device에 각각 3~10개의 Buffer를 초기화
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
		case 1://버퍼 찾기
			SearchBuffer();
			break;
		case 2://모든 버퍼 보여주기
			Display();
			break;
		case 0:
			cout << "종료" << endl;
			return;
		default:
			cout << "잘 못 입력하셨습니다." << endl;
			break;

		}
	}
}
int Cache::GetCommand() {
	int cmd;
	cout << endl;
	cout << "\t 1. 찾을 버퍼를 입력하세요" << endl;
	cout << "\t 2. 모든 버퍼 보기" << endl;
	cout << "\t 0. 종료" << endl;
	cout << "\t ---->";
	cin >> cmd;
	cout << endl;

	return cmd;
}
int Cache::SearchBuffer() {
	BufferData bf_q;
	BufferData bf_s;
	int num;
	cout << "찾을 버퍼를 입력하세요 : ";
	cin >> num;
	//Device 별로 검색
	if (num % 5 == 0) {//0번 Device
		device_0.ResetList();
		for (int i = 0; i < device_0.GetLength(); i++) {
			device_0.GetNextItem(bf_q);//처음부터 하나씩 검색
			if (bf_q.Getid() == num) {//큐에서 찾음
				if (bf_q.GetState() == 1) {//Busy 상태
					//시나리오5 
					cout << "시나리오 5" << endl;
					//찾는 버퍼의 상태를 인위적으로 Free상태로 바꿔준다
					device_0.DeleteItem(bf_q);
					bf_s.Setinfo(num, num % 5);
					bf_s.SetState(0);//Free로 변경
					device_0.EnQueue(bf_s);
					return 0;
				}
				else if(bf_q.GetState() == 0) {//Free상태
					//시나리오1
					cout << "시나리오 1" << endl;
					//찾는 버퍼의 상태를 Busy로 바꿔주고 Free List에서 지운다
					device_0.DeleteItem(bf_q);
					bf_s.Setinfo(num, num % 5);
					bf_s.SetState(1);//busy로 변경
					device_0.EnQueue(bf_s);
					FreeList.Delete(bf_s);
					return 0;
				}
			}
		}
		if (!FreeList.GetLength()) {//찾는 버퍼가 큐에 없고 Free List가 비어있다
			//시나리오4
			cout << "시나리오 4" << endl;
			//다시시작
			return 0;
		}
		FreeList.ResetList();
		while (1) {//시나리오 2, 3
			int cnt = 0;
			FreeList.GetNextItem(bf_q);//앞에서부터 하나씩 검색
			if (bf_q.GetState() == 0) {//검색한 Buffer의 상태가 Free인 경우
				FreeList.Delete(bf_q);//Buffer를 완전히 지우고 검색하려던 새로운 Buffer 추가
				bf_s.Setinfo(num, num % 5);
				bf_s.SetState(1);
				device_0.EnQueue(bf_s);
				if (!cnt)
					cout << "시나리오 2" << endl;
				else
					cout << "시나리오 3" << endl;
				return 0;
			}
			else {//검색한 Buffer의 상태가 Free가 아닌 경우
				//Buffer의 상태를 Write로 만들어주고 Free List에서 삭제한다
				device_0.DeleteItem(bf_q);
				bf_s.Setinfo(num, num % 5);
				bf_s.SetState(3);//write로 변경
				device_0.EnQueue(bf_s);
				FreeList.Delete(bf_s);
				cnt++;
			}
		}

		return 0;
	}
	else if (num % 5 == 1) {//1번 Device
		device_1.ResetList();
		for (int i = 0; i < device_1.GetLength(); i++) {
			device_1.GetNextItem(bf_q);//처음부터 하나씩 검색
			if (bf_q.Getid() == num) {//큐에서 찾음
				if (bf_q.GetState() == 1) {//Busy 상태
					//시나리오5 
					cout << "시나리오 5" << endl;
					//찾는 버퍼의 상태를 인위적으로 Free상태로 바꿔준다
					device_1.DeleteItem(bf_q);
					bf_s.Setinfo(num, num % 5);
					bf_s.SetState(0);//Free로 변경
					device_1.EnQueue(bf_s);
					return 0;
				}
				else if (bf_q.GetState() == 0) {//Free상태
					//시나리오1
					cout << "시나리오 1" << endl;
					//찾는 버퍼의 상태를 Busy로 바꿔주고 Free List에서 지운다
					device_1.DeleteItem(bf_q);
					bf_s.Setinfo(num, num % 5);
					bf_s.SetState(1);//busy로 변경
					device_1.EnQueue(bf_s);
					FreeList.Delete(bf_s);
					return 0;
				}
			}
		}
		if (!FreeList.GetLength()) {//찾는 버퍼가 큐에 없고 Free List가 비어있다
			//시나리오4
			cout << "시나리오 4" << endl;
			//다시시작
			return 0;
		}
		FreeList.ResetList();
		while (1) {//시나리오 2, 3
			int cnt = 0;
			FreeList.GetNextItem(bf_q);//앞에서부터 하나씩 검색
			if (bf_q.GetState() == 0) {//검색한 Buffer의 상태가 Free인 경우
				FreeList.Delete(bf_q);//Buffer를 완전히 지우고 검색하려던 새로운 Buffer 추가
				bf_s.Setinfo(num, num % 5);
				bf_s.SetState(1);
				device_1.EnQueue(bf_s);
				if (!cnt)
					cout << "시나리오 2" << endl;
				else
					cout << "시나리오 3" << endl;
				return 0;
			}
			else {//검색한 Buffer의 상태가 Free가 아닌 경우
				//Buffer의 상태를 Write로 만들어주고 Free List에서 삭제한다
				device_1.DeleteItem(bf_q);
				bf_s.Setinfo(num, num % 5);
				bf_s.SetState(3);//write로 변경
				device_1.EnQueue(bf_s);
				FreeList.Delete(bf_s);
				cnt++;
			}
		}

		return 0;
	}
	else if (num % 5 == 2) {//2번 Device
	device_2.ResetList();
	for (int i = 0; i < device_2.GetLength(); i++) {
		device_2.GetNextItem(bf_q);//처음부터 하나씩 검색
		if (bf_q.Getid() == num) {//큐에서 찾음
			if (bf_q.GetState() == 1) {//Busy 상태
				//시나리오5 
				cout << "시나리오 5" << endl;
				//찾는 버퍼의 상태를 인위적으로 Free상태로 바꿔준다
				device_2.DeleteItem(bf_q);
				bf_s.Setinfo(num, num % 5);
				bf_s.SetState(0);//Free로 변경
				device_2.EnQueue(bf_s);
				return 0;
			}
			else if (bf_q.GetState() == 0) {//Free상태
				//시나리오1
				cout << "시나리오 1" << endl;
				//찾는 버퍼의 상태를 Busy로 바꿔주고 Free List에서 지운다
				device_2.DeleteItem(bf_q);
				bf_s.Setinfo(num, num % 5);
				bf_s.SetState(1);//busy로 변경
				device_2.EnQueue(bf_s);
				FreeList.Delete(bf_s);
				return 0;
			}
		}
	}
	if (!FreeList.GetLength()) {//찾는 버퍼가 큐에 없고 Free List가 비어있다
		//시나리오4
		cout << "시나리오 4" << endl;
		//다시시작
		return 0;
	}
	FreeList.ResetList();
	while (1) {//시나리오 2, 3
		int cnt = 0;
		FreeList.GetNextItem(bf_q);//앞에서부터 하나씩 검색
		if (bf_q.GetState() == 0) {//검색한 Buffer의 상태가 Free인 경우
			FreeList.Delete(bf_q);//Buffer를 완전히 지우고 검색하려던 새로운 Buffer 추가
			bf_s.Setinfo(num, num % 5);
			bf_s.SetState(1);
			device_2.EnQueue(bf_s);
			if (!cnt)
				cout << "시나리오 2" << endl;
			else
				cout << "시나리오 3" << endl;
			return 0;
		}
		else {//검색한 Buffer의 상태가 Free가 아닌 경우
			//Buffer의 상태를 Write로 만들어주고 Free List에서 삭제한다
			device_2.DeleteItem(bf_q);
			bf_s.Setinfo(num, num % 5);
			bf_s.SetState(3);//write로 변경
			device_2.EnQueue(bf_s);
			FreeList.Delete(bf_s);
			cnt++;
		}
	}

	return 0;
	}
	else if (num % 5 == 3) {//3번 Device
	device_3.ResetList();
	for (int i = 0; i < device_3.GetLength(); i++) {
		device_3.GetNextItem(bf_q);//처음부터 하나씩 검색
		if (bf_q.Getid() == num) {//큐에서 찾음
			if (bf_q.GetState() == 1) {//Busy 상태
				//시나리오5 
				cout << "시나리오 5" << endl;
				//찾는 버퍼의 상태를 인위적으로 Free상태로 바꿔준다
				device_3.DeleteItem(bf_q);
				bf_s.Setinfo(num, num % 5);
				bf_s.SetState(0);//Free로 변경
				device_3.EnQueue(bf_s);
				return 0;
			}
			else if (bf_q.GetState() == 0) {//Free상태
				//시나리오1
				cout << "시나리오 1" << endl;
				//찾는 버퍼의 상태를 Busy로 바꿔주고 Free List에서 지운다
				device_3.DeleteItem(bf_q);
				bf_s.Setinfo(num, num % 5);
				bf_s.SetState(1);//busy로 변경
				device_3.EnQueue(bf_s);
				FreeList.Delete(bf_s);
				return 0;
			}
		}
	}
	if (!FreeList.GetLength()) {//찾는 버퍼가 큐에 없고 Free List가 비어있다
		//시나리오4
		cout << "시나리오 4" << endl;
		//다시시작
		return 0;
	}
	FreeList.ResetList();
	while (1) {//시나리오 2, 3
		int cnt = 0;
		FreeList.GetNextItem(bf_q);//앞에서부터 하나씩 검색
		if (bf_q.GetState() == 0) {//검색한 Buffer의 상태가 Free인 경우
			FreeList.Delete(bf_q);//Buffer를 완전히 지우고 검색하려던 새로운 Buffer 추가
			bf_s.Setinfo(num, num % 5);
			bf_s.SetState(1);
			device_3.EnQueue(bf_s);
			if (!cnt)
				cout << "시나리오 2" << endl;
			else
				cout << "시나리오 3" << endl;
			return 0;
		}
		else {//검색한 Buffer의 상태가 Free가 아닌 경우
			//Buffer의 상태를 Write로 만들어주고 Free List에서 삭제한다
			device_3.DeleteItem(bf_q);
			bf_s.Setinfo(num, num % 5);
			bf_s.SetState(3);//write로 변경
			device_3.EnQueue(bf_s);
			FreeList.Delete(bf_s);
			cnt++;
		}
	}

	return 0;
	}
	else if (num % 5 == 4) {//4번 Device
		device_4.ResetList();
		for (int i = 0; i < device_4.GetLength(); i++) {
			device_4.GetNextItem(bf_q);//처음부터 하나씩 검색
			if (bf_q.Getid() == num) {//큐에서 찾음
				if (bf_q.GetState() == 1) {//Busy 상태
					//시나리오5 
					cout << "시나리오 5" << endl;
					//찾는 버퍼의 상태를 인위적으로 Free상태로 바꿔준다
					device_4.DeleteItem(bf_q);
					bf_s.Setinfo(num, num % 5);
					bf_s.SetState(0);//Free로 변경
					device_4.EnQueue(bf_s);
					return 0;
				}
				else if (bf_q.GetState() == 0) {//Free상태
					//시나리오1
					cout << "시나리오 1" << endl;
					//찾는 버퍼의 상태를 Busy로 바꿔주고 Free List에서 지운다
					device_4.DeleteItem(bf_q);
					bf_s.Setinfo(num, num % 5);
					bf_s.SetState(1);//busy로 변경
					device_4.EnQueue(bf_s);
					FreeList.Delete(bf_s);
					return 0;
				}
			}
		}
		if (!FreeList.GetLength()) {//찾는 버퍼가 큐에 없고 Free List가 비어있다
			//시나리오4
			cout << "시나리오 4" << endl;
			//다시시작
			return 0;
		}
		FreeList.ResetList();
		while (1) {//시나리오 2, 3
			int cnt = 0;
			FreeList.GetNextItem(bf_q);//앞에서부터 하나씩 검색
			if (bf_q.GetState() == 0) {//검색한 Buffer의 상태가 Free인 경우
				FreeList.Delete(bf_q);//Buffer를 완전히 지우고 검색하려던 새로운 Buffer 추가
				bf_s.Setinfo(num, num % 5);
				bf_s.SetState(1);
				device_4.EnQueue(bf_s);
				if (!cnt)
					cout << "시나리오 2" << endl;
				else
					cout << "시나리오 3" << endl;
				return 0;
			}
			else {//검색한 Buffer의 상태가 Free가 아닌 경우
				//Buffer의 상태를 Write로 만들어주고 Free List에서 삭제한다
				device_4.DeleteItem(bf_q);
				bf_s.Setinfo(num, num % 5);
				bf_s.SetState(3);//write로 변경
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

	//0번 Device 출력
	cout << "\n\t\tdevice 0\n" << endl;
	device_0.ResetList();
	for (int i = 0; i < device_0.GetLength(); i++) {
		device_0.GetNextItem(bf);
		bf.DisplayAll();
	}
	//1번 Device 출력
	cout << "\n\t\tdevice 1\n" << endl;
	device_1.ResetList();
	for (int i = 0; i < device_1.GetLength(); i++) {
		device_1.GetNextItem(bf);
		bf.DisplayAll();
	}
	//2번 Device 출력
	cout << "\n\t\tdevice 2\n" << endl;
	device_2.ResetList();
	for (int i = 0; i < device_2.GetLength(); i++) {
		device_2.GetNextItem(bf);
		bf.DisplayAll();
	}
	//3번 Device 출력
	cout << "\n\t\tdevice 3\n" << endl;
	device_3.ResetList();
	for (int i = 0; i < device_3.GetLength(); i++) {
		device_3.GetNextItem(bf);
		bf.DisplayAll();
	}
	//4번 Device 출력
	cout << "\n\t\tdevice 4\n" << endl;
	device_4.ResetList();
	for (int i = 0; i < device_4.GetLength(); i++) {
		device_4.GetNextItem(bf);
		bf.DisplayAll();
	}
	//Free List 출력
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
		cout << "\n\t\t비었습니다.\n" << endl;
		return 0;
	}

}