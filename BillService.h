#pragma once
#include "ElecBill.h"
#include "MeterService.h"
#include "CustomerService.h"
class BillService
{
private:         //BillService
    ElecBill* pHead; //
    ElecBill* pTail;
    static int billAmount;  
    int monthManage;
    int yearManage;
public:
    BillService();
    ~BillService();
    MeterService meterList;
    CustomerService cusList;
    void setMeterList(string path);
    void setCusList(string path);
   // void setMetAndCus();//Thêm nhập từ bàn phím
    void add(ElecBill* bill);// Nhận từ file
    bool isEmpty();// Danh sách có rỗng
    void remove();// Xóa
    void update();  
    void display(); 
    void search();  
    void searchByMeter(int);
    void searchByCustomer(string);
 //   void readAllDataInFile(string path); // Đọc file

    bool contain(int);
    void calculatePrice();
    void writeIntoFile(string path);
    void readNewMonth(string path);
    void displayWithArea(string); //In  theo khu vuc
    void setAllUP(UnitPrice&);
    ElecBill& getABill(int);
    void createBill(MeterService&,CustomerService&, UnitPrice&); // tao cac bills
    void exByArea(string path,string address);// Ham xuat ra file theo khu vuc
    void exABill(string path,string cusID);// Ham xuat ra tung file
};

