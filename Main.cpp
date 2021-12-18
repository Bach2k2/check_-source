#include<iostream>
#include <Windows.h>
#include "MeterService.h"
#include "CustomerService.h"
#include "BillService.h"
using namespace std;
BillService billManager;
MeterService meterManager(billManager.meterList);
CustomerService cusManager(billManager.cusList);
UnitPrice unitPrice;
void displayBillMenu();
void displayCustomerMenu();
void displayMainMenu();
void displayUnitPriceMenu();
void displaySearchBill();

int main()
{
	
	displayMainMenu();
	int bChoice;
	cout << " Ban co muon lay du lieu cu da quan ly khong? " << endl;
	cout << "Nhan 1 de co - Nhan 0 de huy" << endl;
	cin >> bChoice;
	switch (bChoice)
	{
	case 1:
	{
		string oMPath;
		cout << "Duong dan luu cac thong tin cong to: " << endl;
		cin >> oMPath;
		meterManager.writeFile(oMPath);
		system("pause");
		cout << "Duong dan luu thong tin khach hang: " << endl;
		string oKhPath;
		cin >> oKhPath;
		cusManager.writeDataInFile(oKhPath);
		system("pause");
		string oBillPath;
		cout << "Nhap duong dan luu tat ca hoa don: " << endl;
		cin >> oBillPath;
		billManager.writeIntoFile(oBillPath);
		system("pause");
		break;
	}
	case 0:
	{
		cout << " Da huy luu du lieu " << endl;
		break;
	}
	default:
		cout << "Lua chon khong chinh xac " << endl;
		break;
	}	
}
void displayBillMenu()
{
	billManager.meterList = meterManager;
	billManager.cusList = cusManager;
	int choice;
	do
	{
		system("cls");
		cout << "\n\n";
		cout << "\n\t\t\t|----------------------QUAN LY HOA DON--------------------------|";
		cout << "\n\t\t\t|1. Them tat ca hoa don cho thang tiep theo   \t\t\t|";
		cout << "\n\t\t\t|2. Cap nhat thong tin mot hoa don\t\t\t\t|";
		cout << "\n\t\t\t|3. Xuat ra mot hoa don   \t\t\t\t\t|";
		cout << "\n\t\t\t|4. Xoa di mot hoa don\t\t\t\t\t\t|";
		cout << "\n\t\t\t|5. Xuat tat ca hoa don  \t\t\t\t\t|";
		cout << "\n\t\t\t|6. Quan ly hoa don theo tung khu vuc \t\t\t\t|";
		cout << "\n\t\t\t|7. In danh sach tien dien cua moi khach\t\t\t|";
		cout << "\n\t\t\t|0. Tro ve menu chinh  \t\t\t\t\t\t|";
		cout << "\n\t\t\t|---------------------------------------------------------------|";
		cout << "\n\n\t\t\tNhap lua chon: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			system("cls");
			cout << "\nCHUC NANG: THEM MOI TAT CA HOA DON CHO THANG TIEP THEO. " << endl;
			billManager.createBill(meterManager, cusManager, unitPrice);
			billManager.display();
			system("pause");
			cout << "nhap file thang tiep theo can them" << endl;
			string monthPath;
			cin >> monthPath;
			billManager.readNewMonth(monthPath);
			meterManager.readFile(monthPath);
			system("pause");
			break;
		}
		case 2:
		{
			system("cls");
			cout << "\nCHUC NANG: CAP NHAT THONG TIN MOT HOA DON. " << endl;
			billManager.update();
			system("pause");
			break;
		}
		case 3:
		{
			system("cls");
			displaySearchBill();
			break;
		}
		case 4:
		{
			system("cls");
			cout << "\nCHUC NANG: XOA MOT HOA DON";
			billManager.remove();
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			cout << "\nCHUC NANG: XUAT TAT CA HOA DON ";
			billManager.setAllUP(unitPrice);
			billManager.display();
			system("pause");
			cout << "Nhan phim 1 de tiep tuc xuat ra file, nhan phim 0 de thoat " << endl;
			int osChoice;
			do
			{
				cout << "Nhap lua chon: " << endl;
				cin >> osChoice;
				if (osChoice == 1)
				{
					string oBillPath;
					cin.ignore(100, '\n');
					cout << " Nhap ten file: " << endl;
					getline(cin, oBillPath);
					billManager.writeIntoFile(oBillPath);
					system("pause");
				}
				else if (osChoice == 0) {
					cout << " Xac nhan thoat ve menu " << endl;
					system("pause");
				}
				else
				{
					cout << " Lua chon khong dung! ";
					system("pause");
				}
			} while (osChoice != 0);
			break;
		}
		case 6:
		{
			cout << "\n CHUC NANG: IN TAT CA HOA DON THEO KHU VUC" << endl;
			cin.ignore(100, '\n');
			cout << "Nhap khu vuc muon tim kiem:  " << endl;
			string area;
			getline(cin, area);
			billManager.displayWithArea(area);
			cout << "Nhan phim 1 de tiep tuc xuat ra file, nhan phim 0 de thoat " << endl;
			int osChoice;
			do
			{
				cout << "Nhap lua chon: " << endl;
				cin >> osChoice;
				if (osChoice == 1)
				{
					string oBillPath;
					cin.ignore(100, '\n');
					cout << " Nhap ten file: " << endl;
					getline(cin, oBillPath);
					billManager.exByArea(oBillPath, area);
					system("pause");
				}
				else if (osChoice == 0) {
					cout << " Xac nhan thoat ve menu " << endl;
					system("pause");
				}
				else
				{
					cout << " Lua chon khong dung! ";
					system("pause");
				}
			} while (osChoice != 0);
			system("pause");
			break;
		}
		case 0:
			cout << "\n\t\t\t------------------------TRO LAI MENU CHINH----------------------------------" << endl;
			system("pause");
			break;
		default:
			cout << "Lua chon khong hop le" << endl;
			cout << "Moi nhap lai lua chon: " << endl;
			system("pause");
			break;
		}
	} while (choice != 0);
}
void displayMeterMenu()
{
	int choice;
	do
	{
		system("cls");
		cout << "\n\n";
		cout << "\n\t\t\t|-----------------------QUAN LY CONG TO DIEN--------------------|";
		cout << "\n\t\t\t|1. Them moi mot cong to  \t\t\t\t\t|";
		cout << "\n\t\t\t|2. Them cong to tu file  \t\t\t\t\t|";
		cout << "\n\t\t\t|3. Cap nhat thong tin mot cong to\t\t\t\t|";
		cout << "\n\t\t\t|4. Tim kiem mot cong to\t\t\t\t\t|";
		cout << "\n\t\t\t|5. Xoa mot cong to\t\t\t\t\t\t|";
		cout << "\n\t\t\t|6. Hien thi danh sach cong to dang quan ly\t\t\t|";
		cout << "\n\t\t\t|0. Tro ve menu chinh\t\t\t\t\t\t|";
		cout << "\n\t\t\t|---------------------------------------------------------------|";
		cout << "\n\n\t\t\tNhap lua chon: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			system("cls");
			cout << "\nCHUC NANG: THEM MOI MOT CONG TO. " << endl;
			meterManager.add();
			system("pause");
			break;
		}
		case 2:
		{
			system("cls");
			cout << "\nCHUC NANG: THEM CONG TO TU FILE " << endl;
			string iMPath;
			cin >> iMPath;
			meterManager.readFile(iMPath);
			system("pause");
			break;
		}
		case 3:
		{
			system("cls");
			cout << "\nCHUC NANG: CAP NHAT THONG TIN MOT CONG TO" << endl;
			meterManager.update();
			system("pause");
			break;
		}
		case 4:
		{
			system("cls");
			cout << "\nCHUC NANG: TIM KIEM THONG TIN MOT CONG TO" << endl;
			cout << "\nNhap so cong to cua hoa don: ";
			meterManager.search();
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			cout << "\nCHUC NANG: XOA MOT CONG TO";
			meterManager.remove();
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			meterManager.display();
			system("pause");
			break;
		}
		case 0:
			cout << "\n\t\t\t------------------------Tam biet----------------------------------" << endl;
			break;
		default:
			cout << "Lua chon khong hop le" << endl;
			cout << "Moi nhap lai lua chon: " << endl;
			break;
		}
	} while (choice != 0);
}
void displayCustomerMenu()
{
	int choice;
	do
	{
		system("cls");
		cout << "\n\n";
		cout << "\n\t\t\t|----------------------QUAN LY KHACH HANG-----------------------|";
		cout << "\n\t\t\t|1. Them moi khach hang \t\t\t\t\t|";
		cout << "\n\t\t\t|2. Them khach hang tu file\t\t\t\t\t|";
		cout << "\n\t\t\t|3. Cap nhat thong tin khach hang\t\t\t\t|";
		cout << "\n\t\t\t|4. Tim kiem mot khach hang\t\t\t\t\t|";
		cout << "\n\t\t\t|5. Xoa di mot khach hang\t\t\t\t\t|";
		cout << "\n\t\t\t|6. In danh sach cua tat ca khach hang\t\t\t\t|";
		cout << "\n\t\t\t|7. Sap xep tat ca khach hang theo ten\t\t\t\t|";
		cout << "\n\t\t\t|0. Tro ve menu chinh   \t\t\t\t\t|";
		cout << "\n\t\t\t|---------------------------------------------------------------|";
		cout << "\n\n\t\t\tNhap lua chon : ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			system("cls");
			cout << "\nCHUC NANG: THEM KHACH HANG " << endl;
			cusManager.add();
			system("pause");
			break;
		}
		case 2:
		{
			system("cls");
			cout << "\nCHUC NANG: THEM KHACH HANG TU FILE " << endl;
			Sleep(100);
			cout << "\n Nhap duong dan cua file khach hang: ";
			string path2;
			cin >> path2;
			cusManager.readDataInFile(path2);
			system("pause");
			break;
		}
		case 3:
		{
			system("cls");
			cout << "\nCHUC NANG: THAY DOI THONG TIN CUA KHACH HANG " << endl;
			cusManager.update();
			system("pause");
			break;
		}
		case 4:
		{
			system("cls");
			cout << "\nCHUC NANG: TIM KIEM KHACH HANG " << endl;
			cout << "|\t Chon loai tim kiem :" << endl;
			cout << "|\t1. Theo ma khach hang." << endl;
			cout << "|\t2.Theo ten" << endl;
			cout << "|\tLua chon:  ";
			int s_choice;
			cin >> s_choice;
			if (s_choice == 1)
			{
				cusManager.search();
			}
			else if(s_choice==2)
			{
				cusManager.searchByName();
			}
			
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			cout << "\nCHUC NANG: XOA KHACH HANG" << endl;
			cusManager.remove();
			system("pause");
			break;
		}
		case 6:
		{
			cout << "\nCHUC NANG: IN DANH SACH KHACH HANG: " << endl;
			system("cls");
			cusManager.display();
			system("pause");
			break;
		}
		case 7:
		{
			cout << "\nCHUC NANG: SAP XEP DANH SACH THEO TEN" << endl;
			cusManager.sortByName();
			break;
		}
		case 0:
		{

		}
			cout << "\n\t\t\t---------TRO VE MENU CHINH----------" << endl;
			system("pause");
			break;
		default:
			cout << "Nhap lua chon khong dung! ";
			break;
		}
	} while (choice != 0);
}
void displayMainMenu()
{
	int choice;
	do
	{
		system("cls");
		cout << "\n\n";
		cout << "\n\t\t\t|-------------------Menu chinh------------------|";
		cout << "\n\t\t\t|1. Quan ly cong to dien \t\t\t|";
		cout << "\n\t\t\t|2. Quan ly khach hang\t\t\t\t|";
		cout << "\n\t\t\t|3. Quan ly hoa don \t\t\t\t|";
		cout << "\n\t\t\t|4. Quan ly don gia \t\t\t\t|";
		cout << "\n\t\t\t|0. Thoat\t\t\t\t\t|";
		cout << "\n\t\t\t|-----------------------------------------------|";
		cout << "\n\n\t\t\tNhap lua chon: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			displayMeterMenu();
			break;
		}
		case 2:
		{
			displayCustomerMenu();
			break;
		}
		case 3:
		{
			displayBillMenu();
			break;
		}
		case 4:
		{
			displayUnitPriceMenu();
			break;
		}
		case 0:
		{
			cout << "--------------\t\tTam biet\t\t----------------" << endl;
			break;
		}
		default:
		{
			cout << "Lua chon sai!" << endl;
		}
		}
	} while (choice != 0);
}
void displayUnitPriceMenu()
{
	int choice;
	do
	{
		system("cls");
		cout << "\n\n";
		cout << "\n\t\t\t|-------------------QUAN LY DON GIA------------------|";
		cout << "\n\t\t\t|1. Nhap don gia tu file\t\t\t|";
		cout << "\n\t\t\t|2. Nhap don gia tu ban phim\t\t\t|";
		cout << "\n\t\t\t|3. In ra man hinh don gia hien tai\t|";
		cout << "\n\t\t\t|0. Thoat\t\t\t\t|";
		cout << "\n\t\t\t|----------------------------------------------------|";
		cout << "\n\n\t\t\tNhap lua chon: "<<endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			system("cls");
			cout << "CHUC NANG: NHAP DON GIA TU FILE" << endl;
			Sleep(100);
			cout << "Nhap duong dan cua file don gia: " << endl;
			string uPath;
			cin >> uPath;
			unitPrice.readData(uPath);
			system("pause");
			break;
		}
		case 2:
		{
			system("cls");
			cout << "CHUC NANG: NHAP DON GIA TU BAN PHIM " << endl;
			unitPrice.typeRank();
			system("pause"); 
			break;
		}
		case 3:
		{
			system("cls");
			cout << "CHUC NANG: NHAP DON GIA TU BAN PHIM " << endl;
			unitPrice.showRank();
			system("pause");
			break;
		}
		default:
		{
			cout << "Lua chon nhap khong dung - Moi nhap lai " << endl;
		}
		}
	} while (choice != 0);
}
void displaySearchBill()
{
	cout << "\nCHUC NANG: TIM KIEM THONG TIN MOT HOA DON. " << endl;
	cout << "| Co 3 loai tim kiem: " << endl;
	cout << " 1. Tim kiem theo ma hoa don" << endl;
	cout << " 2. Tim kiem theo so cong to" << endl;
	cout << " 3. Tim kiem theo ma khach hang" << endl;
	cout << " Lua chon: ";
	int choice1;
	cin >> choice1;
	if (choice1 == 1)
	{

		billManager.search();
		system("pause");
	}
	else if (choice1 == 2)
	{
		int meterNum;
		cout << "\n Nhap so cong to cua hoa don: " << endl;
		cin >> meterNum;
		billManager.searchByMeter(meterNum);
		system("pause");
	}
	else if (choice1 == 3)
	{
		string cusId;
		cout << "\n Nhap ma khach hang cua hoa don: " << endl;
		cin >> cusId;
		billManager.searchByCustomer(cusId);
		system("pause");
	}
	else
	{
		cout << "\nLua chon khong dung" << endl;

	}
}

