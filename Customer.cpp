#include "Customer.h"

Customer::Customer(string cusId, string customerName, string address, string phoneNum) :
	cusId(cusId), cusName(customerName), address(address), phoneNum(phoneNum)
{
	this->next = NULL;
}
Customer::Customer(const Customer& cus)
{
	this->cusId = cus.cusId;
	this->cusName = cus.cusName;
	this->address = cus.address;
	this->phoneNum = cus.phoneNum;
	this->next = cus.next;
}
Customer::~Customer() {}
void Customer::setCusId(string customerId)
{
	this->cusId = customerId;
}
void Customer::setCusName(string name) {
	cusName = name;
}
void Customer::setAddress(string address)
{
	this->address = address;
}
void Customer::setPhoneNum(string phoneNum)
{
	this->phoneNum = phoneNum;
}
void Customer::getOtherCus(const Customer& cus)
{
	this->cusId = cus.cusId;
	this->cusName = cus.cusName;
	this->address = cus.address;
	this->phoneNum = cus.phoneNum;
}
void Customer::setCusData()
{
	bool check = true;
	string cusName;
	cin.ignore();
	do
	{
		cout << "Nhap ten khach hang: ";
		getline(cin, cusName);
		if (cusName == "\n" || cusName == "")
		{
			check = false;
			cout << "Nhap lai" << endl;
		}
		else check = true;
	} while (!check);
	this->cusName = cusName;
	string address;
	do
	{
		cout << "Nhap dia chi: ";
		getline(cin, address);
		if (address == ""||address=="\n")
		{
			check = false;
			cout << "Nhap lai" << endl;
		}
		else check = true;
	} while (!check);
	this->address = address;

	string phoneNumber;
	do
	{
		cout << "Nhap so dien thoai: ";
		getline(cin, phoneNumber);
		if (phoneNumber == ""||(phoneNumber.length()!=10&&phoneNumber.length()!=11)) {
			cout << "So dien thoai qua ngan hoac qua dai" << endl;
			check = false;
			continue;
		}
		else
		{
			check = true;
		}
		for (int i = 0; i < phoneNumber.length(); i++)
		{
			if (!isdigit(phoneNumber[i])) { 
				cout << "Nhap lai!" << endl;
				check = false; break; }
			else { check = true; }
		}
	} while (!check);
	this->phoneNum = phoneNumber;
}
ostream& operator<<(ostream& o, const Customer& cus)
{
	o <<"| " <<setw(6)<< cus.cusId<<setw(12)<<"|";
	o << setw(28) <<cus.cusName<<setw(16)<<"|";
	o << setw(45) << cus.address<<setw(2)<<"|";
	o << setw(15)<< cus.phoneNum<<setw(4)<<"|" << endl;
	return o;
}
void Customer::fromString(string str)
{
	string arr[10];
	int count = 0;
	string word;
	for (int i = 0; i <= str.length(); i++)
	{
		if (str[i] == ',' || i == str.length())
		{

			arr[count++] = word;
			word = "";
		}
		else
		{
			word += str[i];
		}
	}
	this->cusId = arr[0];
	this->cusName = arr[1];
	for (int i = 2; i < count - 1; i++)
	{
		this->address += arr[i] + ',';
	}
	this->phoneNum = arr[count-1];
	this->address = this->address.substr(0, address.length() - 1);
}
string Customer::getLastName()
{
	int length = this->getCusName().length();
	string lastName;
	int pos=0;
	for (int i = length; i > 0; i--)
	{
		if (this->cusName[i] == ' ')
		{
			pos = i;
			break;
		}
	}
	lastName = cusName.substr(pos, length);
	return lastName;
}
bool Customer::compareTo(Customer& cus)
{
	if (this->getLastName().compare(cus.getLastName()) < 0) return false;
	else return true;
}

