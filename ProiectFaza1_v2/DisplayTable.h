#pragma once
#include "Table.h"
#include "Column.h"
#include "DataBase.h"
#include "data_type.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;


class DisplayTable
{
private:
	static DisplayTable* instance;
	DisplayTable() {}
public:
    DisplayTable(const DisplayTable&) = delete;
    void operator=(const DisplayTable&) = delete;
    static DisplayTable* getInstance()
    {
        if (!instance)
            instance = new DisplayTable;
        return instance;
    }
    void run()
    {
        DataBase* db = db->getInstance();
    }
};
DisplayTable* DisplayTable::instance = 0;
