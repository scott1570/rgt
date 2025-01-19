#pragma once


typedef struct _Menu
{
	int tablenumber;
	TCHAR szMenu[100] = { 0 };
	int number;
	int status;

}Menu;

typedef void  (*LPFNOnStatusChange)(Menu status);
