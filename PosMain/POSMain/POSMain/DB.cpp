#include "pch.h"
#include "DB.h"


int DB::updateMenuState(int tableIndex, TCHAR *szMenu, int status)
{
	int cnt = mMenuList.GetCount();
	POSITION pos = mMenuList.GetHeadPosition();
	POSITION prev = pos;
	for (int i = 0; i < cnt; i++) {

		prev = pos;
		Menu* pMenu = mMenuList.GetNext(prev);
		if (pMenu->tablenumber == tableIndex && !_tcsicmp(szMenu, pMenu->szMenu )) {
			pMenu->status = status;
		}
		pos++;

	}

	return 0;
}
int DB::addOrder(int table, Menu menu )
{

	Menu* pMenu = new Menu;
	pMenu->number = menu.number;
	_tcscpy_s(pMenu->szMenu, menu.szMenu);
	pMenu->tablenumber = table;


	mMenuList.AddTail(pMenu);
	return 0;
}
int DB::removeOrder(int table)
{
	int cnt = mMenuList.GetCount();
	POSITION pos = mMenuList.GetHeadPosition();
	POSITION prev = pos;
	for (int i = 0; i < cnt; i++) {

		prev = pos;
		Menu* pMenu = mMenuList.GetNext(prev);
		mMenuList.RemoveAt(prev);
		delete pMenu;
		pMenu = NULL;
		pos++;

	}


	return 0;
}