#pragma once


#include "defines.h"
#include "ControlInterface.h"
#include "Entity.h"
#include "UseCases.h"
#include "DB.h"
#include "POSMainDlg.h"
#include "ServiceMaster.h"
#include "ServiceProxy.h"

class Controller : public ControlInterface
{
public:

	Controller(CPOSMainDlg *pDlg);

	Entity* mpEntity;
	UseCases* mpUseCase;
	DB* mpDB;
	CPOSMainDlg* mpDlg;
	ServiceMaster* mpMaster;
	ServiceProxy* mpProxy;


protected:
	
	virtual void onStatusChange(LPVOID param);
	virtual void onOrderChanged(LPVOID param);
	
	
};

