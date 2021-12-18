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
    
    
public:

    BillService();
    ~BillService();
    MeterService meterList;
    CustomerService cusList;
    void add(ElecBill* bill);// Nhận từ file
    bool isEmpty();// Danh sách có rỗng
    void remove();// Xóa
    void update();  
    void display(); 
    void search(); 
    bool contain(int);
    void calculatePrice();

    void writeIntoFile(string path);
    void readTwoId(string path);
    void readNewMonth(string path);
    void displayWithArea(string);
    void setAllUP(UnitPrice&);
    ElecBill& getABill(int);
    void calcPricePerCus(string);
};

