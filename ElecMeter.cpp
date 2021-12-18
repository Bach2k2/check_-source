#include "ElecMeter.h"
#include <iostream>
#include<string>
#include <iomanip>
using namespace std;
ElecMeter::ElecMeter() {
	this->meterNumber = 0;
	this->prevMeter = 0;
	this->nextMeter = 0;
	this->unit = 0;
	this->next = NULL;
}
ElecMeter::ElecMeter(int meterNumber, int prevMeter, int afterMeter)
{
	this->meterNumber = meterNumber;
	this->prevMeter = prevMeter;
	this->nextMeter = afterMeter;
	this->unit = afterMeter - prevMeter;
	this->next = NULL;
}
ElecMeter::ElecMeter(const ElecMeter& meter)
{
	this->meterNumber = meter.meterNumber;
	this->prevMeter = meter.prevMeter;
	this->nextMeter = meter.nextMeter;
	this->unit = this->nextMeter - this->prevMeter;
	this->next = NULL;
}
ElecMeter::~ElecMeter()
{
}
ostream& operator<<(ostream& os, const ElecMeter& meter)
{
	os << "|\t" << meter.meterNumber << setw(26) << "|\t\t" << meter.prevMeter << "\t" << setw(18) << "|\t " << meter.nextMeter << setw(42) << "|\t " << meter.unit <<setw(21)<< "\t|" << endl;
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
void ElecMeter::writeFile(string path)
{
	fstream file(path);
	if (file.is_open())
	{
		file <<"| So cong to " << setw(18) << "| So dien truoc" << "\t\t" << "| So dien sau \t" << "" << "|\t So dien tieu thu\t\t|" << endl;
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
	this->meterNumber = stof(result[0]);
	this->prevMeter = this->getNextMeter();
	this->nextMeter = stof(result[1]);
	this->unit = this->nextMeter - this->prevMeter;
}
