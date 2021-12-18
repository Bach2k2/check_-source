#include <iostream>
#include <iomanip>
using namespace std;
#include "UnitPrice.h"
UnitPrice::UnitPrice(int unit)
{
	this->rank = new double[6];
	this->unitRank = new int[6];
	this->priceRank = new double[6];
	for (int i = 0; i < 6; i++)
	{
		rank[i] = 0;
		unitRank[i] = 0;
		priceRank[i] = 0;
	}
	this->unitMeter = 0;
	this->total = 0;
	this->peak = 1;
}

UnitPrice::~UnitPrice()
{
	delete rank;
	delete unitRank;
	delete priceRank;
}
int UnitPrice::getUnit()
{
	return this->unitMeter;
}
void UnitPrice::setUnit(int unit)
{
	this->unitMeter = unit;
}
void UnitPrice::typeRank()
{
	for (int i = 0; i < 6; i++)
	{
		cout << " Nhap gia tien tai cac muc " << i + 1 << " : ";
		cin >> rank[i];
		cout << "\n";
	}
	cout << " THONG BAO : Don gia da duoc cap nhat: " << endl;
	for (int i = 0; i < 6; i++)
	{
		cout << " Muc " << i + 1 << ": ";
		cout<< rank[i];
		cout << "\n";
	}
}
void UnitPrice::showRank()
{
	cout << "\n\t\t Don gia theo tung muc: " << endl;
	for (int i = 0; i < 6; i++)
	{
		cout << " Muc " << i + 1 << ": ";
		cout << rank[i];
		cout << "\n";
	}
}
double UnitPrice::getPrice()
{
	cout << "Tong tien :";
	return this->total;
}
void UnitPrice::calcPrice()
{
	// Neu chi dien bac 1
	if (unitMeter <= 50)
	{
		peak = 1;
		unitRank[0] = unitMeter;
	}
	else
		//Neu chi dien bac 2:
		if (unitMeter <= 100)
		{
			peak = 2;
			unitRank[0] = 50;
			unitRank[1] = unitMeter - 50;
		}
		else
			//Neu chi dien bac 3:
			if (unitMeter <= 200)
			{
				peak = 3;
				unitRank[0] = 50;
				unitRank[1] = 50;
				unitRank[2] = unitMeter - 100;
			}
			else
				//Neu chi dien bac 4:
				if (unitMeter <= 300)
				{
					peak = 4;
					unitRank[0] = 50;
					unitRank[1] = 50;
					unitRank[2] = 100;
					unitRank[3] = unitMeter - 200;
				}
				else
					//Neu chi dien bac 5:
					if (unitMeter <= 400)
					{
						peak = 5;
						unitRank[0] = 50;
						unitRank[1] = 50;
						unitRank[2] = 100;
						unitRank[3] = 100;
						unitRank[4] = unitMeter - 300;
					}
	//Neu chi dien bac 6:
					else
					{
						peak = 6;
						unitRank[0] = 50;
						unitRank[1] = 50;
						unitRank[2] = 100;
						unitRank[3] = 100;
						unitRank[4] = 100;
						unitRank[5] = unitMeter - 400;
					}
	this->total = 0; // tra gt cu; // Dung
	for (int i = 0; i < peak; i++)
	{
		priceRank[i] = unitRank[i] * rank[i];
		total += priceRank[i];
	}
}
void UnitPrice::showUnitPrice()
{
	cout << "\n*\t Muc\t\t So chi dien tai moi muc \t\t Gia tien tai moi muc \t\t";
	for (int i = 0; i < peak; i++)
	{
		cout << "\n*\t" << setw(5) << i + 1 << setw(20) << unitRank[i] << setw(25) << priceRank[i];
	}
	cout << "\n*\t Muc cao nhat: " << this->peak;
	cout << "\n*\t Tong tien:" <<setw(35)<< total << endl;
}
void UnitPrice::readData(string path)
{
	ifstream file(path, ios::in);
	if (file.is_open())
	{
		for (int i = 0; i < 6; i++) {
			file >> rank[i];
		}
		cout << "THONG BAO: Da them thong tin don gia: " << path << endl;
	}
}
double UnitPrice::getTotalPrice()
{
	return total;
}
void UnitPrice::setRank(UnitPrice& uPrice)
{
	for (int i = 0; i < 6; i++)
	{
		this->rank[i] = uPrice.rank[i];
	}
}