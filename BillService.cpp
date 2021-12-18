#include "BillService.h"
#include<windows.h>
using namespace std;
int BillService::billAmount = 0;
BillService::BillService()
{
	this->pHead = NULL;
	this->pTail = NULL;
	this->monthManage = 0;
	this->yearManage = 0;
}
BillService::~BillService()
{
}
void BillService::setCusList(string path)
{
	cusList.readDataInFile(path);
}
void BillService::setMeterList(string path)
{
	meterList.readFile(path);
}

void BillService::writeIntoFile(string path)
{
	ofstream oFile(path);
	if (oFile.is_open())
	{
		oFile << "Id hoa don \t | So cong to\t | Ma Khach Hang\t| Ten Khach Hang\t | So dien thoai \t| Ngay bat dau \t| Ngay ket thuc\t | So dien truoc \t| So dien sau| \t";
		oFile << " So dien tieu thu \t | Gia \t|"<<endl;
		ElecBill* bill = pHead;
		while (bill != NULL)
		{
			oFile << bill->getBillId() << "\t " << bill->meter.getMeterNumber() << "\t " << bill->customer.getCusId()
				<< " \t " << bill->customer.getCusName() << "\t" << bill->customer.getPhoneNum() << "\t " << bill->getBeginDate() << "\t "
				<< bill->getEndDate() << "\t " << bill->meter.getUnit() << "\t" << bill->getPrice()<<endl;
			bill = bill->next;

		}
		oFile.close();
	}
}
void BillService::add(ElecBill* bill)
{
	if (pHead == NULL)
	{
		pHead = bill;
		pTail = pHead;
	}
	else
	{
		pTail->next = bill;
		pTail = bill;
	}
	billAmount++;
}
void BillService::display()
{
	calculatePrice();
	ElecBill* bill = pHead;
	if (isEmpty())
	{
		cout << "\n\t\tTHONG BAO: DANH SACH CAC HOA DON TRONG" << endl;
		system("pause");
	}
	else
	{
		cout << "\n------------------------------------------------------------------------------" << endl;
		cout << "\t\t\t DANH SACH HOA DON THANG " << this->monthManage << endl;
		while (bill != NULL)
		{
			bill->showBillOut();
			Sleep(200);
			bill = bill->next;
			cout << "___________________________________________________________________________" << endl;
		}
	}

}
void BillService::displayWithArea(string address)
{
	ElecBill* bill = pHead;

	while (bill != NULL)
	{
		Customer* cus = &bill->customer;
		if (cus->getAddress().rfind(address) <= 100) bill->showBillOut();
		bill = bill->next;
	}
}
void BillService::readNewMonth(string path)
{
	fstream file(path);
	if (file.is_open())
	{
		cout << "Da doc duoc du lieu" << endl;
		string line;
		ElecBill* bill = pHead;
		while (getline(file, line) && bill != NULL)
		{
			bill->fromStringMonth(line);
			bill = bill->next;
		}
	}
	else
	{
		cerr << "File khong tim thay" << endl;
	}
}
void BillService::remove()
{
	bool check = false;
	cout << "Co muon xoa hay khong" << endl;;
	int choice;
	cout << "1- Xoa, 0- Huy" << endl;
	cin >> choice;
	check = choice;
	if (check)
	{
		if (pHead == NULL)
		{
			cout << "Danh sach cac hoa don trong rong";
		}
		else
		{
			int billID;
			do
			{
				cin.ignore();
				cout << "Nhap id cua hoa don can xoa: " << endl;
				cin >> billID;
			} while (billID<0 || billID>billAmount);
			ElecBill* after = pHead;
			ElecBill* before = after;
			while (after != NULL)
			{
				if (after->getBillId() == billID) break;
				before = after;
				after = after->next;
			}
			if (after != NULL)
			{
				if (pHead == after)
				{
					pHead = after->next;
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
				billAmount--;

			}
			else {
				throw "Khong tim thay con tro can xoa";
			}

		}
	}
}
void BillService::search()
{
	string input;
	cout << "Nhap id hoa don" << endl;
	cin >> input;
	ElecBill* bill = pHead;
	if (contain(stof(input)))
	{
		while (bill != NULL)
		{
			if ((to_string(bill->getBillId()).rfind(input) <= 1) || (to_string(bill->meter.getMeterNumber()).rfind(input) <= 6))
			{
				bill->showBillOut();
			}
			bill = bill->next;
		}
	}
	else
	{
		cout << "THONG BAO: KHONG CO HOA DON DUOC TIM THAY" << endl;
	}
}
void BillService::searchByMeter(int meterNum)
{
	ElecBill* bill = pHead;
	if (meterList.contain(meterNum))
	{
		while (bill != NULL)
		{
			if ((to_string(bill->meter.getMeterNumber()).rfind(to_string(meterNum)) <= 6))
			{
				bill->showBillOut();
			}
			bill = bill->next;
		}
	}
	else
	{
		cout << " THONG BAO: KHONG TIM THAY DUOC HOA DON NAO " << endl;
	}
}
void BillService::searchByCustomer(string name)
{
	ElecBill* bill = pHead;
	if (cusList.contain(name))
		while (bill != NULL)
		{
			if ((bill->customer.getCusName()).rfind(name) <= 6)
			{
				bill->showBillOut();
			}
			bill = bill->next;
		}
	else
	{
		cout << " THONG BAO: KHONG TIM THAY DUOC HOA DON NAO " << endl;
	}
}
bool BillService::isEmpty()
{
	if (pHead == NULL)
	{
		return true;
	}
	else return false;
}
bool BillService::contain(int billID)
{
	ElecBill* bill = pHead;
	while (bill != NULL)
	{
		if (bill->getBillId() == billID)
		{
			return true;
			break;
		}
		bill = bill->next;
	}
	return false;
}
void BillService::calculatePrice()
{
	cout << " Dang tinh..." << endl;
	cout << "\n\t\t\t";
	for (int i = 0; i < 10; i++)
	{
		cout << "00";
		Sleep(200);
	}
	cout << "\n";
	ElecBill* bill = pHead;
	while (bill != NULL)
	{
		bill->calcBill();
		bill = bill->next;
	}
}
void BillService::setAllUP(UnitPrice& UP)
{
	ElecBill* bill = pHead;
	while (bill != NULL)
	{
		bill->setUnitPrice(UP);
		bill = bill->next;
	}
	cout << " Da nhan du lieu tu don gia thanh cong" << endl;
}
ElecBill& BillService::getABill(int billId)
{
	ElecBill* temp = pHead;
	while (temp != NULL)
	{
		if (temp->getBillId() == billId) {
			return *temp;
		}
		temp = temp->next;
	}
	throw "Khong tim thay bill nao";
	return *temp;
}
void BillService::update()
{
	cout << "Nhap id cua bill can sua" << endl;
	int billId;
	cin >> billId;
	bool check;
	try {
		ElecBill* temp = &getABill(billId);
		if (temp == NULL) throw " Khong tim thay bill";
		else
		{
			cout << " Da tim thay bill " << endl;
			cout << "------------- Sua thong tin cua hoa don-----------------------" << endl;
			cout << "1. Thay doi id cua hoa don" << endl;
			cout << "2. Thay doi ngay bat dau cua hoa don" << endl;
			cout << "3. Thay doi ngay ket thuc cua hoa don" << endl;
			cout << "0. Thoat" << endl;
			cout << "--------------------------------------------------------" << endl;
			cout << " Lua chon: ";
			int choice;
			cin >> choice;

			switch (choice)
			{
			case 1:
			{
				int n_billId;
				do
				{
					cout << " Nhap id moi cua hoa don: " << endl;
					cin >> n_billId;
					if (contain(n_billId) || n_billId < 0)
					{
						check = false;
						cout << " Nhap lai! Id moi khong hop le" << endl;
					}
					else
					{
						check = true;
					}
				} while (!check);
				temp->setBillId(n_billId);
				cout << " Don vi da duoc chinh sua: " << endl;
				temp->showBillOut();
				break;
			}
			case 2:
			{
				Date n_beginDate;
				int dd, mm, yy;
				do
				{
					cout << "Nhap ngay: " << endl;
					cin >> dd;
					cout << "Nhap thang: " << endl;
					cin >> mm;
					cout << "Nhap nam: " << endl;
					cin >> yy;
					if (!n_beginDate.checkDate(dd, mm, yy))
					{
						cout << "Ngay khong dung!, nhap lai" << endl;
						check = false;
					}
					else
						check = true;
				} while (!check);
				temp->setBeginDate(n_beginDate);
				temp->showBillOut();
				break;
			}
			case 3:
			{
				Date n_endDate;
				int dd, mm, yy;
				do
				{
					cout << "Nhap ngay: " << endl;
					cin >> dd;
					cout << "Nhap thang: " << endl;
					cin >> mm;
					cout << "Nhap nam: " << endl;
					cin >> yy;
					if (!n_endDate.checkDate(dd, mm, yy))
					{
						cout << "Ngay khong dung!, nhap lai" << endl;
						check = false;
					}
					else
						check = true;
				} while (!check);
				temp->setEndDate(n_endDate);
				temp->showBillOut();
				break;
			}
			default:
			{
				cout << "Nhap lua chon khong dung" << endl;
				break;
			}
			}
		}
	}
	catch (const char* e)
	{
		cout << e;
	}
}
void BillService::createBill(MeterService& meterList, CustomerService& cusList, UnitPrice& uPrice)
{
	this->meterList = meterList;
	this->cusList = cusList;
	int month, year;
	cout << "Nhap thang,nam quan ly:" << endl;
	cin >> month >> year;
	this->monthManage = month;
	this->yearManage = year;
	Date date1(1, month, year);
	Date date2(1, month + 1, year);
	for (ElecMeter* meter = this->meterList.mHead; meter != NULL; meter = meter->next)
	{
		try
		{
			string cusId = meter->getCusID();
			Customer* cus = &cusList.getACus(cusId);
			ElecBill* elecBill = new ElecBill(*meter, *cus, date1, date2, uPrice);
			add(elecBill);
		}
		catch (const char* e)
		{
			cout << "\n";
		}
		catch (...)
		{
			cout << "\n";
		}
	}
}
void BillService::exByArea(string path,string address)
{
	fstream oFile(path);
	if (oFile.is_open())
	{
		oFile << "Id hoa don \t | So cong to\t | Ma Khach Hang\t| Ten Khach Hang\t | So dien thoai \t| Ngay bat dau \t| Ngay ket thuc\t | So dien truoc \t| So dien sau| \t";
		oFile << " So dien tieu thu \t | Gia \t|"<<endl;
		ElecBill* bill = pHead;
		while (bill != NULL)
		{
			Customer* cus = &bill->customer;
			if (cus->getAddress().rfind(address) <= 100)
			{
				oFile << bill->getBillId() << "\t " << bill->meter.getMeterNumber() << "\t " << bill->customer.getCusId()
					<< " \t " << bill->customer.getCusName() << "\t" << bill->customer.getPhoneNum() << "\t " << bill->getBeginDate() << "\t "
					<< bill->getEndDate() << "\t " << bill->meter.getUnit() << "\t" << bill->getPrice()<<endl;
			}
			bill = bill->next;
		}
	}
}
void BillService::exABill(string path, string cusID)
{
	fstream oFile(path);
	if(oFile.is_open())
	{
		oFile << "Id hoa don \t | So cong to\t | Ma Khach Hang\t| Ten Khach Hang\t | So dien thoai \t| Ngay bat dau \t| Ngay ket thuc\t | So dien truoc \t| So dien sau| \t";
		oFile << " So dien tieu thu \t | Gia \t|"<<endl;
		ElecBill* bill = pHead;
		if (cusList.contain(cusID))
			while (bill != NULL)
			{
				if ((bill->customer.getCusId()).rfind(cusID) <= 6)
				{

					oFile << bill->getBillId() << "\t " << bill->meter.getMeterNumber() << "\t " << bill->customer.getCusId()
						<< " \t " << bill->customer.getCusName() << "\t" << bill->customer.getPhoneNum() << "\t " << bill->getBeginDate() << "\t "
						<< bill->getEndDate() << "\t " << bill->meter.getUnit() << "\t" << bill->getPrice()<<endl;
				}
				bill = bill->next;
			}
	}
}


