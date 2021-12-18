#pragma once
#include <iostream>
#include <string>
using namespace std;
class Customer{
private:
	string cusId;
	string cusName;
	string phoneNum;
	string address;

public:
	Customer* next;
	Customer(string = "", string = "", string = "", string = "");
	Customer(const Customer&);
	~Customer();
	friend ostream& operator<<(ostream&, const Customer&);
	void fromString(string);
	//get va set
	void setCusData();
	void setCusId(string);
	void setCusName(string);
	void setPhoneNum(string);
	void setAddress(string);
	void getOtherCus(const Customer&);
	string getCusId() {
		return cusId;
	}
	string getCusName() { return cusName; }
	string getPhoneNum() { return phoneNum; }
	string getAddress() { return address; }
	bool compareTo(Customer&);
	string getLastName();
};

