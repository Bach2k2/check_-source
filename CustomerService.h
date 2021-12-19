#pragma once
#include "Customer.h"
#include "Service.h"
#include <string>
#include<fstream>
#include <iostream>
#include <string>
#include<iomanip>
using namespace std;
class CustomerService: public Service
{
public:
    Customer* cusHead;
    Customer* cusTail;
    static int cusAmount;
public:
    CustomerService();
    CustomerService(const CustomerService&);
    ~CustomerService();
    void add();
    void add(Customer* customer);//them sau
    bool isEmpty();
    void remove();//Xoa dau
    void update();
    void display();
    void search();
    void searchByName();
    bool contain(string);
    Customer& getACus(string);
    //   void setData();
    void readDataInFile(string);//Doc file
    void showInfoByMkh(string);
    void writeDataInFile(string);
    void displayUpdateMenu();
    void sortByName();
};

