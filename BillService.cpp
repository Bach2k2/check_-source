#include "BillService.h"
#include<windows.h>
using namespace std;
int BillService::billAmount = 0;
BillService::BillService()
{
	this->pHead = NULL;
	this->pTail = NULL;
}
BillService::~BillService()
{
}
void BillService::readTwoId(string path)
{
	meterList.readFile("meter.txt");
	cusList.readDataInFile("custome.txt");
	path = "CongTo_KhachHang.txt";
	fstream file(path, ios::in);
	if (file.is_open())
	{
		try
		{
			string line;
			while (getline(file, line))
			{
				int meterId = 0;
				string cusId = "";
				string result[3];
				string word;
				int count = 0;
				for (unsigned i = 0; i <= line.length(); i++)
				{
					if (line[i] == ',' || i == line.length())
					{
						result[count++] = word;
						word = "";
					}
					else
					{
						word += line[i];
					}
				}
				meterId = stof(result[0]);
				cusId = result[1];
				ElecMeter meter = meterList.getMeter(meterId);
				Customer cus = cusList.getACus(cusId);
				Date date1;
				Date date2;
				UnitPrice uPrice;
				ElecBill* bill = new ElecBill(meter, cus, date1, date2, uPrice);
				add(bill);
			}
		}
		catch (const char* e)
		{
			cout << e;
		}

	}
	else
	{
		cout << "Duong dan khong ton tai" << endl;
	}
}
void BillService::writeIntoFile(string path)
{
	ofstream oFile(path);
	if (oFile.is_open())
	{
		ElecBill* bill = pHead;
		while (bill != NULL)
		{
			//Dinh dang 
			oFile << bill->getBillId() << endl;
			oFile << bill->meter << endl;
			oFile << bill->customer << endl;
			oFile << " from: " << bill->getBeginDate();
			oFile << " to:  " << bill->getEndDate() << endl;
			oFile << "Total Price: " << bill->getPrice();
			oFile << endl;
			bill = bill->next;

		}
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
	cout << "------------------------------------------------------------------------------" << endl;
	cout << "\t\t\tDANH SACH HOA DON THANG " << bill->getBeginDate().getMonth();
	while (bill != NULL)
	{
		bill->showBillOut();
		Sleep(200);
		bill = bill->next;
		cout << "___________________________________________________________________________" << endl;
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
	cout << "Nhap id hoa don hoac so cong to" << endl;
	cin >> input;
	ElecBill* bill = pHead;
	while (bill != NULL)
	{
		if ((to_string(bill->getBillId()).rfind(input) <= 1) || (to_string(bill->meter.getMeterNumber()).rfind(input) <= 6))
		{
			bill->showBillOut();
		}
		bill = bill->next;
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
		cout << "|";
		Sleep(200);
	}
	ElecBill* bill = pHead;
	while (bill != NULL)
	{
		bill->calcBill();
		bill = bill->next;
	}
	cout << "\nDa tinh dc tien " << endl;

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
void BillService::calcPricePerCus(string cusID)
{
	int count = 0;
	double totalPrice = 0;
	ElecBill* temp = pHead;
	while (temp != NULL)
	{
		if (temp->cusID.compare(cusID) == 0) count++;
		temp = temp->next;
	}
	cout << " Khach hang thang nay co: " << count << " hoa don" << endl;
	ElecBill* bill = pHead;
	while (bill != NULL)
	{
		if (bill->cusID.compare(cusID) == 0) {
			bill->showBillOut();
			totalPrice += bill->getPrice();
			cout << "--------------------------------------------------------" << endl;
		}
		bill=bill->next;
	}
	cout << "Tong tien khach hang  thanh toan trong thang nay: " << totalPrice;
}


