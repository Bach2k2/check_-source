#include<iostream>
#include "MeterService.h"
#include "CustomerService.h"
#include "BillService.h"
using namespace std;
BillService billManager;
MeterService meterManager;
CustomerService cusManager;
UnitPrice unitPrice;
void displayBillMenu();
void displayCustomerMenu();
void displayMainMenu();

int main()
{
	int bChoice;
	cout << " Ban co muon lay du lieu cu da quan ly khong? " << endl;
	cout << "Nhan 1 de co - Nhan 0 de huy" << endl;
	cin >> bChoice;
	switch (bChoice)
	{
	case 1:
	{
		//cout << "Nhap duong dan file bill  -- Nhap meter.txt" << endl;
		string uPath;
		uPath = "UnitPrice.txt";
		unitPrice.readData(uPath);
		string mPath;
		mPath = "meter.txt";
		meterManager.readFile(mPath);
		system("pause");
		string path2;
		path2 = "custome.txt";
		cusManager.readDataInFile(path2);
		system("pause");
		string path3 = "CongTo_KhachHang.txt";
		billManager.readTwoId(path3);
		// Tinh san gia tien moi hoa don: 
		system("pause");
		break;
	}
	default:
		cout << " Da huy" << endl;
		break;
	}
	displayMainMenu();
}
void displayBillMenu()
{
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
		cout << "\n\t\t\t|5. Hien thi het tat ca hoa don trong 1 thang  \t\t\t|";
		cout << "\n\t\t\t|6. Luu vao file tat ca hoa don\t\t\t\t\t|";
		cout << "\n\t\t\t|7. Quan ly hoa don theo tung khu vuc \t\t\t\t|";
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
			cout << "\nCHUC NANG: TIM KIEM THONG TIN MOT HOA DON. " << endl;
			billManager.search();
			system("pause");
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
			cout << "\nCHUC NANG: IN TAT CA HOA DON SAU KHI TINH TIEN";
			billManager.setAllUP(unitPrice);
			billManager.display();
			system("pause");
			break;
		}
		case 6:
		{
			cout << "\n CHUC NANG: IN VAO FILE"<<endl;
			string savePath;
			cout << "Nhap duong dan: ";
			cin >> savePath;
			billManager.writeIntoFile(savePath);
			break;
		}
		case 7:
		{
			cout << "\n CHUC NANG: IN TAT CA HOA DON THEO KHU VUC" << endl;
			cin.ignore(100,'\n');
			cout << "Nhap khu vuc muon tim kiem:  " << endl;
			string area;
			getline(cin, area);
			billManager.displayWithArea(area);
			system("pause");
			break;
		}
		case 8:
		{
			cout << "CHUC NANG: TINH TIEN HOA DON THEO KHACH HANG" << endl;

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
void displayMeterMenu()
{
	int choice;
	do
	{
		system("cls");
		cout << "\n\n";
		cout << "\n\t\t\t|-----------------------QUAN LY CONG TO DIEN--------------------|";
		cout << "\n\t\t\t|1. Them moi mot cong to  \t\t\t\t\t|";
		cout << "\n\t\t\t|2. Cap nhat thong tin mot cong to\t\t\t\t|";
		cout << "\n\t\t\t|3. Tim kiem mot cong to\t\t\t\t\t|";
		cout << "\n\t\t\t|4. Xoa mot cong to\t\t\t\t\t\t|";
		cout << "\n\t\t\t|5. Hien thi het tat ca cong to dang quan ly\t\t\t|";
		cout << "\n\t\t\t|6. In vao file tat ca cong to da cap nhat\t\t\t|";
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
			cout << "\nCHUC NANG: CAP NHAT THONG TIN MOT CONG TO" << endl;
			meterManager.update();
			system("pause");
			break;
		}
		case 3:
		{
			system("cls");
			cout << "\nCHUC NANG: TIM KIEM THONG TIN MOT CONG TO" << endl;
			cout << "\nNhap so cong to cua hoa don: ";
			meterManager.search();
			system("pause");
			break;
		}
		case 4:
		{
			system("cls");
			cout << "\nCHUC NANG: XOA MOT CONG TO";
			meterManager.remove();
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			meterManager.display();
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			cout << "\nCHUC NANG: IN VAO FILE TAT CA CONG TO DA NHAP" << endl;
			string mPath;
			cout << "nhap duong dan can luu" << endl;
			cin >> mPath;
			meterManager.writeFile(mPath);
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
		cout << "\n\t\t\t|----------------------Quan ly Khach Hang-----------------------|";
		cout << "\n\t\t\t|1. Them moi khach hang \t\t\t\t\t|";
		cout << "\n\t\t\t|2. Cap nhat thong tin khach hang\t\t\t\t|";
		cout << "\n\t\t\t|3. Tim kiem mot khach hang\t\t\t\t\t|";
		cout << "\n\t\t\t|4. Xoa di mot khach hang\t\t\t\t\t|";
		cout << "\n\t\t\t|5. In danh sach cua tat ca khach hang\t\t\t\t|";
		cout << "\n\t\t\t|6. Dua du lieu vao file\t\t\t\t\t|";
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
			cout << "\nCHUC NANG: THAY DOI THONG TIN CUA KHACH HANG " << endl;
			//	cout << "\nNhap so cong to cua khach hang:";
			cusManager.update();
			system("pause");
			break;
		}
		case 3:
		{
			system("cls");
			cout << "\nCHUC NANG: TIM KIEM KHACH HANG " << endl;
			cout << " Chon loai tim kiem :" << endl;
			cout << "1. Theo ma khach hang." << endl;
			cout << "2.Theo ten" << endl;
			cout << "Lua chon:  ";
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
		case 4:
		{
			system("cls");
			cout << "\nCHUC NANG: XOA KHACH HANG" << endl;
			cusManager.remove();
			system("pause");
			break;
		}
		case 5:
		{
			cout << "\nCHUC NANG: IN DANH SACH KHACH HANG: " << endl;
			system("cls");
			cusManager.display();
			system("pause");
			break;
		}
		case 6:
		{
			cout << "\nCHUC NANG: IN VAO FILE" << endl;
			cout << "Nhap ten file" << endl;
			string KhPath;
			cin >> KhPath;
			cusManager.writeDataInFile(KhPath);
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
		case 0:
		{
			cout << "Tam biet" << endl;
			break;
		}
		default:
		{
			cout << "Lua chon sai!" << endl;
		}
		}
	} while (choice != 0);
}

