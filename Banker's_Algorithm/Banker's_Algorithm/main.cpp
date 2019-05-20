#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <iomanip>
using namespace std;
random_device random;

//ID, Allocation, Max, Need �Ҵ�
struct Process {
	int ID;// Process ID
	int Allocation[5];// Allocation
	int Max[5] = { 0 };// Max
	int Need[5];// Need
	bool finish = true;// Process ���� ����
};

// Process �ʱ�ȭ
void init(Process* pcs) {
	for (int i = 0; i < 5; i++) {
		pcs->Allocation[i] = random() % 4; // Allocation�� 0~3�� ����
		pcs->Max[i] = random() % 5 + 5; // Max�� 5~9�� ����
		pcs->Need[i] = pcs->Max[i] - pcs->Allocation[i]; // Need�� Max - Allocation
	}
}

// Process ID �ʱ�ȭ
void init_id(Process* pcs, int id) {
	pcs->ID = id + 1;
}

// �����ִ� Process ���
void display(Process pcs) {
	if (pcs.finish) {// Process�� ������� �ʾ����� ���
		cout << "P" << pcs.ID; // ID ���
		for (int i = 0; i < 5; i++) {// Allocation ���
			cout << setw(2) << pcs.Allocation[i] << " ";
		}cout << " ";
		for (int i = 0; i < 5; i++) {// Max ���
			cout << setw(2) << pcs.Max[i] << " ";
		}cout << " ";
		for (int i = 0; i < 5; i++) {// Need ���
			cout << setw(2) << pcs.Need[i] << " ";
		}cout << " " << endl;
	}
}

int main() {
	vector<string> end;// ���� ����� Process ������ �����ϴ� vector
	bool can = true;// ���� �������� ����
	int p_size;// Process ����
	cout << "���μ��� ���� �Է� : ";
	cin >> p_size;
	Process *all_Process = new Process[p_size];
	int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, sum5 = 0;

	bool setting = true;// �ʹ� Ŀ���� �ʰ� ����
	while (setting) {
		for (int i = 0; i < p_size; i++) {
			init(&all_Process[i]);// Process �ʱ�ȭ
			init_id(&all_Process[i], i);// Process ID �ʱ�ȭ
		}
		sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, sum5 = 0;
		for (int i = 0; i < p_size; i++) {// Available ���
			sum1 += all_Process[i].Allocation[0];
			sum2 += all_Process[i].Allocation[1];
			sum3 += all_Process[i].Allocation[2];
			sum4 += all_Process[i].Allocation[3];
			sum5 += all_Process[i].Allocation[4];
		}
		if ((sum1 <= 10) && (sum2 <= 10) && (sum3 <= 10) && (sum4 <= 10) && (sum5 <= 10))
			setting = false;// ��Ȱ�� ������ ���Ͽ� available�� ���� 10 ���Ϸ� �������ش�
	}

	cout << "===================�ʱ⼳��=====================" << endl << endl;
	cout << "     Allocation         Max            Need" << endl;
	cout << "   A  B  C  D  E   A  B  C  D  E   A  B  C  D  E" << endl;
	for (int i = 0; i < p_size; i++)
		display(all_Process[i]);// Process ���
	cout << endl;
	int available[5] = { 15 - sum1, 15 - sum2, 15 - sum3, 15 - sum4, 15 - sum5 };// Available ����. Total�� ��� 15�� ����
	cout << "  Available " << endl;
	cout << " A  B  C  D  E  " << endl;
	for (int i = 0; i < p_size; i++) {// Available ���
		cout << setw(2) << available[i] << " ";
	}cout << endl << endl;
	cout << "=================================================" << endl;
	cout << endl << endl;

	system("pause");

	bool all_finish = true;// ��� Process�� ����Ǿ����� Check
	int count = 0;// Process�� ������ �Ұ������� Check
	while (all_finish) {// Process�� ���������� ����
		for (int i = 0; i < p_size; i++) {// ������� Process ����
			if (all_Process[i].finish == true) {// �ش� Process�� ������� �ʾҴٸ� ����
				// ��� Need�� Available���� ������ ���� ����
				if ((all_Process[i].Need[0] <= available[0]) && (all_Process[i].Need[1] <= available[1]) && (all_Process[i].Need[2] <= available[2]) && (all_Process[i].Need[3] <= available[3]) && (all_Process[i].Need[4] <= available[4])) {
					all_Process[i].finish = false;// ���� �Ϸ� Check
					string id = "P" + to_string(all_Process[i].ID);
					end.push_back(id);// ���� �Ϸ� ������ Vector�� ����
					for (int j = 0; j < 5; j++)// ������Ʈ �� Available ���
						available[j] += all_Process[i].Allocation[j];
					//���� Process ���
					cout << endl << "==============P" << all_Process[i].ID << " ����================" << endl << endl;
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
			if (all_Process[i].finish == true)// Process�� �ϳ��� �����ִٸ� �ٽ� ����
				break;
			if (all_Process[p_size - 1].finish == false) {// ��� Process�� �����ٸ�
				all_finish = false;// Check
			}
		}
		count++;
		if (count > 100) { // ������ �� ���ٸ� "�Ұ���" ���
			cout << "�Ұ���" << endl;
			can = false;// �Ұ��� Check
			break;
		}
	}

	if (can) {// ���� �Ϸ� �ߴٸ� ���� ���
		cout << endl << "============���� ����==============" << endl << endl;
		for (int i = 0; i < p_size; i++) {// Vector�� ���� == ����� Process ����
			cout << end[i] << "  ->  ";
		}cout << "��" << endl << endl;
		cout << "=====================================" << endl;
		cout << endl;
	}
	system("pause");
}