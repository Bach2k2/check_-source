#include "ElecBill.h"
#include <iomanip>
int ElecBill::increment = 1;
ElecBill::ElecBill()
{
	this->next = NULL;
	this->billId = increment++;
	this->price = 0;
	this->meterNumber = 0;
	this->cusID = "";
}

ElecBill::ElecBill(ElecMeter meter, Customer cus, Date beginDate, Date endDate, UnitPrice& uPrice)
{
	this->billId = increment++;
	this->meter = meter;
	this->customer = cus;
	this->cusID = "";
	this->beginDate = beginDate;
	this->endDate = endDate;
	this->next = NULL;
	this->price = 0;
}
ElecBill::ElecBill(const ElecBill& bill)
{
	this->customer = bill.customer;
	this->meterNumber = bill.meterNumber;
	this->billId = bill.billId;
	this->beginDate = bill.beginDate;
	this->endDate = bill.endDate;
	this->price = bill.price;
	this->next = bill.next;
}
ElecBill::~ElecBill()
{
}
void ElecBill::setBillId(int Billid)
{
	this->billId = Billid;
}
void ElecBill::calcBill()
{
	// Them unit vao
	int unit = meter.getUnit();
	unitPrice.setUnit(unit);
	unitPrice.calcPrice();
	this->price = this->unitPrice.getTotalPrice();
}
void ElecBill::showUnitPrice()
{
	calcBill();
	unitPrice.showUnitPrice();
}
// Nhap tu ban phim
void ElecBill::setBeginDate(Date& date)
{
	this->beginDate = date;
}
void ElecBill::setEndDate(Date& date)
{
	this->endDate = date;
}
Date& ElecBill::getBeginDate()
{
	return this->beginDate;
}
Date& ElecBill::getEndDate()
{
	return this->endDate;
}
double ElecBill::getPrice()
{
	return price;
}
void ElecBill::showBillOut()
{
	cout << "\n *****************************************************************************";
	cout << "\n*\tId hoa don : " << setw(5) << this->getBillId();
	cout << "\n*" << "\tTen Khach Hang: " << setw(15) << this->customer.getCusName() << "\t\t\t\t " << "Ma Khach Hang: " << setw(10) << this->customer.getCusId();
	cout << "\n*" << "\tSo dien thoai : " << setw(10) << this->customer.getPhoneNum();
	cout << "\n*" << "\tDia chi : " << setw(30) << this->customer.getAddress();
	cout << "\n*" << "\tSo cong to : " << setw(5) << this->meter.getMeterNumber();
	cout << "\n*" << "\tNgay bat dau: " << setw(4) << this->getBeginDate() << setw(20) << "Ngay ket thuc: " << this->getEndDate();
	cout << "\n*" << "\tSo dien truoc: " << setw(3) << this->meter.getPrevMeter() << setw(17) << "So dien sau: " << this->meter.getNextMeter();
	this->showUnitPrice();
	cout << "*****************************************************************************" << endl;
}
void ElecBill::fromStringMonth(string line)
{
	string result[4];
	string cell;
	int count = 0;
	for (int i = 0; i <= line.length(); i++)
	{
		if (line[i] == ',' || i == line.length())
		{
			result[count++] = cell;
			cell = "";
		}
		else {
			cell += line[i];
		}
	}

	this->meterNumber = stof(result[0]);

	int n_prevMeter = meter.getNextMeter();

	meter.setNextMeter(stof(result[1]));// Gán giá trị chỉ số sau từ file;
	meter.setPrevMeter(n_prevMeter);
	int unit = meter.getNextMeter() - meter.getPrevMeter();
	this->meter.setUnit(unit);
	this->beginDate.fromString(result[2]);
	Date d1 = this->beginDate;
	Date d2 = d1 += 30;
	setEndDate(d2);
}

void ElecBill::setMeter(const ElecMeter& meter)
{
	this->meter = meter;
}
void ElecBill::setCustomer(const Customer& cus)
{
	this->customer = cus;
}
void ElecBill::setUnitPrice(UnitPrice& unitPrice1)
{
	this->unitPrice.setRank(unitPrice1);
}