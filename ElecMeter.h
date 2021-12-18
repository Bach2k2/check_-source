#pragma once
#include <iostream>
#include <fstream>
using namespace std;
class ElecMeter
{
private:
    int meterNumber;// Khoa chinh
    int prevMeter;
    int nextMeter;
    int unit;
    string cusId;
public:
    ElecMeter* next;
    ElecMeter(int=0, int=0, int=0,string="");
    ElecMeter(const ElecMeter&);
    ~ElecMeter();
    void fromString(string);

    // set:
    void setMeterNumber(int);
    void setPrevMeter(int);
    void setNextMeter(int);
    void setCusId(string);
    void typeAllData();
//    void setMeterData();
    void setUnit(int);
    // get:
    int getMeterNumber() { return meterNumber; }
    int getPrevMeter() { return prevMeter; }
    int getNextMeter() { return nextMeter; }
    int getUnit() { return unit; }
    string getCusID() { return cusId; }
    friend ostream& operator<<(ostream&,const ElecMeter&);
    void writeFile(string);
};

