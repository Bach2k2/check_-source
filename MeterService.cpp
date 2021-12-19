#include "MeterService.h"

int MeterService::mAmount = 0;
MeterService::MeterService()
{
	this->mHead = NULL;
	this->mTail = NULL;
}
MeterService::MeterService(const MeterService& meterList) {
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
	ElecMeter* myMeter = new ElecMeter();
	myMeter->setMeterNumber(n_meterNum);
	myMeter->typeAllData();
	if (mHead == NULL)
	{
		mHead = myMeter;
		mTail = mHead;
	}
	else
	{
		mTail->next = myMeter;
		mTail = myMeter;
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
			temp->setMeterNumber(stof(result[0]));
			temp->setCusId(result[1]);
			//temp->fromString(line);
			if(!contain(temp->getMeterNumber()))
			add(temp);
		}
		cout << "THONG BAO: Da them thong tin cac cong to" << endl;
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
			cout << "Nhap so cong to can xoa: " << endl;
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
				cerr << "THONG BAO : Khong tim thay cong to nay" << endl;
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
	if (!isEmpty())
	{
		cout << "\t\t\t\t\t\t DANH SACH CAC CONG TO DIEN HIEN HANH" << endl;
		cout << "____________________________________________________________________________________________________________________________________________________" << endl;
		ElecMeter* meter = mHead;
		cout << "|"<<setw(8)<<" So cong to " << setw(10) << " | " <<setw(10) <<" So dien truoc" << setw(6) << " | "<<setw(8) << "So dien sau " << setw(5) << " | " <<setw(10) <<"So dien tieu thu  " << setw(8) << " | " << "Ma Khach Hang"<<setw(5) <<" | " << endl;
		cout << "____________________________________________________________________________________________________________________________________________________" << endl;
		while (meter != NULL)
		{
			cout << *meter;
			meter = meter->next;
		}
		cout << "____________________________________________________________________________________________________________________________________________________" << endl;
	}
	else
	{
		cout << " THONG BAO : DANH SACH CONG TO DANG RONG" << endl;
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
	cout << "Nhap so cong to can tim kiem: ";
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
	cout << "\nNhap so cong to dien can sua: ";
	cin >> meterNum;
	if (contain(meterNum))
	{
		ElecMeter* temp = &getMeter(meterNum);
		cout << " THONG BAO : DA TIM THAY CONG TO" << endl;
		cout << "----------------Cap nhat cong to-----------------------" << endl;
		cout << "1. Thay doi so cong to" << endl;
		cout << "2. Thay doi so chi dien dau va chi dien sau " << endl;
		cout << "3. Thay doi ma khach hang " << endl;
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
			do {
				cout << " Nhap moi so chi dien dau:" << endl;
				cin >> n_prevUnit;
				if (n_prevUnit < 0) {
					cout << "Nhap lai. So phai lon hon 0" << endl;
					check = false;
				}
				else
				{
					check = true;
				}
			} while (!check);
			temp->setPrevMeter(n_prevUnit);
			int n_nextUnit;
			do {
				cout << " Nhap moi so chi dien sau:" << endl;
				cin >> n_nextUnit;
				if (n_nextUnit < n_prevUnit) {
					cout << "Nhap lai. So phai lon hon so truoc" << endl;
					check = false;
				}
				else
				{
					check = true;
				}
			} while (!check);
			temp->setNextMeter(n_nextUnit);
			int n_unit = n_nextUnit - n_prevUnit;
			temp->setUnit(n_unit);
			break;
		}
		case 3:
		{
			string n_cusId;
			cout << " Nhap ma khach hang moi: " << endl;
			cin >> n_cusId;
			temp->setCusId(n_cusId);
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
		cout << "THONG BAO: Da tim thay duong dan " << endl;
		file << "| So cong to " << setw(18) << "| So dien truoc" << "\t\t" << "| So dien sau \t" << "" << "|\t So dien tieu thu\t\t|" << endl;
		ElecMeter* meter = mHead;
		while (meter != NULL)
		{
			file << *meter;
			meter = meter->next;
		}
		file.close();
	}
	else
	{
		cout << "Khong tim thay duong dan" << endl;
	}
}
void MeterService::sortByMeter(bool check)
{
	for (ElecMeter* temp1 = mHead; temp1 != NULL; temp1 = temp1->next)
	{
		for (ElecMeter* temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next)
		{
			if (temp1->compareWithMeter(*temp2) && check) {
				ElecMeter* hold=new ElecMeter();
				hold->copyData(*temp1);
				temp1->copyData(*temp2);
				temp2->copyData(*hold);
			}
		}
	}
	cout << "THONG BAO: DA SAP XEP THEO XONG" << endl;
}
void MeterService::sortByUnit(bool check)
{
	for (ElecMeter* temp1 = mHead; temp1 != NULL; temp1 = temp1->next)
	{
		for (ElecMeter* temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next)
		{
			if (temp1->compareWithUnit(*temp2) && check) {
				ElecMeter* hold=new ElecMeter();
				hold->copyData(*temp1);
				temp1->copyData(*temp2);
				temp2->copyData(*hold);
			}
		}
	}
	cout << "THONG BAO: DA SAP XEP THEO XONG" << endl;
}