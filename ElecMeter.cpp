#include "ElecMeter.h"
#include <iostream>
#include<string>
#include <iomanip>
using namespace std;
ElecMeter::ElecMeter(int meterNumber, int prevMeter, int afterMeter, string cusID)
{
	this->meterNumber = meterNumber;
	this->prevMeter = prevMeter;
	this->nextMeter = afterMeter;
	this->unit = afterMeter - prevMeter;
	this->cusId = cusID;
	this->next = NULL;
}
ElecMeter::ElecMeter(const ElecMeter& meter)
{
	this->meterNumber = meter.meterNumber;
	this->prevMeter = meter.prevMeter;
	this->nextMeter = meter.nextMeter;
	this->unit = this->nextMeter - this->prevMeter;
	this->cusId = meter.cusId;
	this->next = NULL;
}
ElecMeter::~ElecMeter()
{
}
ostream& operator<<(ostream& os, const ElecMeter& meter)
{
	os << "|\t" << meter.meterNumber
		<< setw(26) << "|\t" << meter.prevMeter << "\t"
		<< setw(15) << "|\t " << meter.nextMeter
		<< setw(15) << "|\t " << meter.unit
		<< setw(18) << "\t|" << meter.cusId
		<< setw(20) << "|" << endl;
	return os;
}
void ElecMeter::setUnit(int unit)
{
	this->unit = unit;
}
void  ElecMeter::setMeterNumber(int number)
{
	this->meterNumber = number;
}
void ElecMeter::setPrevMeter(int meter)
{
	this->prevMeter = meter;
}
void ElecMeter::setNextMeter(int meter)
{
	this->nextMeter = meter;
}
void ElecMeter::setCusId(string id)
{
	this->cusId = id;
}
void ElecMeter::writeFile(string path)
{
	fstream file(path);
	if (file.is_open())
	{
		file << "| So cong to " << setw(18) << "| So dien truoc" << "\t\t" << "| So dien sau \t" << "" << "|\t So dien tieu thu\t\t|" << endl;
		file << "| " << this->meterNumber << setw(6) << "|\t" << this->prevMeter << "\t" << setw(8) << "|  " << this->nextMeter << setw(12) << "|\t " << this->unit << setw(12) << "\t|" << endl;
	}
	else
	{
		cout << "Khong thay file can tim" << endl;
	}
}
void ElecMeter::fromString(string line)
{
	string result[10];
	string cell;
	int count = 0;
	for (int i = 0; i <= line.length(); i++)
	{
		if (line[i] == ',' || i == line.length())
		{
			result[count++] = cell;
			cell = "";
		}
		else
		{
			cell += line[i];
		}
	}
	for (int i = 0; i < count; i++)
	{
		if (result[i] == "") throw "Khong nhan thong tin chinh xac tu file\n";
	}
	this->meterNumber = stof(result[0]);
	this->cusId = result[1];
}
void ElecMeter::typeAllData()
{
	int n_prevMeter, n_nextMeter;
	string n_cusID;
	cout << "Nhap so dien ban dau: " << endl;
	cin >> n_prevMeter;
	cout << "Nhap so dien sau: " << endl;
	cin >> n_nextMeter;
	setPrevMeter(n_prevMeter);
	setNextMeter(n_nextMeter);
	unit = nextMeter - prevMeter;
	cout << "Nhap ma khach hang: " << endl;
	cin >> n_cusID;
	setCusId(n_cusID);
}
