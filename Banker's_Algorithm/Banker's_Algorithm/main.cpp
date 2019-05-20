#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <iomanip>
using namespace std;
random_device random;

//ID, Allocation, Max, Need 할당
struct Process {
	int ID;// Process ID
	int Allocation[5];// Allocation
	int Max[5] = { 0 };// Max
	int Need[5];// Need
	bool finish = true;// Process 종료 여부
};

// Process 초기화
void init(Process* pcs) {
	for (int i = 0; i < 5; i++) {
		pcs->Allocation[i] = random() % 4; // Allocation은 0~3로 설정
		pcs->Max[i] = random() % 5 + 5; // Max는 5~9로 설정
		pcs->Need[i] = pcs->Max[i] - pcs->Allocation[i]; // Need는 Max - Allocation
	}
}

// Process ID 초기화
void init_id(Process* pcs, int id) {
	pcs->ID = id + 1;
}

// 남아있는 Process 출력
void display(Process pcs) {
	if (pcs.finish) {// Process가 종료되지 않았으면 출력
		cout << "P" << pcs.ID; // ID 출력
		for (int i = 0; i < 5; i++) {// Allocation 출력
			cout << setw(2) << pcs.Allocation[i] << " ";
		}cout << " ";
		for (int i = 0; i < 5; i++) {// Max 출력
			cout << setw(2) << pcs.Max[i] << " ";
		}cout << " ";
		for (int i = 0; i < 5; i++) {// Need 출력
			cout << setw(2) << pcs.Need[i] << " ";
		}cout << " " << endl;
	}
}

int main() {
	vector<string> end;// 수행 종료된 Process 순으로 저장하는 vector
	bool can = true;// 수행 가능한지 여부
	int p_size;// Process 개수
	cout << "프로세스 개수 입력 : ";
	cin >> p_size;
	Process *all_Process = new Process[p_size];
	int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, sum5 = 0;

	bool setting = true;// 너무 커지지 않게 조절
	while (setting) {
		for (int i = 0; i < p_size; i++) {
			init(&all_Process[i]);// Process 초기화
			init_id(&all_Process[i], i);// Process ID 초기화
		}
		sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, sum5 = 0;
		for (int i = 0; i < p_size; i++) {// Available 계산
			sum1 += all_Process[i].Allocation[0];
			sum2 += all_Process[i].Allocation[1];
			sum3 += all_Process[i].Allocation[2];
			sum4 += all_Process[i].Allocation[3];
			sum5 += all_Process[i].Allocation[4];
		}
		if ((sum1 <= 10) && (sum2 <= 10) && (sum3 <= 10) && (sum4 <= 10) && (sum5 <= 10))
			setting = false;// 원활한 수행을 위하여 available는 각각 10 이하로 조절해준다
	}

	cout << "===================초기설정=====================" << endl << endl;
	cout << "     Allocation         Max            Need" << endl;
	cout << "   A  B  C  D  E   A  B  C  D  E   A  B  C  D  E" << endl;
	for (int i = 0; i < p_size; i++)
		display(all_Process[i]);// Process 출력
	cout << endl;
	int available[5] = { 15 - sum1, 15 - sum2, 15 - sum3, 15 - sum4, 15 - sum5 };// Available 설정. Total은 모두 15로 설정
	cout << "  Available " << endl;
	cout << " A  B  C  D  E  " << endl;
	for (int i = 0; i < p_size; i++) {// Available 출력
		cout << setw(2) << available[i] << " ";
	}cout << endl << endl;
	cout << "=================================================" << endl;
	cout << endl << endl;

	system("pause");

	bool all_finish = true;// 모든 Process가 종료되었는지 Check
	int count = 0;// Process가 수행이 불가능한지 Check
	while (all_finish) {// Process가 남아있으면 수행
		for (int i = 0; i < p_size; i++) {// 순서대로 Process 수행
			if (all_Process[i].finish == true) {// 해당 Process가 종료되지 않았다면 수행
				// 모든 Need가 Available보다 작으면 다음 수행
				if ((all_Process[i].Need[0] <= available[0]) && (all_Process[i].Need[1] <= available[1]) && (all_Process[i].Need[2] <= available[2]) && (all_Process[i].Need[3] <= available[3]) && (all_Process[i].Need[4] <= available[4])) {
					all_Process[i].finish = false;// 수행 완료 Check
					string id = "P" + to_string(all_Process[i].ID);
					end.push_back(id);// 수행 완료 순으로 Vector에 저장
					for (int j = 0; j < 5; j++)// 업데이트 된 Available 출력
						available[j] += all_Process[i].Allocation[j];
					//남은 Process 출력
					cout << endl << "==============P" << all_Process[i].ID << " 수행================" << endl << endl;
					cout << "     Allocation         Max            Need" << endl;
					cout << "   A  B  C  D  E   A  B  C  D  E   A  B  C  D  E" << endl;
					for (int i = 0; i < p_size; i++)
						display(all_Process[i]);
					cout << endl << "  Available " << endl;
					cout << " A  B  C  D  E  " << endl;
					for (int i = 0; i < p_size; i++) {
						cout << setw(2) << available[i] << " ";
					}cout << endl << endl;
					cout << "=====================================" << endl;
					cout << endl << endl;
					system("pause");
				}
			}
		}
		for (int i = 0; i < p_size; i++) {
			if (all_Process[i].finish == true)// Process중 하나라도 남아있다면 다시 수행
				break;
			if (all_Process[p_size - 1].finish == false) {// 모든 Process가 끝났다면
				all_finish = false;// Check
			}
		}
		count++;
		if (count > 100) { // 수행할 수 없다면 "불가능" 출력
			cout << "불가능" << endl;
			can = false;// 불가능 Check
			break;
		}
	}

	if (can) {// 수행 완료 했다면 다음 출력
		cout << endl << "============수행 순서==============" << endl << endl;
		for (int i = 0; i < p_size; i++) {// Vector의 순서 == 종료된 Process 순서
			cout << end[i] << "  ->  ";
		}cout << "끝" << endl << endl;
		cout << "=====================================" << endl;
		cout << endl;
	}
	system("pause");
}