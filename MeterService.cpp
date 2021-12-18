#include "MeterService.h"
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;
int MeterService::mAmount = 0;
MeterService::MeterService()
{
	this->mHead = NULL;
	this->mTail = NULL;
	this->monthManage = 0;
	this->yearManage = 0;
}
MeterService::MeterService(const MeterService & meterList) {
	this->mHead = meterList.mHead;
	this->mTail = meterList.mTail;
}
MeterService::~MeterService()
{
	delete mHead;
	delete mTail;
}
// Them moi 1 cong to vao danh sach
void MeterService::add()
{
	bool check = true;
	cin.ignore(32767, '\n');
	int n_meterNum;
	do
	{
		cout << "Nhap so cong to dien" << endl;
		cin >> n_meterNum;
		if (n_meterNum < 0 || contain(n_meterNum))
		{
			cout << "Nhap lai! So cong to khong hop le" << endl;
			check = false;
		}
		else {
			check = true;	
		}
	} while (!check);
	ElecMeter* meter = new ElecMeter();
	meter->setMeterNumber(n_meterNum);
	if (mHead == NULL)
	{
		mHead = meter;
		mTail = mHead;
	}
	else
	{
		mTail->next = meter;
		mTail = meter;
	}
	cout << "Da Them";
	mAmount++;
}
void MeterService::add(ElecMeter* meter)
{
	if (isEmpty())
	{
		mHead = meter;
		mTail = meter;
	}
	else
	{
		mTail->next = meter;
		mTail = meter;
	}
	mAmount++;
}
void MeterService::readFile(string path)
{
	fstream file(path, ios::in);
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			ElecMeter* temp = new ElecMeter();
			temp->fromString(line);
			add(temp);
		}
		file.close();
	}

}
bool MeterService::contain(int meterNum)
{
	ElecMeter* meter = mHead;
	while (meter != NULL)
	{
		if (meter->getMeterNumber() == meterNum)
		{
			return true;
		}
		meter = meter->next;
	}
	return false;
}
bool MeterService::isEmpty()
{
	if (mHead == NULL) return true;
	else return false;
}
void MeterService::remove()
{
	bool check = false;
	cout << "Co muon xoa hay khong" << endl;;
	int choice;
	cout << "1- Xoa, 0- Huy" << endl;
	cin >> choice;
	check = choice;
	if (check)
	{
		if (isEmpty())
		{
			cout << "Danh sach cac hoa don trong rong";
		}
		else
		{
			int meterNumber;
			cin.ignore();
			cout << "Nhap so cong to cua hoa don can xoa: " << endl;
			cin >> meterNumber;
			ElecMeter* after = mHead;
			ElecMeter* before = after;
			while (after != NULL)
			{
				if (after->getMeterNumber() == meterNumber) break;
				before = after;
				after = after->next;
			}
			if (after == NULL)
			{
				cout << "Khong tim thay cong to nay" << endl;
			}
			else
			{
				if (mHead == after)
				{
					mHead = after->next;
					after->next = NULL;
					delete after;
					after = NULL;
				}
				else
				{
					before->next = after->next;
					after->next = NULL;
					delete after;
					after = NULL;
				}
				cout << "Xoa thanh cong" << endl;
				mAmount--;
			}
		}
	}
}
void MeterService::display()
{
	cout << "\t\t\t\t DANH SACH CAC CONG TO DIEN HIEN HANH" << endl;
	ElecMeter* meter = mHead;
	cout << "|\t So cong to " << setw(18) << "|\t"<<" So dien truoc\t" << setw(18) << " | \t"<<"So dien sau \t" << setw(28)<< "|\t "<<"So dien tieu thu\t | " << endl;
	cout << "_________________________________________________________________________________________________________________________________________________________" << endl;
	while (meter != NULL)
	{
		cout << *meter;
		meter = meter->next;
	}
}
ElecMeter& MeterService::getMeter(int meterNumber)
{
	ElecMeter* temp = mHead;
	if (contain(meterNumber))
	{
		while (temp != NULL)
		{
			if (temp->getMeterNumber() == meterNumber)
			{
				return *temp;
			}
			temp = temp->next;
		}
	}
	else
	{
		throw "Error! Khong tim duoc so cong to";
	}
	
}
void MeterService::search()
{
	string n_meterNum;
	cout << "Nhap so cong to can tim kiem" << endl;
	cin >> n_meterNum;
	int count = 0;
	ElecMeter* temp1 = mHead;
	while (temp1 != NULL)
	{
		string str = to_string(temp1->getMeterNumber());
		if (str.rfind(n_meterNum) <= 5)
		{
			count++;
		}
		temp1 = temp1->next;
	}
	cout << "Da tim thay: " << count << " cong to: " << endl;
	ElecMeter* temp2 = mHead;
	while (temp2 != NULL)
	{
		string str = to_string(temp2->getMeterNumber());
		if (str.rfind(n_meterNum) <= 5)
		{
			cout << *temp2;
			cout << "-----------------------------------" << endl;
		}
		temp2 = temp2->next;
	}
}
void MeterService::update()
{
	int meterNum;
	cout << "\nNhap so cong to cua hoa don: ";
	cin >> meterNum;
	if (contain(meterNum))
	{
		ElecMeter* temp = &getMeter(meterNum);
		cout << "----------------Cap nhat cong to-----------------------" << endl;
		cout << "1. So cong to" << endl;
		cout << "2. So chi dien dau" << endl;
		cout << "3. So chi dien sau " << endl;
		cout << "----------------------------------------------------------" << endl;
		int choice;
		bool check = true;
		cout << "Lua chon: " << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			cout << "so cong to moi: " << endl;
			int n_meterNum;
			do
			{
				cin >> n_meterNum;
				if (n_meterNum == temp->getMeterNumber())
				{
					check = true;
					cout << "giu nguyen gia tri cu";
					break;
				}
				else
				{
					if (contain(n_meterNum))
					{
						check = false;
						cout << "Da co so cong to nay" << endl;
					}
					check = true;
				}
			} while (!check);
			temp->setMeterNumber(n_meterNum);
			cout << "Da sua" << endl;
			break;
		}
		case 2:
		{
			int n_prevUnit;
			cout << " Nhap moi so chi dien dau:" << endl;
			cin >> n_prevUnit;
			temp->setPrevMeter(n_prevUnit);
			break;
		}
		case 3:
		{
			int n_nextUnit;
			cout << " Nhap moi so chi dien sau:" << endl;
			cin >> n_nextUnit;
			temp->setPrevMeter(n_nextUnit);
			break;
		}
		default:
		{
			cout << " Lua chon khong phu hop" << endl;
			break;
		}
			
		}
		cout << "Cong to sau khi cap nhat" << endl;
		cout << *temp;
	}
	else
	{
		cout << "Khong tim thay cong to nay" << endl;
	}
	
}
void MeterService::writeFile(string path)
{
	ofstream file(path, ios::out);
	if (file.is_open())
	{
		file << "| So cong to " << setw(18) << "| So dien truoc" << "\t\t" << "| So dien sau \t" << "" << "|\t So dien tieu thu\t\t|" << endl;
		ElecMeter* meter = mHead;
		while (meter != NULL)
		{
			file << *meter;
			meter = meter->next;
		}
	}
	else
	{
		cout << "Khong tim thay duong dan" << endl;
	}
}