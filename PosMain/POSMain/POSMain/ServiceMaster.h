#pragma once


#include "defines.h"
#include "ServiceProxy.h"
class ServiceMaster
{
public:

	ServiceMaster();
	~ServiceMaster();
	void order(Menu menu);
	static void onOderStatusChanged(LPVOID param);


	ServiceProxy* mpProxy;
};

