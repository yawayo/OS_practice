#pragma once
#include<iostream>

using namespace std;

class BufferData {
public:
	BufferData();
	~BufferData();

	void Setinfo(int b_id, int d_num);//Buffer의 data와 device number를 설정
	void SetState(int state);//Buffer의 상태를 설정
	int Getid();//Buffer의 Data 리턴
	int Getnum();//Buffer의 Device number 리턴
	int GetState();//Buffer의 상태 리턴
	void DisplayAll();//Buffer의 정보 출력


	bool operator== (const BufferData &obj) { return (this->buffer_id == obj.buffer_id); }
	bool operator> (const BufferData &obj) { return (this->buffer_id > obj.buffer_id); }
	bool operator< (const BufferData &obj) { return (this->buffer_id < obj.buffer_id); }
	bool operator>= (const BufferData &obj) { return !(*this >= obj); }
	bool operator<= (const BufferData &obj) { return !(*this <= obj); }

private:
	int buffer_id;//Buffer의 data
	int device_num;//Buffer의 Device number
	int state_Free;//Free 상태
	int state_Busy;//Busy 상태
	int state_Delay;//Delay 상태
	int state_Write;//Write 상태
};

