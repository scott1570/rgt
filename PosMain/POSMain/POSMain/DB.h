#pragma once


#include "defines.h"

#include <afxtempl.h>
class DB
{

public:
	int updateMenuState(int tableIndex, TCHAR* szMenu, int status);
	int addOrder(int table, Menu menu);
	int removeOrder(int table);
	

private:
	CList<Menu*> mMenuList;

};

