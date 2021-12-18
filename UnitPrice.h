#pragma once
#include<iostream>
#include <fstream>
#include <string>
using namespace std;
class UnitPrice
{
protected:
	int unitMeter;
	int peak;
	//double price;
	double rank[6]; // Cac dinh muc gia
	int unitRank[6]; // cac so dien tai tung muc
	double priceRank[6]; // gia tien tai tung muc
	double total; // Tong tien cac muc.
public:
	UnitPrice(int = 0);
	~UnitPrice();
	int getUnit();
	void setUnit(int);
//	void calculate();
	double getPrice();
	void showUnitPrice();
	double getTotalPrice();
	void setRank(UnitPrice &);
	void readData(string);
	void writeData(string);
	void calcPrice();
};

