#include "pch.h"

#include "ControlInterface.h"
#include "Controller.h"
#include "POSMainDlg.h"

Controller::Controller(CPOSMainDlg *pDlg) {

	mpUseCase = new UseCases();
	mpEntity = new Entity(mpUseCase);
	mpDlg = pDlg;

	
	mpMaster = new ServiceMaster();
	mpProxy = new ServiceProxy(mpMaster);
	if (mpProxy->Init(_T("127.0.0.1"), 5678) < 0)
	{
		AfxMessageBox(_T("cannot connect to service"));
		exit(0);
	}

}


void Controller::onStatusChange(LPVOID param) {

}

void Controller::onOrderChanged(LPVOID param) {

}


