#include "Customer.h"
#include <iostream>
#include <string>
#include<fstream>
using namespace std;
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
	do
	{
		cout << "Nhap ten khach hang";
		cin.ignore(32767, '\n');
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
		cin.ignore(32767, '\n');
		getline(cin, phoneNumber);
		if (phoneNumber == "") { check = false; }
		else
		{
			check = true;
		}
		for (int i = 0; i < phoneNumber.length(); i++)
		{
			if (!isdigit(phoneNumber[i])) { check = false; break; }
			else { check = true; }
		}
	} while (!check);
	this->phoneNum = phoneNumber;
}
ostream& operator<<(ostream& o, const Customer& cus)
{
		o<< cus.cusId <<" "
		 << cus.cusName << " "
		 << cus.address  << " "
		 << cus.phoneNum << endl;
	return o;
}
void Customer::fromString(string str)
{
	string arr[20];
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
	int length = count;
	this->cusId = arr[0];
	this->cusName = arr[1];
	this->phoneNum = arr[length - 1];
	cout << count;
	for (int i = 2; i < length - 1; i++)
	{
		this->address += arr[i] + ',';
	}
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

