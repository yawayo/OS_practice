#pragma once
#include<iostream>

using namespace std;

class BufferData {
public:
	BufferData();
	~BufferData();

	void Setinfo(int b_id, int d_num);//Buffer�� data�� device number�� ����
	void SetState(int state);//Buffer�� ���¸� ����
	int Getid();//Buffer�� Data ����
	int Getnum();//Buffer�� Device number ����
	int GetState();//Buffer�� ���� ����
	void DisplayAll();//Buffer�� ���� ���


	bool operator== (const BufferData &obj) { return (this->buffer_id == obj.buffer_id); }
	bool operator> (const BufferData &obj) { return (this->buffer_id > obj.buffer_id); }
	bool operator< (const BufferData &obj) { return (this->buffer_id < obj.buffer_id); }
	bool operator>= (const BufferData &obj) { return !(*this >= obj); }
	bool operator<= (const BufferData &obj) { return !(*this <= obj); }

private:
	int buffer_id;//Buffer�� data
	int device_num;//Buffer�� Device number
	int state_Free;//Free ����
	int state_Busy;//Busy ����
	int state_Delay;//Delay ����
	int state_Write;//Write ����
};

