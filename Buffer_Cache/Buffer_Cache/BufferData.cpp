#include "BufferData.h"


BufferData::BufferData() {
	buffer_id = -1;
	device_num = -1;
	state_Free = -1;
	state_Busy = -1;
	state_Delay = -1;
	state_Write = -1;
}
BufferData::~BufferData() {}

void BufferData::Setinfo(int b_id, int d_num) { buffer_id = b_id; device_num = d_num; }

void BufferData::SetState(int state){
	if (state == 0) {
		state_Free = 1;
		state_Busy = -1;
		state_Delay = -1;
		state_Write = -1;

	}
	else if (state == 1) {
		state_Free = -1;
		state_Busy = 1;
		state_Delay = -1;
		state_Write = -1;

	}
	else if (state == 2) {
		state_Free = -1;
		state_Busy = -1;
		state_Delay = 1;
		state_Write = -1;

	}
	else if (state == 3) {
		state_Free = -1;
		state_Busy = -1;
		state_Delay = -1;
		state_Write = 1;

	}
}

int BufferData::Getid() { return buffer_id; }

int BufferData::Getnum() { return device_num; }

int BufferData::GetState() {
	if (state_Free == 1)
		return 0;
	else if (state_Busy == 1)
		return 1;
	else if (state_Delay == 1)
		return 2;
	else if (state_Write == 1)
		return 3;
	else
		return -1;
}

void BufferData::DisplayAll() {
	cout << "\tdevice : " << device_num << " , ";
	cout << "data : " << buffer_id << " , ";
	if (state_Free == 1)
		cout << "State : Free";
	else if (state_Busy == 1)
		cout << "State : Busy";
	else if (state_Delay == 1)
		cout << "State : Delay";
	else if (state_Write == 1)
		cout << "State : Write";
	cout << endl;
}