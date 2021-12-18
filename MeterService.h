#pragma once
#include <fstream>
using namespace std;
#include "ElecMeter.h"
class MeterService
{
private:
	ElecMeter* mHead; //
	ElecMeter* mTail;
	static int mAmount;
	int monthManage;
	int yearManage;
public:
	MeterService();
	MeterService(const MeterService&);
	~MeterService();
	void add();//Thêm nhập từ bàn phím
	void add(ElecMeter*);// Nhận từ file
	bool isEmpty();// Danh sách có rỗng
	void remove();// Xóa
	void update(); 
	void display(); // Rồi
	void search(); 
	void readFile(string path); // Đọc file
	void writeFile(string path); // in ra file
	bool contain(int);
	// void calculatePrice();
	// void MonthManger();
	ElecMeter& getMeter(int meterNum);
};


