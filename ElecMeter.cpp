#include "ElecMeter.h"

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
		<< setw(10) << "|"<<setw(6) << meter.prevMeter << "\t"
		<< setw(10) << "|" << setw(6) << meter.nextMeter
		<< setw(11) << "|" << setw(6) << meter.unit
		<< setw(21) << "|" << setw(6) << meter.cusId
		<< setw(10) << "|" << endl;
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
	//this->prevMeter = this->getNextMeter();
	//this->nextMeter = stof(result[1]);
	//this->unit = this->nextMeter - this->prevMeter;
}
void ElecMeter::typeAllData()
{
	bool check = true;
	int n_prevMeter, n_nextMeter;
	string n_cusID;
	do
	{
		cout << "Nhap so dien ban dau: " << endl;
		cin >> n_prevMeter;
		if (n_prevMeter < 0) check = false;
		else check = true;
		cout << "Nhap so dien sau: " << endl;
		cin >> n_nextMeter;
		if (n_nextMeter < n_prevMeter) check = false;
		else check = true;
	} while (!check);
	setPrevMeter(n_prevMeter);
	setNextMeter(n_nextMeter);
	unit = nextMeter - prevMeter;
	cout << "Nhap ma khach hang: " << endl;
	cin >> n_cusID;
	setCusId(n_cusID);
}
void ElecMeter::copyData(ElecMeter& oMeter)
{
	this->meterNumber = oMeter.meterNumber;
	this->prevMeter = oMeter.prevMeter;
	this->nextMeter = oMeter.nextMeter;
	this->unit = oMeter.unit;
	this->cusId = oMeter.cusId;
}
bool ElecMeter::compareWithMeter(ElecMeter& oMeter)
{
	if (this->meterNumber > oMeter.getMeterNumber()) return true;
	else return false;
}
bool ElecMeter::compareWithUnit(ElecMeter& oMeter)
{
	if (this->unit > oMeter.getUnit()) return true;
	else return false;
}