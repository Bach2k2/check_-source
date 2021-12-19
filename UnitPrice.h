#pragma once
#include<iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <Windows.h>
using namespace std;
class UnitPrice
{
private:
	int unitMeter;
	int peak;
	//double price;
	double *rank; // Cac dinh muc gia
	int *unitRank; // cac so dien tai tung muc
	double *priceRank; // gia tien tai tung muc
	double total; // Tong tien cac muc.
public:
	UnitPrice(int = 0);
	~UnitPrice();
	int getUnit();
	void setUnit(int);
//	void calculate();
	double getPrice();
	void showUnitPrice();
	void showRank();
	double getTotalPrice();
	void setRank(UnitPrice &);
	void typeRank();
	void readData(string);
	void writeData(string);
	void calcPrice();
};

