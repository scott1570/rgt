#pragma once
class ControlInterface
{


protected:
	virtual void onStatusChange(LPVOID param) = 0;
	
	virtual void onOrderChanged(LPVOID param) = 0;

	
};

